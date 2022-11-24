#include "CPU.h"

#define FUNC_NAME __func__
#define FUNC_LINE __LINE__  

void StackCtor(Stack * st)
{   
    st->capacity = STACK_CAPACITY + 2; 
    st->size = 1;
    st->data = (stack_type *)calloc(st->capacity, sizeof(stack_type));

    st->left_canary_position = 0;
    st->right_canary_position = st->capacity - 1;
    st->data[0] = CANARY;
    st->data[st->capacity-1] = CANARY;
    
    StackCheck(st, FUNC_NAME, FUNC_LINE);
    for(int  i = 1; i < st->capacity-1; i++)
    {   
       st->data[i] = POISON_VALUE;
    }

    // *(st->data + st->capacity) = CANARY;
    // *((st->data) - 1 * sizeof(stack_type)) = CANARY;
    StackCheck(st, FUNC_NAME, FUNC_LINE);
}
    
void StackPush(Stack * st, stack_type push_value)
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE);
    st->data[st->size++] = push_value; 
    StackCheck(st, FUNC_NAME, FUNC_LINE);
}

stack_type StackPop(Stack * st)
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE);
    stack_type temp = st->data[st->size - 1];
    st->data[st->size - 1] = POISON_VALUE;
    st->size--;
    StackCheck(st, FUNC_NAME, FUNC_LINE);
    return temp;
}

void StackDump(Stack * st, const char * FUNCT_NAME, int FUNCT_LINE)
{
    FILE *file = fopen("log.txt", "a+");
    if (file == NULL)
    {
        printf("ERROR: log file cannot be open");
    }
    else
    {
        fprintf(file, "-------------------START OF STACK DUMP------------------------\n\n");
        fprintf(file, "Stack * data = %p\n", st->data);
        fprintf(file, "Stack capacity = %ld\n", st->capacity);
        fprintf(file, "Stack size = %ld\n\n", st->size);
        fprintf(file, "Left canary position = %ld\n", st->left_canary_position);
        fprintf(file, "Right canary position = %ld\n\n", st->right_canary_position);

        fprintf(file, "Stack error code = %ld\n", st->error_code);
        fprintf(file, "Called from file: %s\n", __FILE__);
        fprintf(file, "Called error function name: %s\n", FUNCT_NAME);
        fprintf(file, "Called from line: %d\n", FUNCT_LINE);    
        fprintf(file, "Date when was called: %s\n", __DATE__);
        fprintf(file, "Time when was called: %s\n\n", __TIME__);


        // fprintf(file, "data[-1] = %.3lf", *((st->data) - 1 * sizeof(stack_type)));
        // fprintf(file, "\t address %p\n", ((st->data) - 1));
        for(int i = 0; i < st->capacity; i++)
        {
            if(i == st->capacity - 1)
            {
                fprintf(file, "data[%d] = %.3lf", i, st->data[i]);
                fprintf(file, "\t address %p\n\n", st->data + i);
            }   
            else
            {
                fprintf(file, "data[%d] = %.3lf", i, st->data[i]);
                fprintf(file, "\t address %p\n", st->data + i);
            }
        }
        // fprintf(file, "data[+1] = %.3lf", *(st->data + st->capacity));
        // fprintf(file, "\t address %p\n\n", st->data + st->capacity);
        fprintf(file, "--------------------END OF STACK DUMP--------------------------\n\n");
    }
    fclose(file);
}

void StackMul(Stack * st)
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE);
    st->data[st->size - 2] = st->data[st->size - 1] * st->data[st->size - 2];
    st->data[st->size - 1] = POISON_VALUE;
    st->size--;
    StackCheck(st, FUNC_NAME, FUNC_LINE);
}

void StackSub(Stack * st)
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE);
    st->data[st->size - 2] = st->data[st->size - 2] - st->data[st->size - 1];
    st->data[st->size - 1] = POISON_VALUE;
    st->size--;
    StackCheck(st, FUNC_NAME, FUNC_LINE);
}

void StackDiv(Stack * st)
{   
    if(fabs(st->data[st->size - 1] - 0.0) > EPS)
    {
        StackCheck(st, FUNC_NAME, FUNC_LINE);
        st->data[st->size - 2] = (st->data[st->size - 2]) / (st->data[st->size - 1]);
        st->data[st->size - 1] = POISON_VALUE;
        st->size--;
        StackCheck(st, FUNC_NAME, FUNC_LINE);
    }
    else
    {
        st->error_code = ERR_DIV_ZERO;
        StackDump(st, FUNC_NAME, FUNC_LINE);
        StackDtor(st);
        abort();
    }
}

void StackPrint(Stack * st)
{   
    // printf("data[-1] = %.3lf", *((st->data) - 1 * sizeof(stack_type)));
    // printf("\t address %p\n", ((st->data) - 1));
    printf("\n");
    for(int i = 0; i < st->capacity; i++)
    {
        if(i == st->capacity - 1)
        {
            printf("data[%d] = %.3lf\n\n", i, st->data[i]);
            //printf("\t address %p\n\n", st->data + i);
        }
        else
        {
            printf("data[%d] = %.3lf\n", i, st->data[i]);
            //printf("\t address %p\n", st->data + i);
        }
    }
    // printf("data[+1] = %.3lf", *(st->data + st->capacity));
    // printf("\t address %p\n\n", st->data + st->capacity);
}

