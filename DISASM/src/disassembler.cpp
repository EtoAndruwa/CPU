#include "disassembler.h"

FILE* check_code_file(disasm_struct* disasm_struct)
{
    FILE* bin_file_ptr = fopen("../ASM/bin_code.bin", "rb"); // Opens an empty file

    if(bin_file_ptr == nullptr)
    {
        safe_exit(disasm_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_OPEN_BIN_FILE);
    }
    else
    {   
        return bin_file_ptr;
    }
}

void get_cmd_in_buf(disasm_struct* disasm_struct)
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
    for(size_t i = 0; i < *disasm_struct->num_bin_cmd; i++)
    {
        if((i < 21) || (i > 27))
        {
            disasm_struct->commands[i].type = cmd;
        }
    }
}