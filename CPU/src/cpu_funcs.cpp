#include "CPU.h"

int push_ret(CPU* CPU, Call_stack* Call_stack, float index_to_jmp) // CHECKED
{
    if((Call_stack->cur_index >= 0) && (Call_stack->cur_index < CALL_STACK_SIZE))
    {
        Call_stack->call_stack[Call_stack->cur_index] = (int)index_to_jmp;
        Call_stack->cur_index++;
    }
    else
    {
        ERROR_MESSAGE(stderr, ERR_CALL_STACK_FULL)
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CALL_STACK_FULL);
    }
    return RETURN_OK;
}

void jmp_flag(CPU* CPU, float index_to_jmp) // CHECKED
{
    CPU->curr_cmd = (int)(CPU->bin_code[(int)index_to_jmp]);
} 

void jmp_flag_jz(CPU* CPU, float index_to_jmp) // CHECKED
{
    if(check_is_positive(CPU->reg[CX]) == IS_ZERO)
    {
        CPU->curr_cmd = (int)CPU->bin_code[(int)index_to_jmp];
        return;
    }
    CPU->curr_cmd += 2; 
}

int dec(CPU* CPU, float reg_code) // CHECKED
{
    #define DEF_CMD_DEC(reg_code)         \
        case reg_code:                    \
            CPU->reg[reg_code - 21] -= 1; \
            break;                        \

    switch((int)reg_code)
    { 
        DEF_CMD_DEC(AX)
        DEF_CMD_DEC(BX)
        DEF_CMD_DEC(CX)
        DEF_CMD_DEC(DX)
        DEF_CMD_DEC(EX)
        DEF_CMD_DEC(FX)
        DEF_CMD_DEC(HX)
        DEF_CMD_DEC(IX)
        #undef CMD_DEC

        default:
            ERROR_MESSAGE(stderr, ERR_NEW_REG)
            return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_NEW_REG);
    }
    return RETURN_OK;
}

int inc(CPU* CPU, float reg_code) // CHECKED
{
    #define DEF_CMD_INC(reg_code)         \
        case reg_code:                    \
            CPU->reg[reg_code - 21] += 1; \
            break;                        \

    switch((int)reg_code)
    { 
        DEF_CMD_INC(AX)
        DEF_CMD_INC(BX)
        DEF_CMD_INC(CX)
        DEF_CMD_INC(DX)
        DEF_CMD_INC(EX)
        DEF_CMD_INC(FX)
        DEF_CMD_INC(HX)
        DEF_CMD_INC(IX)
        #undef DEF_CMD_INC

        default:
            ERROR_MESSAGE(stderr, ERR_NEW_REG)
            return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_NEW_REG);
    }
    return RETURN_OK;
}

int jmp_ret(CPU* CPU, Call_stack* Call_stack) // CHECKED
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
        ERROR_MESSAGE(stderr, ERR_CALL_STACK_EMPT)
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CALL_STACK_EMPT);
    }
    return RETURN_OK;
}

int push_reg(CPU* CPU, float reg_code) // CHECKED From reg to stack
{   
    #define DEF_CMD_PUSH_REG(reg_code)                                          \
        case reg_code:                                                          \
        {                                                                       \
            int err_code = StackPush(CPU->stack, CPU->reg[reg_code - 21]);      \
            if(err_code != RETURN_OK)                                           \
            {                                                                   \
                CPU->error_code = err_code;                                     \
                ERROR_MESSAGE(stderr, CPU->error_code)                          \
                return CPU->error_code;                                         \
            }                                                                   \
            break;                                                              \
        }                                                                       \

    switch((int)reg_code)
    {
        DEF_CMD_PUSH_REG(AX)
        DEF_CMD_PUSH_REG(CX)
        DEF_CMD_PUSH_REG(BX)
        DEF_CMD_PUSH_REG(DX)
        DEF_CMD_PUSH_REG(EX)
        DEF_CMD_PUSH_REG(FX)
        DEF_CMD_PUSH_REG(HX)
        DEF_CMD_PUSH_REG(IX)
        #undef DEF_CMD_PUSH_REG

        default:
            ERROR_MESSAGE(stderr, ERR_NEW_REG)
            return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_NEW_REG);
    }
    return RETURN_OK;
}

