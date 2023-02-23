#include "CPU.h"

void push_ret(CPU* CPU, Call_stack* Call_stack, size_t index_to_jmp) 
{
    if((Call_stack->cur_index >= 0) && (Call_stack->cur_index < CALL_STACK_SIZE))
    {
        Call_stack->call_stack[Call_stack->cur_index] = index_to_jmp;
        Call_stack->cur_index++;
    }
    else
    {
        safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CALL_STACK_FULL);
    }
}

void jmp_flag(CPU* CPU, size_t index_to_jmp)
{
    CPU->curr_cmd = CPU->bin_code[index_to_jmp];
}   

void jmp_ret(CPU* CPU, Call_stack* Call_stack)
{
    if((Call_stack->cur_index == 0) && (Call_stack->call_stack[Call_stack->cur_index] != POISON_VALUE))
    {   
        CPU->curr_cmd = Call_stack->call_stack[Call_stack->cur_index];
        Call_stack->call_stack[Call_stack->cur_index] = POISON_VALUE;
    }
    else if(Call_stack->cur_index > 0)
    {   
        Call_stack->cur_index--;
        CPU->curr_cmd = Call_stack->call_stack[Call_stack->cur_index];
        Call_stack->call_stack[Call_stack->cur_index] = POISON_VALUE;    
    }
    else
    {
        safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CALL_STACK_EMPT);
    }
}

void push_reg(CPU* CPU, size_t reg_code) // From reg to stack
{   
    switch (reg_code)
    {
    case ax:
        StackPush(CPU->stack, CPU->reg[0]);
        break;
    case bx:
        StackPush(CPU->stack, CPU->reg[1]);
        break;
    case cx:
        StackPush(CPU->stack, CPU->reg[2]);
        break;
    case dx:
        StackPush(CPU->stack, CPU->reg[3]);
        break;
    case rax:
        StackPush(CPU->stack, CPU->r_reg[0]);
        break;
    case rbx:
        StackPush(CPU->stack, CPU->r_reg[1]);
        break;
    case rcx:
        StackPush(CPU->stack, CPU->r_reg[2]);
        break;
    default:
        safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INVALID_REG);
    }
}

void pop_reg(CPU* CPU, size_t reg_code) // From Stack to reg
{
    switch (reg_code)
    {
    case ax:
        CPU->reg[0] = StackPop(CPU->stack);
        break;
    case bx:
        CPU->reg[1] = StackPop(CPU->stack);
        break;
    case cx:
        CPU->reg[2] = StackPop(CPU->stack);
        break;
    case dx:
        CPU->reg[3] = StackPop(CPU->stack);
        break;
    case rax:
        CPU->r_reg[0] = StackPop(CPU->stack);
        break;
    case rbx:
        CPU->r_reg[1] = StackPop(CPU->stack);
        break;
    case rcx:
        CPU->r_reg[2] = StackPop(CPU->stack);
        break;
    default:
        safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INVALID_REG);
    }
}

void push_ram_val(CPU* CPU, size_t ram_index)
{
    if((ram_index < RAM_SIZE) && (ram_index >= 0))
    {
        StackPush(CPU->stack, CPU->ram[ram_index]);
    }
    else
    {
        safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
    }
}

void pop_ram_val(CPU* CPU, size_t ram_index)
{
    if((ram_index < RAM_SIZE) && (ram_index >= 0))
    {
        CPU->ram[ram_index] = StackPop(CPU->stack);
    }
    else
    {
        safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
    }
}

void push_ram_reg(CPU* CPU, size_t reg_id)
{
    switch (reg_id)
    {
    case ax:
        if((CPU->reg[0] / 100) >= RAM_SIZE)
        {
            safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
        }
        else
        {
            StackPush(CPU->stack, CPU->ram[CPU->reg[0] / 100]);
        }
        break;
    case bx:
        if((CPU->reg[1] / 100) >= RAM_SIZE)
        {
            safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
        }
        else
        {
            StackPush(CPU->stack, CPU->ram[CPU->reg[1] / 100]);
        }
        break;
    case cx:
        if((CPU->reg[2] / 100) >= RAM_SIZE)
        {
            safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
        }
        else
        {
            StackPush(CPU->stack, CPU->ram[CPU->reg[2] / 100]);
        }
        break;
    case dx:
        if((CPU->reg[3] / 100) >= RAM_SIZE)
        {
            safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
        }
        else
        {
            StackPush(CPU->stack, CPU->ram[CPU->reg[3] / 100]);
        }
        break;
    case rax:
        if((CPU->r_reg[0] / 100) >= RAM_SIZE)
        {
            safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
        }
        else
        {
            StackPush(CPU->stack, CPU->ram[CPU->r_reg[0] / 100]);
        }
        break;
    case rbx:
        if((CPU->r_reg[1] / 100) >= RAM_SIZE)
        {
            safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
        }
        else
        {
            StackPush(CPU->stack, CPU->ram[CPU->r_reg[1] / 100]);
        }
        break;
    case rcx:
        if((CPU->r_reg[2] / 100) >= RAM_SIZE)
        {
            safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
        }
        else
        {
            StackPush(CPU->stack, CPU->ram[CPU->r_reg[2] / 100]);
        }
        break;
    default:
        safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INVALID_REG);
    }
}

void pop_ram_reg(CPU* CPU, size_t reg_id)
{
    switch (reg_id)
    {
    case ax:
        if((CPU->reg[0] / 100) >= RAM_SIZE)
        {
            safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
        }
        else
        {
            CPU->ram[CPU->reg[0] / 100] = StackPop(CPU->stack);;
        }
        break;
    case bx:
        if((CPU->reg[1] / 100) >= RAM_SIZE)
        {   
            safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
        }
        else
        {
            CPU->ram[CPU->reg[1] / 100] = StackPop(CPU->stack);;
        }
        break;
    case cx:
        if((CPU->reg[2] / 100) >= RAM_SIZE)
        {
            safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
        }
        else
        {
            CPU->ram[CPU->reg[2] / 100] = StackPop(CPU->stack);;
        }
        break;
    case dx:
        if((CPU->reg[3] / 100) >= RAM_SIZE)
        {
            safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
        }
        else
        {
            CPU->ram[CPU->reg[3] / 100] = StackPop(CPU->stack);;
        }
        break;
    case rax:
        if((CPU->r_reg[0] / 100) >= RAM_SIZE)
        {
            safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
        }
        else
        {
            CPU->ram[CPU->r_reg[0] / 100] = StackPop(CPU->stack);;
        }
        break;
    case rbx:
        if((CPU->r_reg[1] / 100) >= RAM_SIZE)
        {
            safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
        }
        else
        {
            CPU->ram[CPU->r_reg[1] / 100] = StackPop(CPU->stack);;
        }
        break;
    case rcx:
        if((CPU->r_reg[2] / 100) >= RAM_SIZE)
        {
            safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
        }
        else
        {
            CPU->ram[CPU->r_reg[2] / 100] = StackPop(CPU->stack);;
        }
        break;
    default:
        safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INVALID_REG);
    }
}