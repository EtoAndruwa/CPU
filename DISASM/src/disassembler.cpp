#include "disassembler.h"

size_t check_code_file(disasm_struct* disasm_struct)
{
    FILE* bin_file_ptr = fopen("../ASM/bin_code.bin", "rb"); // Opens an empty file

    if(bin_file_ptr == nullptr)
    {
        safe_exit(disasm_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_OPEN_BIN_FILE);
    }
    else
    {   
        disasm_struct->bin_file_ptr;
    }
}

size_t get_cmd_in_buf(disasm_struct* disasm_struct)
{
    FILE* bin_file_ptr = check_code_file(disasm_struct);

    if(fread(disasm_struct->num_bin_cmd, sizeof(int), 1, bin_file_ptr) != 1)
    {
        safe_exit(disasm_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INV_READ_NUM_CMD);
    }

    disasm_struct->bin_codes_buf = (int*)calloc(*disasm_struct->num_bin_cmd, sizeof(int));

    if(disasm_struct->bin_codes_buf == nullptr)    
    {
        safe_exit(disasm_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CALLOC_BIN_BUF);
    }

    if(fread(disasm_struct->bin_codes_buf, sizeof(int), *disasm_struct->num_bin_cmd, bin_file_ptr) != *disasm_struct->num_bin_cmd)
    {
        safe_exit(disasm_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CANNOT_READ_CMD);
    }

    if(fclose(bin_file_ptr) == EOF)
    {
        safe_exit(disasm_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CLOSE_BIN_FILE);
    }
}

void safe_exit(disasm_struct* disasm_struct, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE, size_t error_code)
{
    disasm_struct->error_code = error_code;
    dump_disasm(disasm_struct, FUNCT_NAME, FUNCT_LINE, FUNCT_FILE);
    disasm_dtor(disasm_struct);
    exit(error_code);
}

void get_command_types(disasm_struct* disasm_struct)
{
    for(disasm_struct->cur_cmd_index =  0; disasm_struct->cur_cmd_index < *disasm_struct->num_bin_cmd;)
    {
        if((disasm_struct->commands[disasm_struct->cur_cmd_index].value < 21) || (disasm_struct->commands[disasm_struct->cur_cmd_index].value > 27))
        {
            disasm_struct->commands[disasm_struct->cur_cmd_index].type = cmd;
            check_next_cmd(disasm_struct);
        }
    }
}

void check_next_cmd(disasm_struct* disasm_struct)
{
    switch(disasm_struct->commands[disasm_struct->cur_cmd_index].value)
    {
        case HLT:
            disasm_struct->cur_cmd_index++;
            break;
        case PUSH_ST:
            disasm_struct->commands[disasm_struct->cur_cmd_index + 1].type = val;
            disasm_struct->cur_cmd_index += 2;
            break;
        case PUSH_REG:
            disasm_struct->commands[disasm_struct->cur_cmd_index + 1].type = reg;
            disasm_struct->cur_cmd_index += 2;
            break;
        case PUSH_RAM_VAL:
            disasm_struct->commands[disasm_struct->cur_cmd_index + 1].type = ram_val;
            disasm_struct->cur_cmd_index += 2;
            break;
        case PUSH_RAM_REG:
            disasm_struct->commands[disasm_struct->cur_cmd_index + 1].type = ram_reg;
            disasm_struct->cur_cmd_index += 2;
            break;
        case POP_REG:
            disasm_struct->commands[disasm_struct->cur_cmd_index + 1].type = reg;
            disasm_struct->cur_cmd_index += 2;
            break;
        case POP_RAM_VAL:
            disasm_struct->commands[disasm_struct->cur_cmd_index + 1].type = ram_val;
            disasm_struct->cur_cmd_index += 2;
            break;
        case POP_RAM_REG:
            disasm_struct->commands[disasm_struct->cur_cmd_index + 1].type = ram_reg;
            disasm_struct->cur_cmd_index += 2;
            break;
        case DEC:
            disasm_struct->commands[disasm_struct->cur_cmd_index + 1].type = reg;
            disasm_struct->cur_cmd_index += 2;
            break;
        case JZ:
            disasm_struct->commands[disasm_struct->cur_cmd_index + 1].type = val;
            disasm_struct->cur_cmd_index += 2;
            break;
        case ADD:
            disasm_struct->cur_cmd_index++;
            break;
        case SUB:
            disasm_struct->cur_cmd_index++;
            break;
        case MUL:
            disasm_struct->cur_cmd_index++;
            break;
        case DIV:
            disasm_struct->cur_cmd_index++;
            break;
        case SQRT:
            disasm_struct->cur_cmd_index++;
            break;
        case OUT:
            disasm_struct->cur_cmd_index++;
            break;
        case RET:
            disasm_struct->cur_cmd_index++;
            break;
        case JMP:
            disasm_struct->commands[disasm_struct->cur_cmd_index + 1].type = val;
            disasm_struct->cur_cmd_index += 2;
            break;
        case CALL:
            disasm_struct->commands[disasm_struct->cur_cmd_index + 1].type = val;
            disasm_struct->cur_cmd_index += 2;
            break;
    }
}

void put_flag_func(disasm_struct* disasm_struct)
{
    for(size_t i = 0; i < *disasm_struct->num_bin_cmd; i++)
    {
        if(disasm_struct->commands[i].type == cmd)
        {   
            if(disasm_struct->commands[i].value == JMP || disasm_struct->commands[i].value == JZ)
            {
                disasm_struct->commands[disasm_struct->commands[i + 1].value].flag_before = disasm_struct->commands[i+1].value;
                i++;
            }
            else if(disasm_struct->commands[i].value == CALL)
            {
                disasm_struct->commands[disasm_struct->commands[i + 1].value].func_before = disasm_struct->commands[i+1].value;
                i++;
            }
        }
    }
}
