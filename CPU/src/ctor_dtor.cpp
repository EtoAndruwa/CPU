#include "CPU.h"

void cpu_ctor(CPU* CPU, Stack* Stack)
{
    StackCtor(Stack, STACK_SIZE);
    CPU->stack = Stack;
    fill_with_posion(CPU->reg, REG_NUM);
    fill_with_posion(CPU->r_reg, R_REG_NUM);

    for(size_t i = 0; i < RAM_SIZE; i++)
    {
        CPU->ram[i] = 'O' * 100;
    }

    CPU->error_code = CPU_OK;
}

void cpu_dtor(CPU* CPU)
{
    StackDtor(CPU->stack);
    CPU->stack = nullptr;

    fill_with_posion(CPU->reg, REG_NUM);
    fill_with_posion(CPU->r_reg, R_REG_NUM);
    fill_with_posion(CPU->ram, RAM_SIZE);

    free(CPU->bin_code);
    CPU->bin_code = nullptr;
    CPU->error_code = 0;
}

void call_stack_ctor_dtor(Call_stack* Call_stack)
{
    fill_with_posion(Call_stack->call_stack, CALL_STACK_SIZE);
    Call_stack->cur_index = 0;
}

void fill_with_posion(stack_type* arr_ptr, size_t size_arr)
{
    for(size_t i = 0; i < size_arr; i++)
    {
        arr_ptr[i] = POISON_VALUE;
    }
}
