#include "CPU.h"

void print_cpu_data(CPU* CPU)
{
    printf("stack_type* memmory: %p\n", CPU->ram);
    printf("error_code: %ld (%s)\n", CPU->error_code, convert_enum_cpu(CPU->error_code));

    printf("\nREGS:\n");
    for(size_t i = 0; i < REG_NUM; i++)
    {
        printf("reg[%ld] = %d\n", ax + i, CPU->reg[i]);
    }

    printf("\nR_REGS:\n");
    for(size_t i = 0; i < R_REG_NUM; i++)
    {
        printf("r_reg[%ld] = %d\n", rax + i, CPU->r_reg[i]);
    }
}

void print_ram(CPU* CPU)
{
    printf("\n-----RAM_START-----\n");
    for(size_t i = 0; i < RAM_SIZE; i++)
    {
        printf("RAM[%ld]: %d\n", i, CPU->ram[i]);
    }
    printf("-----RAM_END-----\n");
}

void print_call_stack(Call_stack* Call_stack)
{
    printf("\n---CALL_STACK---\n");
    for(size_t i = 0; i < CALL_STACK_SIZE; i++)
    {
        printf("Call_stack[%ld]: %d\n", i, Call_stack->call_stack[i]);
    }
    printf("---CALL_STACK---\n");
}

void print_ram_screen(CPU* CPU)
{
    printf("\n----------------SCREEN-----------------\n");
    for(size_t i = 0; i < RAM_SIZE; i++)
    {
        if((i % SCREEN_SIZE) == 0)
        {
            printf("\n");
        }
        if((CPU->ram[i] / MUL_CONST) == (int)'X')
        {
            printf("\033[97m\033[107m%c \033[0m", (CPU->ram[i] / MUL_CONST));
        }
        else
        {
            printf("\033[30m\033[40m%c \033[0m", (CPU->ram[i] / MUL_CONST));
        }
    }
    printf("\n\n----------------SCREEN-----------------\n\n");
}

void dump_cpu(CPU* CPU, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE)
{
    FILE* dump_log = fopen(DUMP_NAME, "w");

    if (dump_log == nullptr)
    {
        printf("ERROR: %s cannot be openned", DUMP_NAME);
        CPU->error_code = ERR_OPEN_DUMP_FILE;
        cpu_dtor(CPU);
        exit(ERR_OPEN_DUMP_FILE);
    }
    else
    {   
        fprintf(dump_log, "\n------------STRUCT_DATA------------\n");
        fprintf(dump_log, "Error code: %ld (%s)\n", CPU->error_code, convert_enum_cpu(CPU->error_code));
        fprintf(dump_log, "Current command: %ld\n", CPU->curr_cmd);
        fprintf(dump_log, "Number of commands: %d\n", *CPU->num_bin_cmd);
        fprintf(dump_log, "Pointer to the bin code: %p\n", CPU->bin_code);
        fprintf(dump_log, "Pointer to the stack: %p\n", CPU->stack);
        fprintf(dump_log, "------------STRUCT_DATA------------\n");

        fprintf(dump_log, "\n------------DUMP_DATA------------\n");
        fprintf(dump_log, "File name: %s\n", FUNCT_FILE);
        fprintf(dump_log, "Function name: %s\n", FUNCT_NAME);
        fprintf(dump_log, "Line: %d\n", FUNCT_LINE);
        fprintf(dump_log, "Time: %s\n", __TIME__);
        fprintf(dump_log, "Date: %s\n", __DATE__);
        fprintf(dump_log, "-------------DUMP_DATA-------------\n");

        fprintf(dump_log, "\n------------REGS------------\n");
        for(size_t i = 0; i < REG_NUM; i++)
        {
            fprintf(dump_log, "REG[%ld] = %d\n", i, CPU->reg[i]);
        }
        fprintf(dump_log, "------------REGS------------\n");

        fprintf(dump_log, "\n------------R_REGS------------\n");
        for(size_t i = 0; i < R_REG_NUM; i++)
        {
            fprintf(dump_log, "R_REG[%ld] = %d\n", i, CPU->r_reg[i]);
        }
        fprintf(dump_log, "------------R_REGS------------\n");

        fprintf(dump_log, "\n------------STACK------------\n");
        for(size_t i = 0; i < CPU->stack->capacity; i++)
        {
            fprintf(dump_log, "STACK[%ld] = %d\n", i, CPU->stack->data[i]);
        }
        fprintf(dump_log, "------------STACK------------\n");  
    
        fprintf(dump_log, "\n----------------SCREEN-----------------\n");
        for(size_t i = 0; i < RAM_SIZE; i++)
        {
            if((i % SCREEN_SIZE) == 0)
            {
                fprintf(dump_log, "\n");
            }
            fprintf(dump_log, "%c ", (CPU->ram[i] / 100));
        }
        fprintf(dump_log, "\n\n----------------SCREEN-----------------\n");

        fprintf(dump_log, "\n------------RAM------------\n");
        for(size_t i = 0; i < RAM_SIZE; i++)
        {
            fprintf(dump_log, "RAM[%ld] = %d\n", i, CPU->ram[i]);
        }
        fprintf(dump_log, "------------RAM------------\n\n");  
    }

    if(fclose(dump_log) == EOF)
    {
        printf("ERROR: %s cannot be closed", DUMP_NAME);
        CPU->error_code = ERR_CLOSE_DUMP_FILE;
        cpu_dtor(CPU);
        exit(ERR_CLOSE_DUMP_FILE);
    }
}