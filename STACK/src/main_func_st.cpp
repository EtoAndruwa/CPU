#include "stack.h"

void StackSqrt(Stack* stack_struct) // (OK) Gets the root of the value
{
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    stack_struct->data[stack_struct->next_empty_cell - 1] = sqrt(stack_struct->data[stack_struct->next_empty_cell - 1]) * 10;
    Calculate_hash(stack_struct);

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}

void StackOut(Stack * stack_struct) // (OK) Prints the stack's current structure in the console
{   
    printf("\nLEFT_CANARY: = %ld\n", *(stack_struct->left_canary_position));
    for(size_t i = 0; i < stack_struct->capacity; i++) 
    {
        printf("data[%ld] = %d\n", i, stack_struct->data[i]);
    }
    printf("RIGHT_CANARY: = %ld\n\n", *(stack_struct->right_canary_position));
}

void StackAdd(Stack* stack_struct) // (OK) Adds the entered value to next empty memory cell of the stack
{   
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    stack_struct->data[stack_struct->next_empty_cell - 2] = (stack_struct->data[stack_struct->next_empty_cell - 2]) + (stack_struct->data[stack_struct->next_empty_cell - 1]);
    stack_struct->data[stack_struct->next_empty_cell - 1] = POISON_VALUE;
    stack_struct->next_empty_cell--;
    Calculate_hash(stack_struct);

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}

void StackMul(Stack* stack_struct) // (OK) Multiplies two values of the stack
{   
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    stack_struct->data[stack_struct->next_empty_cell - 2] = stack_struct->data[stack_struct->next_empty_cell - 1] * (stack_struct->data[stack_struct->next_empty_cell - 2] / 100);
    stack_struct->data[stack_struct->next_empty_cell - 1] = POISON_VALUE;
    stack_struct->next_empty_cell--;
    Calculate_hash(stack_struct);

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}

void StackSub(Stack* stack_struct) // (OK) Substracts one value of the stack from another one
{   
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    stack_struct->data[stack_struct->next_empty_cell - 2] = stack_struct->data[stack_struct->next_empty_cell - 2] - stack_struct->data[stack_struct->next_empty_cell - 1];
    stack_struct->data[stack_struct->next_empty_cell - 1] = POISON_VALUE;
    stack_struct->next_empty_cell--;
    Calculate_hash(stack_struct);

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}

void StackDiv(Stack* stack_struct) // (OK) Divides the preceding element by the last elemcapacityent of the stack
{   
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    if(stack_struct->data[stack_struct->next_empty_cell - 1] == 0)
    {
        stack_struct->error_code = ERR_DIV_TO_ZERO;
        StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    }
    else    
    {
        stack_struct->data[stack_struct->next_empty_cell - 2] = ((float)(stack_struct->data[stack_struct->next_empty_cell - 2]) / (float)(stack_struct->data[stack_struct->next_empty_cell - 1])) * 100;
        stack_struct->data[stack_struct->next_empty_cell - 1] = POISON_VALUE;
        stack_struct->next_empty_cell--;
        Calculate_hash(stack_struct);
    }

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}

void StackPush(Stack* stack_struct, stack_type push_value) // (OK) Gets the value and pushes in to the stack
{   
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    stack_struct->data[stack_struct->next_empty_cell++] = push_value; 
    stack_struct->hash = stack_struct->hash + push_value; // Сalculating new hash value

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}

stack_type StackPop(Stack* stack_struct) // (OK) Deletes the value from the stack
{   
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    stack_type poped_value = stack_struct->data[stack_struct->next_empty_cell - 1];
    stack_struct->data[stack_struct->next_empty_cell - 1] = POISON_VALUE;
    stack_struct->next_empty_cell--;
    stack_struct->hash = stack_struct->hash - poped_value; // Calculating new hash value

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    return poped_value;
}
