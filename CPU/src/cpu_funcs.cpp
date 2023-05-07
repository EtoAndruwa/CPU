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

int jmp_flag(CPU* CPU, float index_to_jmp) // CHECKED
{
    CPU->curr_cmd = (int)(CPU->bin_code[(int)index_to_jmp]);
    return RETURN_OK;
} 

int jmp_flag_jz(CPU* CPU, float index_to_jmp) // CHECKED
{
    if(check_is_positive(CPU->reg[IX - AX]) == IS_ZERO)
    {
        CPU->curr_cmd = (int)CPU->bin_code[(int)index_to_jmp];
        return RETURN_OK;
    }
    CPU->curr_cmd += 2; 
    return RETURN_OK;
}

int jmp_flag_je(CPU* CPU, float index_to_jmp) // CHECKED
{
    if(fabs(CPU->reg[IX - AX] - CPU->reg[HX - AX]) <= EPS)
    {
        CPU->curr_cmd = (int)CPU->bin_code[(int)index_to_jmp];
        return RETURN_OK;
    }
    CPU->curr_cmd += 2; 
    return RETURN_OK;
}

int jmp_flag_jge(CPU* CPU, float index_to_jmp) // CHECKED
{
    if(fabs(CPU->reg[IX - AX] - CPU->reg[HX - AX]) <= EPS)
    {
        CPU->curr_cmd = (int)CPU->bin_code[(int)index_to_jmp];
        return RETURN_OK;
    }
    else if(check_is_positive(CPU->reg[IX - AX]) == IS_POSITIVE && (check_is_positive(CPU->reg[HX - AX]) == IS_NEGATIVE || 
        check_is_positive(CPU->reg[IX - AX] - CPU->reg[HX - AX]) == IS_POSITIVE))
    {
        CPU->curr_cmd = (int)CPU->bin_code[(int)index_to_jmp];
        return RETURN_OK;
    }
    else if(check_is_positive(CPU->reg[IX - AX]) == IS_NEGATIVE && check_is_positive(CPU->reg[HX - AX]) == IS_NEGATIVE &&
         check_is_positive(fabs(CPU->reg[IX - AX]) - fabs(CPU->reg[HX - AX])) == IS_NEGATIVE)
    {
        CPU->curr_cmd = (int)CPU->bin_code[(int)index_to_jmp];
        return RETURN_OK;
    }

    CPU->curr_cmd += 2; 
    return RETURN_OK;
}

int jmp_flag_jne(CPU* CPU, float index_to_jmp) // CHECKED
{
    if(fabs(CPU->reg[IX - AX] - CPU->reg[HX - AX]) > EPS)
    {
        printf("OLD cur - %ld\n", CPU->curr_cmd);
        printf("index_to_jmp %f\n", index_to_jmp);
        CPU->curr_cmd = (int)CPU->bin_code[(int)index_to_jmp] + 1;
        printf("CPU->num_bin_cmd %f\n", *CPU->num_bin_cmd);
        printf("Cur index after jne %ld and command now %f and pref cmd %f %f %f %f %f %f\n", CPU->curr_cmd, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd - 1], CPU->bin_code[CPU->curr_cmd - 2], CPU->bin_code[CPU->curr_cmd - 3], CPU->bin_code[CPU->curr_cmd - 4], CPU->bin_code[CPU->curr_cmd - 5], CPU->bin_code[CPU->curr_cmd - 6], CPU->bin_code[CPU->curr_cmd - 7]);
        return RETURN_OK;
    }

    CPU->curr_cmd += 2; 
    printf("Cur index after jne %ld and command now %f\n", CPU->curr_cmd, CPU->bin_code[CPU->curr_cmd]);
    return RETURN_OK;
}

