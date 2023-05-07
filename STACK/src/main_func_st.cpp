#include "stack.h"

int StackCtor(Stack* stack_struct, size_t stack_size) // (CHECKED) Creates and initializes stack
{   
    stack_struct->capacity = stack_size;
    stack_struct->stack_pointer = calloc(1, 2 * sizeof(size_t) + stack_struct->capacity * sizeof(stack_type)); 

    if(stack_struct->stack_pointer == nullptr)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }

    stack_struct->left_canary_position = (size_t*)stack_struct->stack_pointer;
    stack_struct->data = (stack_type*)(stack_struct->left_canary_position + 1);
    stack_struct->right_canary_position = (size_t*)(stack_struct->data + stack_struct->capacity);

    stack_struct->left_canary_position[0]  = CANARY;
    stack_struct->right_canary_position[0] = CANARY;
    stack_struct->hash = 0;   

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }

    for(size_t i = 0; i < stack_struct->capacity ; i++)
    {
        stack_struct->data[i] = POISON_VALUE;
    }

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }
    return RETURN_OK;
}

void StackDtor(Stack* stack_struct) // (CHECKED) Deletes the stack and spoils all stack's data with the poison value
{
    for(size_t i = 0; i < stack_struct->capacity; i++)
    {
        stack_struct->data[i] = POISON_VALUE;
    }

    stack_struct->capacity = 0;
    stack_struct->next_empty_cell = 0;
    stack_struct->hash = 0;
    stack_struct->left_canary_position[0]  = 0;
    stack_struct->right_canary_position[0] = 0;

    stack_struct->left_canary_position  = nullptr;
    stack_struct->right_canary_position = nullptr;
    stack_struct->data = nullptr;

    free(stack_struct->stack_pointer);
    stack_struct->stack_pointer = nullptr;
}

int StackSqrt(Stack* stack_struct) // (CHECKED) Gets the root of the value
{
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }

    if(check_is_positive(stack_struct->data[stack_struct->next_empty_cell - 1]) == IS_ZERO)
    {
        stack_struct->data[stack_struct->next_empty_cell - 1] = 0;
    }
    else if(check_is_positive(stack_struct->data[stack_struct->next_empty_cell - 1]) == IS_NEGATIVE)
    {
        stack_struct->error_code = ERR_SQRT_FROM_NEGATIVE;
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }
    stack_struct->data[stack_struct->next_empty_cell - 1] = sqrt(stack_struct->data[stack_struct->next_empty_cell - 1]);
    Calculate_hash(stack_struct);

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }
    return RETURN_OK;
}

int StackOut(Stack * stack_struct) // (CHECKED) Prints the stack's current structure in the console
{   
    printf("\nLEFT_CANARY: = %ld\n", *(stack_struct->left_canary_position));
    for(size_t i = 0; i < stack_struct->capacity; i++) 
    {
        printf("data[%ld] = %f\n", i, stack_struct->data[i]);
    }
    printf("RIGHT_CANARY: = %ld\n\n", *(stack_struct->right_canary_position));
    return RETURN_OK;
}

int StackAdd(Stack* stack_struct) // (CHECKED) Adds the entered value to next empty memory cell of the stack
{   
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }

    stack_struct->data[stack_struct->next_empty_cell - 2] = stack_struct->data[stack_struct->next_empty_cell - 2] + stack_struct->data[stack_struct->next_empty_cell - 1];
    stack_struct->data[stack_struct->next_empty_cell - 1] = POISON_VALUE;
    stack_struct->next_empty_cell--;
    Calculate_hash(stack_struct);

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }
    return RETURN_OK;
}

int StackMul(Stack* stack_struct) // (CHECKED) Multiplies two values of the stack
{   
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }

    stack_struct->data[stack_struct->next_empty_cell - 2] = stack_struct->data[stack_struct->next_empty_cell - 1] * stack_struct->data[stack_struct->next_empty_cell - 2];
    stack_struct->data[stack_struct->next_empty_cell - 1] = POISON_VALUE;
    stack_struct->next_empty_cell--;
    Calculate_hash(stack_struct);

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }
    return RETURN_OK;
}

