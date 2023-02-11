#include "CPU.h"

void check_code_file()
{

}

void push_reg(CPU* CPU, size_t reg_code, stack_type push_value)
{
    switch (reg_code)
    {
    case 21:
        CPU->ax = push_value;
        break;
    case 22:
        CPU->ax = push_value;
        break;
    case 23:
        CPU->bx = push_value;
        break;
    case 24:
        CPU->cx = push_value;
        break;
    case 25:
        CPU->rax = push_value;
        break;
    case 26:
        CPU->rbx = push_value;
        break;
    case 27:
        CPU->rcx = push_value;
        break;
    default:
        break;
    }
}

void pop_reg(CPU* CPU, size_t reg_code)
{

}

void print_regs_val(CPU* CPU)
{   
    printf("Reg values\n");
    printf("\nax: %f\n", CPU->ax);
    printf("bx: %f\n", CPU->bx);
    printf("cx: %f\n", CPU->cx);
    printf("rax: %f\n", CPU->rax);
    printf("rbx: %f\n", CPU->rbx);
    printf("rcx: %f\n", CPU->rcx);
}
