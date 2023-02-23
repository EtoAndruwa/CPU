#include "CPU.h"

void cpu_ctor(CPU* CPU, Stack* Stack)
{
    StackCtor(Stack, STACK_SIZE);
    CPU->stack = Stack;
    CPU->error_code = CPU_OK;

    fill_with_posion(CPU->reg, REG_NUM);
    fill_with_posion(CPU->r_reg, R_REG_NUM);

    for(size_t i = 0; i < RAM_SIZE; i++)
    {
        CPU->ram[i] = 'O' * 100;
    }
}

void cpu_dtor(CPU* CPU)
{
    dump_cpu(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    StackDtor(CPU->stack);
    CPU->stack = nullptr;

    fill_with_posion(CPU->reg, REG_NUM);
    fill_with_posion(CPU->r_reg, R_REG_NUM);
    fill_with_posion(CPU->ram, RAM_SIZE);

    if(CPU->bin_code != nullptr)
    {
        free(CPU->bin_code);
        CPU->bin_code = nullptr;
    }
    else
    {
        CPU->error_code = ERR_BIN_NULL_BEF_DTOR;
        printf("Error code: %d (%s)\n", ERR_BIN_NULL_BEF_DTOR, convert_enum_cpu(ERR_BIN_NULL_BEF_DTOR));
        exit(ERR_BIN_NULL_BEF_DTOR);
    }
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
