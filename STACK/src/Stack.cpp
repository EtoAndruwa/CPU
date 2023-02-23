#include  "stack.h"

void StackLogic(Stack* st, char* command, stack_type push_value) // (OK) Calls other functions depending on the entered command 
{
    if(strcmp(command, "PUSH") == 0)
    {   
        StackRealocUp(st);
        StackPush(st, push_value);
    }
    else if(strcmp(command, "POP") == 0)
    {   
        StackRealocDown(st);
        StackPop(st);
    }
    else if(strcmp(command, "ADD") == 0)
    {   
        StackRealocDown(st);
        StackAdd(st);
    }
    else if(strcmp(command, "SUB") == 0)
    {   
        StackRealocDown(st);
        StackSub(st);
    }
    else if(strcmp(command, "MUL") == 0)
    {   
        StackRealocDown(st);
        StackMul(st);
    }
    else if(strcmp(command, "DIV") == 0)
    {   
        StackRealocDown(st);
        StackDiv(st);
    }
    else if(strcmp(command, "SQRT") == 0)
    {   
        StackRealocDown(st);
        StackSqrt(st);
    }
    else
    {
        printf("\nInvalid command, try again!\n");
    }
}

void StackConsoleWork(Stack* st) // (OK) Supports the work of the program until 'HLT' will be entered 
{
    char* command = (char*)calloc(MAX_LINE_COMMAND, sizeof(char));

    if(command == nullptr)
    {
        st->error_code = ERR_TO_CALLOC_CMD_STR;
        StackDump(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        StackDtor(st);
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
        StackLogic(st, command, push_value);
        //StackOut(st);
    }

    free(command);
    command = nullptr;
}

void StackCheck(Stack* st, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE) // (OK) Checks the stack for the possible errors
{   
    if(st->data == nullptr)
    {
        st->error_code = ERR_NULL_DATA;
        StackDump(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        StackDtor(st);
        exit(ERR_NULL_DATA);
    }
    else if(st->next_empty_cell > st->capacity)
    {
        st->error_code = ERR_OUT_OF_STACK_RIGHT;
        StackDump(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        StackDtor(st);
        exit(ERR_OUT_OF_STACK_RIGHT);
    }
    else if(st->next_empty_cell < 0)
    {   
        st->error_code = ERR_OUT_OF_STACK_LEFT;
        StackDump(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        StackDtor(st);
        exit(ERR_OUT_OF_STACK_LEFT);
    }
    else if(st->left_canary_position[0] != CANARY)
    {   
        st->error_code = ERR_LEFT_CANARY_DEAD;
        StackDump(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        StackDtor(st);
        exit(ERR_LEFT_CANARY_DEAD);
    }
    else if(st->right_canary_position[0] != CANARY)
    {   
        st->error_code = ERR_RIGHT_CANARY_DEAD;
        StackDump(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        StackDtor(st);
        exit(ERR_RIGHT_CANARY_DEAD);
    }
    else if(st->hash != Get_cur_value_of_hash(st))   
    {
        st->error_code = ERR_HASH_CHANGED;
        StackDump(st, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        StackDtor(st);
        exit(ERR_HASH_CHANGED);
    }
}

