#include "CPU.h"

size_t check_code_file(CPU* CPU)
{
    FILE* bin_file_ptr = fopen("../ASM/bin_code.bin", "rb"); // Opens an empty file

    if(bin_file_ptr == nullptr)
    {
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_OPEN_BIN_FILE);
    }
    else
    {   
        CPU->bin_file = bin_file_ptr;
        return 0;
    }
}

size_t cpu_logic(size_t cmd_code, CPU* CPU, Call_stack* Call_stack)
{
    #define DEF_CMD(name, body) case name: body; break;

    switch (cmd_code)
    {

    #include "gen_cmd.h"
    #undef DEF_CMD

    default:
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_UNKNOWN_CMD);
    }
}

size_t get_cmd_in_buf(CPU* CPU)
{
    if(check_code_file(CPU) != 0)
    {
        return CPU->error_code;
    }
    if(fread(CPU->num_bin_cmd, sizeof(int), 1, CPU->bin_file) != 1)
    {
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INV_READ_NUM_CMD);
    }
    CPU->bin_code = (int*)calloc(CPU->num_bin_cmd[0], sizeof(int));

    if(CPU->bin_code == nullptr)    
    {
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CALLOC_BIN_CODE);
    }

    if(fread(CPU->bin_code, sizeof(int), CPU->num_bin_cmd[0], CPU->bin_file) != *CPU->num_bin_cmd)
    {
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CANNOT_READ_CMD);
    }
    if(fclose(CPU->bin_file) == EOF)
    {
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CLOSE_BIN_FILE);
    }
    CPU->bin_file = nullptr;

    return 0;
}

size_t cpu_work(CPU* CPU, Call_stack* Call_stack)
{
    while(CPU->bin_code[CPU->curr_cmd] != HLT)
    {
        size_t error_code = cpu_logic(CPU->bin_code[CPU->curr_cmd], CPU, Call_stack);
        // if(error_code != 0)
        // {
        //     return error_code;
        // }
    }
    return 0;
}

size_t safe_exit(CPU* CPU, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE, size_t error_code)
{
    CPU->error_code = error_code;
    if(dump_cpu(CPU, FUNCT_NAME, FUNCT_LINE, FUNCT_FILE) != 0)
    {
        return CPU->error_code;
    }
    cpu_dtor(CPU);

    return CPU->error_code;
}

