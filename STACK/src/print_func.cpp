#include "stack.h"

void StackDump(Stack* st, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE) // outputs the data to the LOG.txt about the stack
{
    FILE *dump_log = fopen(LOG_FILE_NAME, "a+");

    if (dump_log == nullptr)
    {
        printf("ERROR: %s cannot be openned", LOG_FILE_NAME);
        st->error_code = ERR_OPEN_DUMP_FILE;
        StackDtor(st);
        exit(ERR_OPEN_DUMP_FILE);
    }
    else
    {   
        fprintf(dump_log, "-------------------START OF STACK DUMP------------------------\n\n");
        fprintf(dump_log, "Left canary address = %p\n", st->left_canary_position);
        fprintf(dump_log, "Data address = %p\n", st->data);
        fprintf(dump_log, "Right canary address = %p\n", st->right_canary_position);
        fprintf(dump_log, "Stack capacity = %ld\n", st->capacity);
        fprintf(dump_log, "Stack next_empty_cell = %ld\n\n", st->next_empty_cell);
        fprintf(dump_log, "Stack hash = %d\n\n", st->hash);

        fprintf(dump_log, "Stack error code = %ld (%s)\n", st->error_code, Enum_to_string(st->error_code)); // check
        fprintf(dump_log, "Called from dump_log: %s\n", __FILE__);
        fprintf(dump_log, "Called error function name: %s\n", FUNCT_NAME);
        fprintf(dump_log, "Called from line: %d\n", FUNCT_LINE);    
        fprintf(dump_log, "Called from dump_log: %d\n", FUNCT_FILE);  
        fprintf(dump_log, "Date when was called: %s\n", __DATE__);
        fprintf(dump_log, "Time when was called: %s\n\n", __TIME__);

        fprintf(dump_log, "LEFT CANARY = %ld\n", st->left_canary_position[0]);
        for(int i = 0; i < st->capacity; i++)
        {
                fprintf(dump_log, "data[%d] = %d", i, st->data[i]);
                fprintf(dump_log, "\t address %p\n", st->data + i);
        }
        fprintf(dump_log, "RIGHT CANARY = %ld\n", st->right_canary_position[0]);
        fprintf(dump_log, "--------------------END OF STACK DUMP--------------------------\n\n");
    }

    if(fclose(dump_log) == EOF)
    {
        printf("ERROR: %s cannot be closed", LOG_FILE_NAME);
        st->error_code = ERR_CLOSE_DUMP_FILE;
        StackDtor(st);
        exit(ERR_CLOSE_DUMP_FILE);
    }
}

void StackPrint(Stack* st) // (OK) (DEBUG ONLY) Prints the stack's current structure in the console
{   
    FILE* Action_log_stack = fopen(ACTION_LOG_NAME, "a+");

    if(Action_log_stack == nullptr)
    {
        printf("ERROR: %s cannot be openned", ACTION_LOG_NAME);
        st->error_code = ERR_OPEN_ACTION_LOG;
        StackDtor(st);
        exit(ERR_OPEN_ACTION_LOG);
    }

    fprintf(Action_log_stack, "\n");
    fprintf(Action_log_stack, "LEFT_CANARY: = %ld\n", *(st->left_canary_position));
    for(size_t i = 0; i < st->capacity; i++) 
    {
        fprintf(Action_log_stack, "data[%ld] = %d\n", i, st->data[i]);
    }
    fprintf(Action_log_stack,"RIGHT_CANARY: = %ld\n\n", *(st->right_canary_position));

    if(fclose(Action_log_stack) == EOF)
    {
        printf("ERROR: %s cannot be closed", ACTION_LOG_NAME);
        st->error_code = ERR_CLOSE_ACTION_LOG;
        StackDtor(st);
        exit(ERR_CLOSE_ACTION_LOG);
    }
}