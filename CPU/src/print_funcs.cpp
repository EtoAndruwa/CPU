#include "CPU.h"

void print_cpu_data(CPU* CPU) // CHECKED
{
    printf("stack_type* memmory: %p\n", CPU->ram);
    printf("error_code: %d (%s)\n", CPU->error_code, convert_enum_cpu(CPU->error_code));

    printf("\nREGS:\n");
    for(size_t i = 0; i < REG_NUM; i++)
    {
        printf("reg[%ld] = %f\n", AX + i, CPU->reg[i]);
    }
}

void print_ram(CPU* CPU) // CHECKED
{
    printf("\n-----RAM_START-----\n");
    for(size_t i = 0; i < RAM_SIZE; i++)
    {
        printf("RAM[%ld]: %f\n", i, CPU->ram[i]);
    }
    printf("-----RAM_END-----\n");
}

void print_call_stack(Call_stack* Call_stack) // CHECKED
{
    printf("\n---CALL_STACK---\n");
    for(size_t i = 0; i < CALL_STACK_SIZE; i++)
    {
        printf("Call_stack[%ld]: %d\n", i, (int)Call_stack->call_stack[i]);
    }
    printf("---CALL_STACK---\n");
}

void print_ram_screen(CPU* CPU) // CHECKED
{
    printf("\n----------------SCREEN-----------------\n");
    for(size_t i = 0; i < RAM_SIZE; i++)
    {
        if((i % SCREEN_SIZE) == 0)
        {
            printf("\n");
        }
        if((int)(CPU->ram[i]) == (int)'X')
        {
            printf("\033[97m\033[107m%c \033[0m", (int)(CPU->ram[i]));
        }
        else
        {
            printf("\033[30m\033[40m%c \033[0m", (int)(CPU->ram[i]));
        }
    }
    printf("\n\n----------------SCREEN-----------------\n\n");
}

int dump_cpu(CPU* CPU, const char* func_name, int func_line, const char* func_file)
{
    FILE* dump_log = fopen(DUMP_NAME, "w");
    if(dump_log == nullptr)
    {
        CPU->error_code = ERR_OPEN_DUMP_FILE;
        ERROR_MESSAGE(stderr, CPU->error_code)
        return CPU->error_code;
    }
    fprintf(dump_log, "\n------------STRUCT_DATA------------\n");
    fprintf(dump_log, "Error code: %d (%s)\n", CPU->error_code, convert_enum_cpu(CPU->error_code));
    fprintf(dump_log, "Current command: %ld\n", CPU->curr_cmd);
    fprintf(dump_log, "Number of commands: %d\n", (int)CPU->num_bin_cmd[0]);
    fprintf(dump_log, "Pointer to the bin code: %p\n", CPU->bin_code);
    fprintf(dump_log, "Pointer to the stack: %p\n", CPU->stack);
    fprintf(dump_log, "------------STRUCT_DATA------------\n");

    fprintf(dump_log, "\n------------DUMP_DATA------------\n");
    fprintf(dump_log, "File name: %s\n", func_file);
    fprintf(dump_log, "Function name: %s\n", func_name);
    fprintf(dump_log, "Line: %d\n", func_line);
    fprintf(dump_log, "Time: %s\n", __TIME__);
    fprintf(dump_log, "Date: %s\n", __DATE__);
    fprintf(dump_log, "-------------DUMP_DATA-------------\n");

    fprintf(dump_log, "\n------------REGS------------\n");
    for(size_t i = 0; i < REG_NUM; i++)
    {
        fprintf(dump_log, "REG[%ld] = %f\n", i, CPU->reg[i]);
    }
    fprintf(dump_log, "------------REGS------------\n");

    fprintf(dump_log, "\n------------STACK------------\n");
    for(size_t i = 0; i < CPU->stack->capacity; i++)
    {
        fprintf(dump_log, "STACK[%ld] = %f\n", i, CPU->stack->data[i]);
    }
    fprintf(dump_log, "------------STACK------------\n");  

    fprintf(dump_log, "\n----------------SCREEN-----------------\n");
    for(size_t i = 0; i < RAM_SIZE; i++)
    {
        if((i % SCREEN_SIZE) == 0)
        {
            fprintf(dump_log, "\n");
        }
        fprintf(dump_log, "%c ", (int)(CPU->ram[i]));
    }
    fprintf(dump_log, "\n\n----------------SCREEN-----------------\n");

    fprintf(dump_log, "\n------------RAM------------\n");
    for(size_t i = 0; i < RAM_SIZE; i++)
    {
        fprintf(dump_log, "RAM[%ld] = %f\n", i, CPU->ram[i]);
    }
    fprintf(dump_log, "------------RAM------------\n\n");  

    if(fclose(dump_log) == EOF)
    {
        CPU->error_code = ERR_CLOSE_DUMP_FILE;
        ERROR_MESSAGE(stderr, CPU->error_code)
        return CPU->error_code;
    }
    return RETURN_OK;
}
