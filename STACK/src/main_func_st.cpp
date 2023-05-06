#include "stack.h"

size_t StackCtor(Stack* stack_struct, size_t stack_size) // (OK) Creates and initializes stack
{   
    stack_struct->capacity = stack_size;
    stack_struct->stack_pointer = calloc(1, 2 * sizeof(size_t) + stack_struct->capacity * sizeof(stack_type)); 

    if(stack_struct->stack_pointer == nullptr)
    {
        stack_struct->error_code = ERR_TO_CALLOC_STACK;
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        StackDtor(stack_struct);
        return stack_struct->error_code;
    }

    stack_struct->left_canary_position = (size_t*)stack_struct->stack_pointer;
    stack_struct->data = (stack_type*)(stack_struct->left_canary_position + 1);
    stack_struct->right_canary_position = (size_t*)(stack_struct->data + stack_struct->capacity);

    stack_struct->left_canary_position[0] = CANARY;
    stack_struct->right_canary_position[0] = CANARY;
    stack_struct->hash = 0;   

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    for(size_t i = 0; i < stack_struct->capacity ; i++)
    {
        stack_struct->data[i] = POISON_VALUE;
    }

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    return 0;
}

void StackDtor(Stack* stack_struct) // (OK) Deletes the stack and spoils all stack's data with the poison value
{
    for(size_t i = 0; i < stack_struct->capacity; i++)
    {
        stack_struct->data[i] = POISON_VALUE;
    }

    stack_struct->capacity = 0;
    stack_struct->next_empty_cell = 0;
    stack_struct->hash = 0;
    stack_struct->left_canary_position[0] = 0;
    stack_struct->right_canary_position[0] = 0;

    stack_struct->left_canary_position = nullptr;
    stack_struct->right_canary_position = nullptr;
    stack_struct->data = nullptr;

    free(stack_struct->stack_pointer);
    stack_struct->stack_pointer = nullptr;
}

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
