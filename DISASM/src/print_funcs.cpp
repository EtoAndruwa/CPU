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

void print_commands(disasm_struct* disasm_struct) // DEBUG
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

void write_asm(disasm_struct* disasm_struct)
{
    FILE* asm_file = fopen(FILE_ASM_NAME, "wb");

    if(asm_file == nullptr)
    {
        printf("ERROR: %s cannot be openned\n", FILE_ASM_NAME);
        disasm_struct->error_code = ERR_OPEN_ASM_FILE;
        disasm_dtor(disasm_struct);
        exit(ERR_OPEN_ASM_FILE);
    }
    else
    {
        for(size_t i = 0; i < *disasm_struct->num_bin_cmd; i++)
        {
            if(disasm_struct->commands[i].flag_before != 0)
            {
                fprintf(asm_file, ":%ld\n", disasm_struct->flag_num);
                disasm_struct->flag_num++;
            }
            else if(disasm_struct->commands[i].func_before != 0)
            {
                fprintf(asm_file, "FUNCTION%ld:\n", disasm_struct->func_num);
                disasm_struct->func_num++;
            }
            else if(disasm_struct->commands[i].type == cmd)
            {
                fprintf(asm_file, "%s", get_cmd_string(disasm_struct->commands[i].value));
                fprintf(asm_file, "\n");
            }
        }
    }

    if(fclose(asm_file) == EOF)
    {
        printf("ERROR: %s cannot be closed\n", FILE_ASM_NAME);
        disasm_struct->error_code = ERR_CLOSE_ASM_FILE;
        disasm_dtor(disasm_struct);
        exit(ERR_CLOSE_ASM_FILE);
    }
}