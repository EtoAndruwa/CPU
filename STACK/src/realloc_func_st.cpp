#include "stack.h"

void StackRealocUp(Stack* st) // (OK) Increases the capacity of the stack, reallocs data
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    if(st->next_empty_cell == st->capacity)
    {   
        st->capacity *= 2;

        st->stack_pointer = realloc(st->stack_pointer, st->capacity * sizeof(stack_type) + 2 * sizeof(size_t)); 

        if(st->stack_pointer == nullptr)
        {
            st->error_code = ERR_TO_REALLOC_UP;
            StackDump(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
            StackDtor(st);
            exit(ERR_TO_REALLOC_UP);
        }

        st->left_canary_position = (size_t*)st->stack_pointer;
        st->data = (stack_type*)(st->left_canary_position + 1);
        st->right_canary_position = (size_t*)(st->data + st->capacity);

        for(size_t i = st->next_empty_cell; i < st->capacity ; i++)
        {
            st->data[i] = POISON_VALUE;
        }

        st->left_canary_position[0] = CANARY;
        st->right_canary_position[0] = CANARY;
        //StackPrint(st);
    }

    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}

void StackRealocDown(Stack* st) // (OK) Decreases the capacity of the stack, reallocs data
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    if((st->next_empty_cell <= (st->capacity - 2) / 2) && (st->capacity > 3))
    {   
        st->capacity = st->capacity - ((st->capacity - 1)/2); // Decreases the capacity of the array

        st->stack_pointer = realloc(st->stack_pointer, st->capacity * sizeof(stack_type) + 2 * sizeof(size_t)); // Realocs the memory 

        if(st->stack_pointer == nullptr)
        {
            st->error_code = ERR_TO_REALLOC_DOWN;
            StackDump(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
            StackDtor(st);
            exit(ERR_TO_REALLOC_DOWN);
        }

        st->left_canary_position = (size_t*)st->stack_pointer;  
        st->data = (stack_type*)(st->left_canary_position + 1);
        st->right_canary_position = (size_t*)(st->data + st->capacity);

        for(size_t i = st->next_empty_cell; i < st->capacity ; i++)
        {
            st->data[i] = POISON_VALUE;
        }

        st->left_canary_position[0] = CANARY;
        st->right_canary_position[0] = CANARY;
        //StackPrint(st);
    }
    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}