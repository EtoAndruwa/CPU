#include "CPU.h"

size_t cpu_ctor(CPU* CPU, Stack* Stack)
{
    size_t error_code = StackCtor(Stack, STACK_SIZE);
    if(error_code != 0)
    {
        return error_code;
    }

    CPU->stack = Stack;
    CPU->error_code = CPU_OK;

    fill_with_poison(CPU->reg, REG_NUM);

    for(size_t i = 0; i < RAM_SIZE; i++)
    {
        CPU->ram[i] = 'O' * 100;
    }
}

void cpu_dtor(CPU* CPU)
{
    dump_cpu(CPU,FUNC_NAME, FUNC_LINE, FUNC_FILE);

    StackDtor(CPU->stack);
    CPU->stack = nullptr;

    fill_with_poison(CPU->reg, REG_NUM);    
    fill_with_poison(CPU->ram, RAM_SIZE);

    free(CPU->bin_code);
    CPU->bin_code = nullptr;

    CPU->error_code = 0;
}

void call_stack_ctor_dtor(Call_stack* Call_stack)
{
    fill_with_poison(Call_stack->call_stack, CALL_STACK_SIZE);
    Call_stack->cur_index = 0;
}

void fill_with_poison(stack_type* arr_ptr, size_t size_arr)
{
    for(size_t i = 0; i < size_arr; i++)
    {
        arr_ptr[i] = POISON_VALUE;
    }
}