int StackSub(Stack* stack_struct) // (CHECKED) Substracts one value of the stack from another one
{   
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }

    stack_struct->data[stack_struct->next_empty_cell - 2] = stack_struct->data[stack_struct->next_empty_cell - 2] - stack_struct->data[stack_struct->next_empty_cell - 1];
    stack_struct->data[stack_struct->next_empty_cell - 1] = POISON_VALUE;
    stack_struct->next_empty_cell--;
    Calculate_hash(stack_struct);

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }
    return RETURN_OK;
}

int StackDiv(Stack* stack_struct) // (CHECKED) Divides the preceding element by the last elemcapacityent of the stack
{   
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }

    if(check_is_positive(stack_struct->data[stack_struct->next_empty_cell - 1]) == IS_ZERO)
    {
        stack_struct->error_code = ERR_DIV_TO_ZERO;
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }
    stack_struct->data[stack_struct->next_empty_cell - 2] = stack_struct->data[stack_struct->next_empty_cell - 2] / stack_struct->data[stack_struct->next_empty_cell - 1];
    stack_struct->data[stack_struct->next_empty_cell - 1] = POISON_VALUE;
    stack_struct->next_empty_cell--;
    Calculate_hash(stack_struct);

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }
    return RETURN_OK;
}

int StackPush(Stack* stack_struct, stack_type push_value) // (CHECKED) Gets the value and pushes in to the stack
{   
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }

    stack_struct->data[stack_struct->next_empty_cell++] = push_value; 
    stack_struct->hash += push_value; // Сalculating new hash value

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }
    return RETURN_OK;
}

stack_type StackPop(Stack* stack_struct) // (CHECKED) Deletes the value from the stack
{   
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return POISON_VALUE;
    }

    stack_type poped_value = stack_struct->data[stack_struct->next_empty_cell - 1];
    stack_struct->data[stack_struct->next_empty_cell - 1] = POISON_VALUE;
    stack_struct->next_empty_cell--;
    stack_struct->hash = stack_struct->hash - poped_value; // Calculating new hash value

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return POISON_VALUE;
    }
    return poped_value;
}

int check_is_positive(double value) // CHECKED
{
    if((fabs(value - fabs(value)) < EPS) && (fabs(value) > EPS))
    {
        return IS_POSITIVE;
    }
    else if(fabs(value) <= EPS)
    {
        return IS_ZERO;
    }
    return IS_NEGATIVE;
}

int StackRealocUp(Stack* stack_struct) // (CHECKED) Increases the capacity of the stack, reallocs data
{   
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }

    if(stack_struct->next_empty_cell == stack_struct->capacity)
    {   
        stack_struct->capacity *= 2;
        stack_struct->stack_pointer = realloc(stack_struct->stack_pointer, stack_struct->capacity * sizeof(stack_type) + 2 * sizeof(size_t)); 

        if(stack_struct->stack_pointer == nullptr)
        {
            stack_struct->error_code = ERR_TO_REALLOC_UP;
            StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
            ERROR_MESSAGE(stderr, stack_struct->error_code)
            return stack_struct->error_code;
        }

        stack_struct->left_canary_position = (size_t*)stack_struct->stack_pointer;
        stack_struct->data = (stack_type*)(stack_struct->left_canary_position + 1);
        stack_struct->right_canary_position = (size_t*)(stack_struct->data + stack_struct->capacity);

        for(size_t i = stack_struct->next_empty_cell; i < stack_struct->capacity ; i++)
        {
            stack_struct->data[i] = POISON_VALUE;
        }

        stack_struct->left_canary_position[0]  = CANARY;
        stack_struct->right_canary_position[0] = CANARY;
    }

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }
    return RETURN_OK;
}

int StackRealocDown(Stack* stack_struct) // (CHECKED) Decreases the capacity of the stack, reallocs data
{   
    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }

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

        stack_struct->left_canary_position[0]  = CANARY;
        stack_struct->right_canary_position[0] = CANARY;
    }

    StackCheck(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }
    return RETURN_OK;
}


