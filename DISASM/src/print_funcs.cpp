#include "disassembler.h"

void dump_disasm(disasm_struct* disasm_struct, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE) 
{
    FILE* logfile = fopen(FILE_DUMP_NAME, "wb");

    if(logfile == nullptr)
    {
        printf("ERROR: %s cannot be openned\n" , FILE_DUMP_NAME);
        disasm_struct->error_code = ERR_OPEN_DUMP_FILE;
        disasm_dtor(disasm_struct);
        exit(ERR_OPEN_DUMP_FILE);
    }
    else
    {
        fprintf(logfile, "\n-------------------STRUCT_DATA-------------------\n");
        fprintf(logfile, "disasm_struct->err_code: %ld (%s)\n", disasm_struct->error_code, enum_struct_err_to_string(disasm_struct->error_code));   
        fprintf(logfile, "-------------------STRUCT_DATA-------------------\n");

        fprintf(logfile, "\n-------------------DUMP_DATA-------------------\n");
        fprintf(logfile, "File name: %s\n", FUNCT_FILE);
        fprintf(logfile, "Function name: %s\n", FUNCT_NAME);
        fprintf(logfile, "Line: %d\n", FUNCT_LINE);
        fprintf(logfile, "Time: %s\n", __TIME__);
        fprintf(logfile, "Date: %s\n", __DATE__);
        fprintf(logfile, "-------------------DUMP_DATA-------------------\n");
    }

    if(fclose(logfile) == EOF)
    {
        printf("ERROR: %s cannot be closed\n", FILE_DUMP_NAME);
        disasm_struct->error_code = ERR_CLOSE_DUMP_FILE;
        disasm_dtor(disasm_struct);
        exit(ERR_CLOSE_DUMP_FILE);
    }
}

void print_commands(disasm_struct* disasm_struct)
{
    for(size_t i = 0; i < *disasm_struct->num_bin_cmd; i++)
    {
        printf("\nIndex: %ld\n", i);
        printf("Value: %d\n", disasm_struct->commands[i].value);
        printf("Type: %ld\n", disasm_struct->commands[i].type);
        printf("Flag before: %ld\n", disasm_struct->commands[i].flag_before);
        printf("Function before: %ld\n", disasm_struct->commands[i].func_before);
    }
}