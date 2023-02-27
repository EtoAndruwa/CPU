#include "stack.h"

void StackCtor(Stack* stack_struct, size_t stack_size) // (OK) Creates and initializes stack
{   
    stack_struct->capacity = stack_size;
    stack_struct->stack_pointer = calloc(1, 2 * sizeof(size_t) + stack_struct->capacity * sizeof(stack_type)); 

    if(stack_struct->stack_pointer == nullptr)
    {
        stack_struct->error_code = ERR_TO_CALLOC_STACK;
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        StackDtor(stack_struct);
        exit(ERR_TO_CALLOC_STACK);
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