int pop_reg(CPU* CPU, float reg_code) // CHECKED From Stack to reg
{
    #define DEF_CMD_POP_REG(reg_code)                       \
        case reg_code:                                      \
        {                                                   \
            stack_type val = StackPop(CPU->stack);          \
            if(val == POISON_VALUE)                         \
            {                                               \
                CPU->error_code = ERR_POP_VALUE_ERROR;      \
                ERROR_MESSAGE(stderr, CPU->error_code)      \
                return CPU->error_code;                     \
            }                                               \
            CPU->reg[reg_code - 21] = val;                  \
            break;                                          \
        }                                                   \

    switch((int)reg_code)
    {
        DEF_CMD_POP_REG(AX)
        DEF_CMD_POP_REG(BX)
        DEF_CMD_POP_REG(CX)
        DEF_CMD_POP_REG(DX)
        DEF_CMD_POP_REG(EX)
        DEF_CMD_POP_REG(FX)
        DEF_CMD_POP_REG(HX)
        DEF_CMD_POP_REG(IX)
        #undef DEF_CMD_POP_REG

        default:
            ERROR_MESSAGE(stderr, ERR_NEW_REG)
            return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_NEW_REG);
    }
    return RETURN_OK;
}

int push_ram_val(CPU* CPU, float ram_index) // CHECKED From RAM to Stack
{
    if(((int)ram_index < RAM_SIZE) && ((int)ram_index >= 0))
    {
        int error_code = StackPush(CPU->stack, CPU->ram[(int)ram_index]);
        if(error_code != RETURN_OK)
        {
            ERROR_MESSAGE(stderr, error_code)
            return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, error_code);
        }
    }
    else
    {
        ERROR_MESSAGE(stderr, ERR_RAM_ADDRESSING)
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
    }
    return RETURN_OK;
}

int pop_ram_val(CPU* CPU, float ram_index) // CHECKED From Stack to RAM
{
    if(((int)ram_index < RAM_SIZE) && ((int)ram_index >= 0))
    {
        stack_type val = StackPop(CPU->stack);
        if(CPU->stack->error_code != STACK_IS_OK)
        {
            ERROR_MESSAGE(stderr, CPU->stack->error_code)
            return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_POP_VALUE_ERROR);
        }
        CPU->ram[(int)ram_index] = val;
        return RETURN_OK;
    }
    ERROR_MESSAGE(stderr, ERR_RAM_ADDRESSING)
    return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);
}

int push_ram_reg(CPU* CPU, float reg_id) // CHECKED From RAM to stack
{
    #define DEF_CMD_POP_REG(reg_index)                                                          \
        case reg_index:                                                                         \
        {                                                                                       \
            int new_ram_id = CPU->reg[reg_index - 21];                                          \
            if(new_ram_id >= RAM_SIZE || new_ram_id < 0)                                        \
            {                                                                                   \
                ERROR_MESSAGE(stderr, ERR_RAM_ADDRESSING)                                       \
                return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);     \
            }                                                                                   \                                                                                 
            int err_code = StackPush(CPU->stack, CPU->ram[(int)CPU->reg[reg_index - 21]]);      \   
            if(err_code != RETURN_OK)                                                           \
            {                                                                                   \
                CPU->error_code = err_code;                                                     \
                ERROR_MESSAGE(stderr, CPU->error_code)                                          \
                return CPU->error_code;                                                         \
            }                                                                                   \    
            break;                                                                              \
        }                                                                                       \

    switch((int)reg_id)
    {
        DEF_CMD_POP_REG(AX)
        DEF_CMD_POP_REG(BX)
        DEF_CMD_POP_REG(CX)
        DEF_CMD_POP_REG(DX)
        DEF_CMD_POP_REG(EX)
        DEF_CMD_POP_REG(FX)
        DEF_CMD_POP_REG(HX)
        DEF_CMD_POP_REG(IX)
        #undef DEF_CMD_POP_REG

        default:
            ERROR_MESSAGE(stderr, ERR_NEW_REG)
            return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_NEW_REG);
    }
    return RETURN_OK;
}

int pop_ram_reg(CPU* CPU, float reg_id) // From Stack to RAM
{
    #define DEF_CMD_POP_RAM_REG(reg_index)                                                  \
        case reg_index:                                                                     \
            if((int)(CPU->reg[reg_index - 21]) >= RAM_SIZE)                                 \
            {                                                                               \
                return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING); \
            }                                                                               \                                                                             
            CPU->ram[(int)CPU->reg[reg_index - 21]] = StackPop(CPU->stack);                 \                                                                                 
            break;                                                                          \

    switch((int)reg_id)
    {
        DEF_CMD_POP_RAM_REG(AX)
        DEF_CMD_POP_RAM_REG(BX)
        DEF_CMD_POP_RAM_REG(CX)
        DEF_CMD_POP_RAM_REG(DX)
        #undef DEF_CMD_POP_RAM_REG

        default:
            ERROR_MESSAGE(stderr, ERR_NEW_REG)
            return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_NEW_REG);
    }
    return RETURN_OK;
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

int check_is_positive(double value) // CHECKED
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



