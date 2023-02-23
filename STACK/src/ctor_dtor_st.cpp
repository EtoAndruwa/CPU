#include "stack.h"

void StackCtor(Stack * st, size_t stack_size) // (OK) Creates and initializes stack
{   
    st->capacity = stack_size;
    st->stack_pointer = calloc(1, 2 * sizeof(size_t) + st->capacity * sizeof(stack_type)); 

    if(st->stack_pointer == nullptr)
    {
        st->error_code = ERR_TO_CALLOC_STACK;
        StackDump(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        StackDtor(st);
        exit(ERR_TO_CALLOC_STACK);
    }

    st->left_canary_position = (size_t*)st->stack_pointer;
    st->data = (stack_type*)(st->left_canary_position + 1);
    st->right_canary_position = (size_t*)(st->data + st->capacity);

    st->left_canary_position[0] = CANARY;
    st->right_canary_position[0] = CANARY;
    st->hash = 0;   

    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    for(size_t i = 0; i < st->capacity ; i++)
    {
        st->data[i] = POISON_VALUE;
    }

    StackCheck(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
}

void StackDtor(Stack * st) // (OK) Deletes the stack and spoils all stack's data with the poison value
{
    for(size_t i = 0; i < st->capacity; i++)
    {
        st->data[i] = POISON_VALUE;
    }

    st->capacity = 0;
    st->next_empty_cell = 0;
    st->hash = 0;
    st->left_canary_position[0] = 0;
    st->right_canary_position[0] = 0;

    st->left_canary_position = nullptr;
    st->right_canary_position = nullptr;
    st->data = nullptr;

    free(st->stack_pointer);
    st->stack_pointer = nullptr;
}