#include "CPU.h"

FILE* check_code_file(CPU* CPU)
{
    FILE* bin_file_ptr = fopen("../ASM/bin_code.bin", "rb"); // Opens an empty file

    if(bin_file_ptr == nullptr)
    {
        safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_OPEN_BIN_FILE);
    }
    else
    {   
        return bin_file_ptr;
    }
}

void cpu_logic(size_t cmd_code, CPU* CPU, Call_stack* Call_stack)
{
    switch (cmd_code)
    {
    case PUSH_ST: 
        StackPush(CPU->stack, (int)CPU->bin_code[CPU->curr_cmd + 1] * MUL_CONST);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        break;
    case PUSH_REG: 
        push_reg(CPU, CPU->bin_code[CPU->curr_cmd + 1]);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        break;
    case POP_REG: 
        pop_reg(CPU, CPU->bin_code[CPU->curr_cmd + 1]);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        break;
    case ADD: 
        StackAdd(CPU->stack);
        CPU->curr_cmd++;
        break;
    case MUL: 
        StackMul(CPU->stack);
        CPU->curr_cmd++;
        break;
    case OUT: 
        StackOut(CPU->stack);
        CPU->curr_cmd++;
        break;
    case DIV: 
        StackDiv(CPU->stack);
        CPU->curr_cmd++;
        break;
    case SQRT: 
        StackSqrt(CPU->stack);
        CPU->curr_cmd++;
        break;
    case SUB: 
        StackSub(CPU->stack);
        CPU->curr_cmd++;
        break;
    case CALL: 
        push_ret(CPU, Call_stack, CPU->curr_cmd + 2);
        CPU->curr_cmd = CPU->bin_code[CPU->curr_cmd + 1];
        break;
    case RET:
        jmp_ret(CPU, Call_stack);
        break;
    case JMP:
        jmp_flag(CPU, CPU->curr_cmd + 1);
        break;
    case PUSH_RAM_REG:
        push_ram_reg(CPU, CPU->bin_code[CPU->curr_cmd + 1]);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        break;
    case PUSH_RAM_VAL:
        push_ram_val(CPU, CPU->bin_code[CPU->curr_cmd + 1]);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        break;
    case POP_RAM_REG:
        pop_ram_reg(CPU, CPU->bin_code[CPU->curr_cmd + 1]);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        break;
    case POP_RAM_VAL:
        pop_ram_val(CPU, CPU->bin_code[CPU->curr_cmd + 1]);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        break;
    default:
        safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_UNKNOWN_CMD);
    }
}

void get_cmd_in_buf(CPU* CPU)
{
    FILE* bin_file_ptr = check_code_file(CPU);

    if(fread(CPU->num_bin_cmd, sizeof(int), 1, bin_file_ptr) != 1)
    {
        safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INV_READ_NUM_CMD);
    }

    CPU->bin_code = (int*)calloc(*CPU->num_bin_cmd, sizeof(int));

    if(CPU->bin_code == nullptr)    
    {
        safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CALLOC_BIN_CODE);
    }

    if(fread(CPU->bin_code, sizeof(int), *CPU->num_bin_cmd, bin_file_ptr) != *CPU->num_bin_cmd)
    {
        safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CANNOT_READ_CMD);
    }

    if(fclose(bin_file_ptr) == EOF)
    {
        safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CLOSE_BIN_FILE);
    }
}

void cpu_work(CPU* CPU, Call_stack* Call_stack)
{
    while(CPU->bin_code[CPU->curr_cmd] != HLT)
    {
        cpu_logic(CPU->bin_code[CPU->curr_cmd], CPU, Call_stack);
    }
}

void safe_exit(CPU* CPU, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE, size_t error_code)
{
    CPU->error_code = error_code;
    dump_cpu(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE);
    cpu_dtor(CPU);
    exit(error_code);
}