int jmp_flag_jg(CPU* CPU, float index_to_jmp) // CHECKED
{
    if(check_is_positive(CPU->reg[IX - AX]) == IS_POSITIVE && check_is_positive(CPU->reg[HX - AX]) == IS_POSITIVE && 
        check_is_positive(CPU->reg[IX - AX] - CPU->reg[HX - AX]) == IS_POSITIVE)
    {   
        CPU->curr_cmd = (int)CPU->bin_code[(int)index_to_jmp];
        return RETURN_OK;
    }
    else if(check_is_positive(CPU->reg[IX - AX]) == IS_POSITIVE && check_is_positive(CPU->reg[HX - AX]) == IS_NEGATIVE)
    {
        printf("\n2\n");
        CPU->curr_cmd = (int)CPU->bin_code[(int)index_to_jmp];
        return RETURN_OK;
    }
    else if(check_is_positive(CPU->reg[IX - AX]) == IS_NEGATIVE && check_is_positive(CPU->reg[HX - AX]) == IS_NEGATIVE && 
        check_is_positive(fabs(CPU->reg[IX - AX]) - fabs(CPU->reg[HX - AX])) == IS_NEGATIVE)
    {
        printf("\n3\n");
        CPU->curr_cmd = (int)CPU->bin_code[(int)index_to_jmp];
        return RETURN_OK;
    }

    printf("\n4\n");
    CPU->curr_cmd += 2; 
    return RETURN_OK;
}

int inp(CPU* CPU, float reg_code) // CHECKED
{
    #define DEF_CMD_INP(reg_code)                               \
        case reg_code:                                          \
        {                                                       \
            printf("Enter the value of reg %s = ", #reg_code);  \
            float val = 0;                                      \
            scanf("%f", &val);                                  \
            CPU->reg[reg_code - 21] = val;                      \
            break;                                              \
        }                                                       \

    switch((int)reg_code)
    { 
        DEF_CMD_INP(AX)
        DEF_CMD_INP(BX)
        DEF_CMD_INP(CX)
        DEF_CMD_INP(DX)
        DEF_CMD_INP(EX)
        DEF_CMD_INP(FX)
        DEF_CMD_INP(HX)
        DEF_CMD_INP(IX)
        #undef DEF_CMD_INP

        default:
            ERROR_MESSAGE(stderr, ERR_NEW_REG)
            return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_NEW_REG);
    }
    return RETURN_OK;
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
        #undef DEF_CMD_DEC

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

int pop_ram_reg(CPU* CPU, float reg_id) // CHECKED From Stack to RAM
{
    #define DEF_CMD_POP_RAM_REG(reg_index)                                                  \
        case reg_index:                                                                     \
        {                                                                                   \
            if((int)(CPU->reg[reg_index - 21]) >= RAM_SIZE)                                 \
            {                                                                               \
                ERROR_MESSAGE(stderr, ERR_RAM_ADDRESSING)                                   \
                return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING); \
            }                                                                               \                                                                             
            stack_type val = StackPop(CPU->stack);                                          \
            if(CPU->stack->error_code != STACK_IS_OK)                                       \
            {                                                                               \
                ERROR_MESSAGE(stderr, CPU->stack->error_code)                               \
                return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_POP_VALUE_ERROR);\
            }                                                                               \
            CPU->ram[(int)CPU->reg[reg_index - 21]] = val;                                  \                                                                                   
            break;                                                                          \
        }                                                                                   \

    switch((int)reg_id)
    {
        DEF_CMD_POP_RAM_REG(AX)
        DEF_CMD_POP_RAM_REG(BX)
        DEF_CMD_POP_RAM_REG(CX)
        DEF_CMD_POP_RAM_REG(DX)
        DEF_CMD_POP_RAM_REG(EX)
        DEF_CMD_POP_RAM_REG(FX)
        DEF_CMD_POP_RAM_REG(HX)
        DEF_CMD_POP_RAM_REG(IX)
        #undef DEF_CMD_POP_RAM_REG

        default:
            ERROR_MESSAGE(stderr, ERR_NEW_REG)
            return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_NEW_REG);
    }
    return RETURN_OK;
}

