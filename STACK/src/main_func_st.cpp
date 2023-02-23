#include "stack.h"

void StackSqrt(Stack * st) // (OK) Gets the root of the value
{
    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    st->data[st->next_empty_cell - 1] = sqrt(st->data[st->next_empty_cell - 1]) * 10;
    Calculate_hash(st);
    //StackPrint(st); 

    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}

void StackOut(Stack * st) // (OK) Prints the stack's current structure in the console
{   
    printf("\nLEFT_CANARY: = %ld\n", *(st->left_canary_position));
    for(size_t i = 0; i < st->capacity; i++) 
    {
        printf("data[%ld] = %d\n", i, st->data[i]);
    }
    printf("RIGHT_CANARY: = %ld\n\n", *(st->right_canary_position));
}

void StackAdd(Stack * st) // (OK) Adds the entered value to next empty memory cell of the stack
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    st->data[st->next_empty_cell - 2] = (st->data[st->next_empty_cell - 2]) + (st->data[st->next_empty_cell - 1]);
    st->data[st->next_empty_cell - 1] = POISON_VALUE;
    st->next_empty_cell--;
    Calculate_hash(st);
    //StackPrint(st);

    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}

void StackMul(Stack * st) // (OK) Multiplies two values of the stack
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    st->data[st->next_empty_cell - 2] = (st->data[st->next_empty_cell - 1] * st->data[st->next_empty_cell - 2]) / 100;
    st->data[st->next_empty_cell - 1] = POISON_VALUE;
    st->next_empty_cell--;
    //printf("hash: %d\n", st->hash);
    Calculate_hash(st);

    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}

void StackSub(Stack * st) // (OK) Substracts one value of the stack from another one
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    st->data[st->next_empty_cell - 2] = st->data[st->next_empty_cell - 2] - st->data[st->next_empty_cell - 1];
    st->data[st->next_empty_cell - 1] = POISON_VALUE;
    st->next_empty_cell--;
    Calculate_hash(st);
    //StackPrint(st);

    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}

void StackDiv(Stack * st) // (OK) Divides the preceding element by the last elemcapacityent of the stack
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    st->data[st->next_empty_cell - 2] = ((float)(st->data[st->next_empty_cell - 2]) / (float)(st->data[st->next_empty_cell - 1]) ) * 100;
    st->data[st->next_empty_cell - 1] = POISON_VALUE;
    st->next_empty_cell--;
    Calculate_hash(st);
    //StackPrint(st);

    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}

void StackPush(Stack * st, stack_type push_value) // (OK) Gets the value and pushes in to the stack
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    st->data[st->next_empty_cell++] = push_value; 
    st->hash = st->hash + push_value; // Сalculating new hash value
    //printf("Hash value: %d", st->hash);
    //StackPrint(st);

    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}

stack_type StackPop(Stack * st) // (OK) Deletes the value from the stack
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    stack_type poped_value = st->data[st->next_empty_cell - 1];
    st->data[st->next_empty_cell - 1] = POISON_VALUE;
    st->next_empty_cell--;
    st->hash = st->hash - poped_value; // Calculating new hash value
    //printf("Hash value: %d", st->hash);
    //StackPrint(st);

    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    return poped_value;
}