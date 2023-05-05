#include "CPU.h"

size_t push_ret(CPU* CPU, Call_stack* Call_stack, size_t index_to_jmp) 
{
    if((Call_stack->cur_index >= 0) && (Call_stack->cur_index < CALL_STACK_SIZE))
    {
        Call_stack->call_stack[Call_stack->cur_index] = index_to_jmp;
        Call_stack->cur_index++;
    }
    else
    {
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CALL_STACK_FULL);
    }
}

void jmp_flag(CPU* CPU, size_t index_to_jmp)
{
    CPU->curr_cmd = CPU->bin_code[index_to_jmp];
} 

void jmp_flag_jz(CPU* CPU, size_t index_to_jmp)
{
    if((CPU->reg[CX] / MUL_CONST) == 0)
    {
        CPU->curr_cmd = CPU->bin_code[index_to_jmp];
    }
    else
    {
        CPU->curr_cmd += 2; 
    }
}

size_t dec(CPU* CPU, size_t reg_code)
{
    #define DEF_CMD_DEC(reg_code)         \
        case reg_code:                    \
            CPU->reg[reg_code - 21] -= 1; \
            break;                        \

    switch (reg_code)
    { 

    DEF_CMD_DEC(AX)
    DEF_CMD_DEC(BX)
    DEF_CMD_DEC(CX)
    DEF_CMD_DEC(DX)
    #undef CMD_DEC

    default:
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INVALID_REG);
    }
}

size_t jmp_ret(CPU* CPU, Call_stack* Call_stack)
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
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CALL_STACK_EMPT);
    }
}

size_t push_reg(CPU* CPU, size_t reg_code) // From reg to stack
{   
    #define DEF_CMD_PUSH_REG(reg_code)                      \
        case reg_code:                                      \
            StackPush(CPU->stack, CPU->reg[reg_code - 21]); \
            break;                                          \

    switch (reg_code)
    {

    DEF_CMD_PUSH_REG(AX)
    DEF_CMD_PUSH_REG(CX)
    DEF_CMD_PUSH_REG(BX)
    DEF_CMD_PUSH_REG(DX)
    #undef DEF_CMD_PUSH_REG

    default:
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INVALID_REG);
    }
}

size_t pop_reg(CPU* CPU, size_t reg_code) // From Stack to reg
{
    #define DEF_CMD_POP_REG(reg_code)                       \
        case reg_code:                                      \
            CPU->reg[reg_code - 21] = StackPop(CPU->stack); \
            break;                                          \

    switch (reg_code)
    {

    DEF_CMD_POP_REG(AX)
    DEF_CMD_POP_REG(BX)
    DEF_CMD_POP_REG(CX)
    DEF_CMD_POP_REG(DX)
    #undef DEF_CMD_POP_REG

    default:
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INVALID_REG);
    }
}

size_t push_ram_val(CPU* CPU, size_t ram_index) // From RAM to Stack
{
    if((ram_index < RAM_SIZE) && (ram_index >= 0))
    {
        StackPush(CPU->stack, CPU->ram[ram_index]);
    }
    else
    {
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
    }
}

size_t pop_ram_val(CPU* CPU, size_t ram_index) // From Stack to RAM
{
    printf("1\n\n");
    if((ram_index < RAM_SIZE) && (ram_index >= 0))
    {
        CPU->ram[ram_index] = StackPop(CPU->stack);
    }
    else
    {
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
    }
}

size_t push_ram_reg(CPU* CPU, size_t reg_id) // From RAM to stack
{
    #define DEF_CMD_POP_REG(reg_id)                                                             \
        case reg_id:                                                                            \
            new_ram_id = (CPU->reg[reg_id - 21] / MUL_CONST);                                   \
            if(new_ram_id >= RAM_SIZE || new_ram_id < 0)                                        \
            {                                                                                   \
                return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);     \
            }                                                                                   \
            else                                                                                \
            {                                                                                   \
                StackPush(CPU->stack, CPU->ram[CPU->reg[reg_id - 1] / MUL_CONST]);              \
            }                                                                                   \
            break;                                                                              \

    int new_ram_id = 0;
    switch (reg_id)
    {

    DEF_CMD_POP_REG(AX)
    DEF_CMD_POP_REG(BX)
    DEF_CMD_POP_REG(CX)
    DEF_CMD_POP_REG(DX)
    #undef DEF_CMD_POP_REG

    default:
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INVALID_REG);
    }
}