int push_ram_reg_val(CPU* CPU, float push_id, float shift_value) // CHECKED
{
    int register_id = ((int)push_id) & (7 << 2);    

    switch(register_id)
    {
        case 0:
            register_id = AX;
            break;
        case 4:
            register_id = BX;
            break;
        case 8:
            register_id = CX;
            break;
        case 16:
            register_id = DX;
            break;
        case 12:
            register_id = EX;
            break;
        case 20:
            register_id = FX;
            break;
        case 24:
            register_id = HX;
            break;
        case 28:
            register_id = IX;
            break;
        default:
            ERROR_MESSAGE(stderr, ERR_NEW_REG)
            return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_NEW_REG);
    }

    #define DEF_CMD_PUSH_RAM_REG_VAL(register_id)                                               \
        case register_id:                                                                       \
        {                                                                                       \
            int new_ram_id = CPU->reg[register_id - 21] + shift_value;                          \
            if(new_ram_id >= RAM_SIZE || new_ram_id < 0)                                        \
            {                                                                                   \
                ERROR_MESSAGE(stderr, ERR_RAM_ADDRESSING)                                       \
                return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);     \
            }                                                                                   \                                                                                   
            StackPush(CPU->stack, CPU->ram[new_ram_id]);                                        \
            if(CPU->stack->error_code != STACK_IS_OK)                                           \   
            {                                                                                   \
                ERROR_MESSAGE(stderr, ERR_RAM_ADDRESSING)                                       \   
                return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);     \
            }                                                                                   \
            break;                                                                              \
        }                                                                                       \

    switch(register_id)
    {
        DEF_CMD_PUSH_RAM_REG_VAL(AX)
        DEF_CMD_PUSH_RAM_REG_VAL(BX)
        DEF_CMD_PUSH_RAM_REG_VAL(CX)
        DEF_CMD_PUSH_RAM_REG_VAL(DX)
        DEF_CMD_PUSH_RAM_REG_VAL(EX)
        DEF_CMD_PUSH_RAM_REG_VAL(FX)
        DEF_CMD_PUSH_RAM_REG_VAL(HX)
        DEF_CMD_PUSH_RAM_REG_VAL(IX)
        #undef DEF_CMD_PUSH_RAM_REG_VAL

        default:
            ERROR_MESSAGE(stderr, ERR_NEW_REG)
            return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_NEW_REG);
    }
    return RETURN_OK;
}

int pop_ram_reg_val(CPU* CPU, float pop_id, float shift_value) // CHECKED
{
    int register_id = ((int)pop_id) & (7 << 2);    

    switch(register_id)
    {
        case 0:
            register_id = AX;
            break;
        case 4:
            register_id = BX;
            break;
        case 8:
            register_id = CX;
            break;
        case 16:
            register_id = DX;
            break;
        case 12:
            register_id = EX;
            break;
        case 20:
            register_id = FX;
            break;
        case 24:
            register_id = HX;
            break;
        case 28:
            register_id = IX;
            break;
        default:
            ERROR_MESSAGE(stderr, ERR_NEW_REG)
            return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_NEW_REG);
    }

    #define DEF_CMD_POP_RAM_REG_VAL(register_id)                                                \
        case register_id:                                                                       \
        {                                                                                       \
            int new_ram_id = CPU->reg[register_id - 21] + shift_value;                          \
            if(new_ram_id >= RAM_SIZE || new_ram_id < 0)                                        \
            {                                                                                   \
                ERROR_MESSAGE(stderr, ERR_RAM_ADDRESSING)                                       \
                return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);     \
            }                                                                                   \                                                                                 
            stack_type val = StackPop(CPU->stack);                                              \
            if(CPU->stack->error_code != STACK_IS_OK)                                           \
            {                                                                                   \
                ERROR_MESSAGE(stderr, ERR_RAM_ADDRESSING)                                       \
                return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_RAM_ADDRESSING);     \
            }                                                                                   \
            CPU->ram[new_ram_id] = val;                                                         \
            break;                                                                              \
        }                                                                                       \

    switch(register_id)
    {
        DEF_CMD_POP_RAM_REG_VAL(AX)
        DEF_CMD_POP_RAM_REG_VAL(BX)
        DEF_CMD_POP_RAM_REG_VAL(CX)
        DEF_CMD_POP_RAM_REG_VAL(DX)
        DEF_CMD_POP_RAM_REG_VAL(EX)
        DEF_CMD_POP_RAM_REG_VAL(FX)
        DEF_CMD_POP_RAM_REG_VAL(HX)
        DEF_CMD_POP_RAM_REG_VAL(IX)
        #undef DEF_CMD_POP_RAM_REG_VAL

        default:
            ERROR_MESSAGE(stderr, ERR_NEW_REG)
            return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_NEW_REG);
    }
    return RETURN_OK;
}



