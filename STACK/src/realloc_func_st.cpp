#include "stack.h"

void StackRealocUp(Stack* stack_struct) // (OK) Increases the capacity of the stack, reallocs data
{   
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    if(stack_struct->next_empty_cell == stack_struct->capacity)
    {   
        stack_struct->capacity *= 2;

        stack_struct->stack_pointer = realloc(stack_struct->stack_pointer, stack_struct->capacity * sizeof(stack_type) + 2 * sizeof(size_t)); 

        if(stack_struct->stack_pointer == nullptr)
        {
            stack_struct->error_code = ERR_TO_REALLOC_UP;
            StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
            StackDtor(stack_struct);
            exit(ERR_TO_REALLOC_UP);
        }

        stack_struct->left_canary_position = (size_t*)stack_struct->stack_pointer;
        stack_struct->data = (stack_type*)(stack_struct->left_canary_position + 1);
        stack_struct->right_canary_position = (size_t*)(stack_struct->data + stack_struct->capacity);

        for(size_t i = stack_struct->next_empty_cell; i < stack_struct->capacity ; i++)
        {
            stack_struct->data[i] = POISON_VALUE;
        }

        stack_struct->left_canary_position[0] = CANARY;
        stack_struct->right_canary_position[0] = CANARY;
    }

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}

void StackRealocDown(Stack* stack_struct) // (OK) Decreases the capacity of the stack, reallocs data
{   
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    if((stack_struct->next_empty_cell <= (stack_struct->capacity - 2) / 2) && (stack_struct->capacity > 3))
    {   
        stack_struct->capacity = stack_struct->capacity - ((stack_struct->capacity - 1)/2); // Decreases the capacity of the array

        stack_struct->stack_pointer = realloc(stack_struct->stack_pointer, stack_struct->capacity * sizeof(stack_type) + 2 * sizeof(size_t)); // Realocs the memory 

        if(stack_struct->stack_pointer == nullptr)
        {
            stack_struct->error_code = ERR_TO_REALLOC_DOWN;
            StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
            StackDtor(stack_struct);
            exit(ERR_TO_REALLOC_DOWN);
        }

        stack_struct->left_canary_position = (size_t*)stack_struct->stack_pointer;  
        stack_struct->data = (stack_type*)(stack_struct->left_canary_position + 1);
        stack_struct->right_canary_position = (size_t*)(stack_struct->data + stack_struct->capacity);

        for(size_t i = stack_struct->next_empty_cell; i < stack_struct->capacity ; i++)
        {
            stack_struct->data[i] = POISON_VALUE;
        }

        stack_struct->left_canary_position[0] = CANARY;
        stack_struct->right_canary_position[0] = CANARY;
    }
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}
