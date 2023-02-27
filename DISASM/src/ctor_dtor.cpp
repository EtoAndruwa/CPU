#include "disassembler.h"

void disasm_ctor(disasm_struct* disasm_struct)
{
    disasm_struct->error_code = STRUCT_OK;
    disasm_struct->flag_num = 1;
    disasm_struct->func_num = 1;

     disasm_struct->commands = (command*)calloc(*disasm_struct->num_bin_cmd, sizeof(command));

    if(disasm_struct->commands == nullptr)    
    {
        safe_exit(disasm_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CALLOC_COMMANDS);
    }

    for(size_t i = 0; i < *disasm_struct->num_bin_cmd; i++)
    {
        disasm_struct->commands[i].value = disasm_struct->bin_codes_buf[i];
        disasm_struct->commands[i].flag_before = 0;
        disasm_struct->commands[i].func_before = 0;
        disasm_struct->commands[i].type = empty;
    }

    fill_with_poison(disasm_struct->bin_codes_buf, *disasm_struct->num_bin_cmd);
    free(disasm_struct->bin_codes_buf);
    disasm_struct->bin_codes_buf = nullptr;
}


void disasm_dtor(disasm_struct* disasm_struct)
{
     dump_disasm(disasm_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);

    for(size_t i = 0; i < *disasm_struct->num_bin_cmd; i++)
    {
        disasm_struct->commands[i].value = POISON;
        disasm_struct->commands[i].flag_before = POISON;
        disasm_struct->commands[i].func_before = POISON;
        disasm_struct->commands[i].type = POISON;
    }

    free(disasm_struct->commands);
    disasm_struct->commands = nullptr;

    disasm_struct->error_code = POISON;
    disasm_struct->flag_num = POISON;
    disasm_struct->func_num = POISON;
    disasm_struct->num_bin_cmd[0] = POISON;
}


void fill_with_poison(int* arr_ptr, size_t size_arr)
{
    for(size_t i = 0; i < size_arr; i++)
    {
        arr_ptr[i] = POISON;
    }
}
