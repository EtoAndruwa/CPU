#include  "stack.h"

int StackLogic(Stack* stack_struct, char* command, stack_type push_value) // (OK) Calls other functions depending on the entered command 
{
    if(strcmp(command, "PUSH") == 0)
    {   
        StackRealocUp(stack_struct);
        return StackPush(stack_struct, push_value);
    }
    else if(strcmp(command, "POP") == 0)
    {   
        StackRealocDown(stack_struct);
        return StackPop(stack_struct);
    }
    else if(strcmp(command, "ADD") == 0)
    {   
        StackRealocDown(stack_struct);
        return StackAdd(stack_struct);
    }
    else if(strcmp(command, "SUB") == 0)
    {   
        StackRealocDown(stack_struct);
        return StackSub(stack_struct);
    }
    else if(strcmp(command, "MUL") == 0)
    {   
        StackRealocDown(stack_struct);
        return StackMul(stack_struct);
    }
    else if(strcmp(command, "DIV") == 0)
    {   
        StackRealocDown(stack_struct);
        return StackDiv(stack_struct);
    }
    else if(strcmp(command, "SQRT") == 0)
    {   
        StackRealocDown(stack_struct);
        return StackSqrt(stack_struct);
    }
    else
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
        return stack_struct->error_code;
    }
}

void StackConsoleWork(Stack* stack_struct) // (OLD COMMAND)
{
    char* command = (char*)calloc(MAX_LINE_COMMAND, sizeof(char));

    if(command == nullptr)
    {
        stack_struct->error_code = ERR_TO_CALLOC_CMD_STR;
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        StackDtor(stack_struct);
        exit(ERR_TO_CALLOC_CMD_STR);
    }
    stack_type push_value = 0;

    while(strcmp(command, "HLT") != 0)
    {
        if(scanf("%4s", command) == 0)
        {
            printf("\nInvalid command, try again!\n");
            continue;
        }

        if(strcmp(command, "PUSH") == 0)
        {
            if(scanf(" %d", &push_value) == 0)
            {
                printf("\nInvalid argument, try again!\n");
                continue;
            }
        }
        StackLogic(stack_struct, command, push_value);
    }

    free(command);
}

void StackCheck(Stack* stack_struct, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE) // (CHECKED) Checks the stack for the possible errors
{   
    if(stack_struct->data == nullptr)
    {
        stack_struct->error_code = ERR_NULL_DATA;
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
    }
    else if(stack_struct->next_empty_cell > stack_struct->capacity)
    {
        stack_struct->error_code = ERR_OUT_OF_STACK_RIGHT;
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
    }
    else if(stack_struct->next_empty_cell < 0)
    {   
        stack_struct->error_code = ERR_OUT_OF_STACK_LEFT;
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
    }
    else if(stack_struct->left_canary_position[0] != CANARY)
    {   
        stack_struct->error_code = ERR_LEFT_CANARY_DEAD;
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code) 
    }
    else if(stack_struct->right_canary_position[0] != CANARY)
    {   
        stack_struct->error_code = ERR_RIGHT_CANARY_DEAD;
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
    }
    else if(stack_struct->hash != Get_cur_value_of_hash(stack_struct))   
    {
        stack_struct->error_code = ERR_HASH_CHANGED;
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
    }
    else if(stack_struct->error_code != STACK_IS_OK)
    {
        StackDump(stack_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, stack_struct->error_code)
    }
}