void StackAdd(Stack * st)
{   
    StackCheck(st, FUNC_NAME, FUNC_LINE);
    st->data[st->size - 2] = (st->data[st->size - 2]) + (st->data[st->size - 1]);
    st->data[st->size - 1] = POISON_VALUE;
    st->size--;
    StackCheck(st, FUNC_NAME, FUNC_LINE);
}

void StackLogic(Stack * st, int command_id, stack_type push_value)
{
    switch (command_id)
    {
        case 1:
            StackRealocUp(st);
            StackPush(st, push_value);
            break;
        case 2:
            StackRealocDown(st);
            StackPop(st);
            break;
        case 3:
            StackRealocDown(st);
            StackAdd(st);
            break;
        case 4:
            StackRealocDown(st);
            StackSub(st);
            break;
        case 5:
            StackRealocDown(st);
            StackMul(st);
            break;
        case 6:
            StackRealocDown(st);
            StackDiv(st);
            break;
        default:
            break;
    }
}

void StackConsoleWork(Stack * st, FILE * test_code)
{
    stack_type push_value = 0;
    int command_id = 0;
    do
    {
        fscanf(test_code, "%d", &command_id);
        if(command_id == 1)
        {
            fscanf(test_code, " %lf", &push_value);
        }
        StackLogic(st, command_id, push_value);
        StackPrint(st);
    }
    while(command_id != 0)    ;
    fclose(test_code);
}

void StackCheck(Stack * st, const char * FUNCT_NAME, int FUNCT_LINE)
{   
    if(st->data == nullptr)
    {
        st->error_code = ERR_NULL_DATA;
        StackDump(st, FUNCT_NAME, FUNCT_LINE);
        StackDtor(st);
        abort();
    }
    else if(st->size > st->capacity)
    {
        st->error_code = ERR_OUT_OF_STACK_RIGHT;
        StackDump(st, FUNCT_NAME, FUNCT_LINE);
        StackDtor(st);
        abort();
    }
    else if(st->size < 0)
    {   
        st->error_code = ERR_OUT_OF_STACK_LEFT;
        StackDump(st, FUNCT_NAME, FUNCT_LINE);
        StackDtor(st);;
        abort();
    }
    // else if(*((st->data) - 1 * sizeof(stack_type)) != CANARY)
    // {   
    //     st->error_code = ERR_LEFT_BUFFER_CANARY_DEAD;
    //     StackDump(st, FUNCT_NAME, FUNCT_LINE);
    //     StackDtor(st);
    //     abort();
    // }
    // else if(*(st->data + st->capacity) != CANARY)
    // {   
    //     st->error_code = ERR_RIGHT_BUFFER_CANARY_DEAD;
    //     StackDump(st, FUNCT_NAME, FUNCT_LINE);
    //     StackDtor(st);
    //     abort();
    // }
    else if(st->data[0] != CANARY)
    {   
        st->error_code = ERR_LEFT_CANARY_DEAD;
        StackDump(st, FUNCT_NAME, FUNCT_LINE);
        StackDtor(st);
        abort();
    }
    else if(st->data[st->capacity-1] != CANARY)
    {   
        st->error_code = ERR_RIGHT_CANARY_DEAD;
        StackDump(st, FUNCT_NAME, FUNCT_LINE);
        StackDtor(st);
        abort();
    }       
}

void StackDtor(Stack * st)
{
    for(int  i = 1; i < st->capacity - 1; i++)
    {
        st->data[i] = POISON_VALUE;
    }
    //StackPrint(st);
    st->capacity = POISON_VALUE;
    st->size = POISON_VALUE;
    st->right_canary_position = POISON_VALUE;
    st->left_canary_position = POISON_VALUE;
    free(st->data);
    st->data = nullptr;
}

void StackRealocUp(Stack * st)
{
    if(st->size == (st->capacity -1))
    {   
        // printf("Old capacity PUSH: %ld\n", st->capacity);
        st->data[st->capacity - 1] = POISON_VALUE;
        size_t old_right_canary_post = st->right_canary_position;
        st->capacity *= 2;
        // printf("New capacity PUSH: %ld\n", st->capacity);

        st->data = (stack_type *)realloc(st->data, st->capacity * sizeof(stack_type));

        st->data[st->capacity - 1] = CANARY;
        st->right_canary_position = st->capacity - 1;

        for(size_t  i = old_right_canary_post; i < st->right_canary_position; i++)
        {   
        st->data[i] = POISON_VALUE;
        }

        StackCheck(st, FUNC_NAME, FUNC_LINE);
    }
}

void StackRealocDown(Stack * st)
{
    if((st->size <= (st->capacity - 2) / 2) && (st->capacity > 3))
        {   
            st->data[st->capacity - 1] = POISON_VALUE;
            // printf("Old capacity POP: %ld\n", st->capacity);    
            st->capacity = st->capacity - ((st->capacity -1 )/2);
            // printf("New capacity POP: %ld\n", st->capacity);

            st->data = (stack_type *)realloc(st->data, st->capacity * sizeof(stack_type));

            st->data[st->capacity - 1] = CANARY;
            st->right_canary_position = st->capacity - 1;
            StackCheck(st, FUNC_NAME, FUNC_LINE);
        }
}

void file_openning_check(Stack * st)
{   
    if (fopen("test_code.txt", "r") == 0)
    {
        printf("ERROR: unable to open assembly file \n");
        abort();
    }
    else
    {
        FILE * test_code = fopen("test_code.txt", "r");//opens file with text
        
        printf("OK\n");

        StackConsoleWork(st, test_code);
    }
}