#include "CPU.h"

void cpu_data_print(CPU* CPU)
{
    printf("stack_type* memmory: %p\n", CPU->memmory);
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
        printf("RAM[%ld]: %d\n", i, CPU->memmory[i]);
    }
    printf("-----RAM_END-----\n");
}