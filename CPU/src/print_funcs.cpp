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
        printf("%c ", (CPU->ram[i] / 100));
    }
    printf("\n\n----------------SCREEN-----------------\n\n");
}