size_t pop_ram_reg(CPU* CPU, size_t reg_id) // From Stack to RAM
{
    #define DEF_CMD_POP_RAM_REG(reg_id)                                                     \
        case reg_id:                                                                        \
            if((CPU->reg[reg_id - 21] / MUL_CONST) >= RAM_SIZE)                             \
            {                                                                               \
                return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING); \
            }                                                                               \
            else                                                                            \
            {                                                                               \
                CPU->ram[CPU->reg[reg_id - 21] / MUL_CONST] = StackPop(CPU->stack);         \
            }                                                                               \
            return 0;                                                                       \

    switch (reg_id)
    {

    DEF_CMD_POP_RAM_REG(AX)
    DEF_CMD_POP_RAM_REG(BX)
    DEF_CMD_POP_RAM_REG(CX)
    DEF_CMD_POP_RAM_REG(DX)
    #undef DEF_CMD_POP_RAM_REG

    default:
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INVALID_REG);
    }
}

size_t push_ram_reg_val(CPU* CPU, int push_id, size_t shift_value)
{
    size_t register_id = push_id & (3 << 2);    

    switch (register_id)
    {
    case 0:
        register_id = AX;
        break;
    case 2:
        register_id = BX;
        break;
    case 4:
        register_id = CX;
        break;
    case 8:
        register_id = DX;
        break;
    default:
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INVALID_REG);
    }

    #define DEF_CMD_PUSH_RAM_REG_VAL(register_id)                                           \
    case register_id:                                                                       \
        new_ram_id = (CPU->reg[register_id - 21] / MUL_CONST) + shift_value;                \
        if(new_ram_id >= RAM_SIZE || new_ram_id < 0)                                        \
        {                                                                                   \
            return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);     \
        }                                                                                   \
        else                                                                                \
        {                                                                                   \
            StackPush(CPU->stack,  CPU->ram[new_ram_id]);                                   \
        }                                                                                   \
        break;  

    size_t new_ram_id = 0;
    switch (register_id)
    {

    DEF_CMD_PUSH_RAM_REG_VAL(AX)
    DEF_CMD_PUSH_RAM_REG_VAL(BX)
    DEF_CMD_PUSH_RAM_REG_VAL(CX)
    DEF_CMD_PUSH_RAM_REG_VAL(DX)
    #undef DEF_CMD_PUSH_RAM_REG_VAL

    default:
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INVALID_REG);
    }
}

size_t pop_ram_reg_val(CPU* CPU, int pop_id, size_t shift_value)
{
    int register_id = pop_id & (3 << 2);    

    switch (register_id)
    {
    case 0:
        register_id = AX;
        break;
    case 2:
        register_id = BX;
        break;
    case 4:
        register_id = CX;
        break;
    case 8:
        register_id = DX;
        break;
    default:
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INVALID_REG);
    }

    #define DEF_CMD_POP_RAM_REG_VAL(register_id)                                                \
        case register_id:                                                                       \
            new_ram_id = (CPU->reg[register_id - 21] / MUL_CONST) + shift_value;                \
            if(new_ram_id >= RAM_SIZE || new_ram_id < 0)                                        \
            {                                                                                   \
                return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);     \
            }                                                                                   \
            else                                                                                \
            {                                                                                   \
                CPU->ram[new_ram_id] = StackPop(CPU->stack);                                    \
            }                                                                                   \
            break;  

    int new_ram_id = 0;
    switch (register_id)
    {

    DEF_CMD_POP_RAM_REG_VAL(AX)
    DEF_CMD_POP_RAM_REG_VAL(BX)
    DEF_CMD_POP_RAM_REG_VAL(CX)
    DEF_CMD_POP_RAM_REG_VAL(DX)
    #undef DEF_CMD_POP_RAM_REG_VAL

    default:
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INVALID_REG);
    }
}

int check_is_positive(double value) // ok
{
    if((fabs(value - fabs(value)) < EPS) && (fabs(value) > EPS))
    {
        return IS_POSITIVE;
    }
    else if(fabs(value) <= EPS)
    {
        return IS_ZERO;
    }
    
    return IS_NEGATIVE;
}



