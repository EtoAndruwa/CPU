#include "disassembler.h"

size_t dump_disasm(disasm_struct* disasm_struct, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE) 
{
    FILE* logfile = fopen(FILE_DUMP_NAME, "wb");

    if(logfile == nullptr)
    {
        printf("ERROR: %s cannot be openned\n" , FILE_DUMP_NAME);
        disasm_struct->error_code = ERR_OPEN_DUMP_FILE;
        disasm_dtor(disasm_struct);
        return disasm_struct->error_code;
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
        return disasm_struct->error_code;
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

size_t write_asm(disasm_struct* disasm_struct)
{
    FILE* asm_file = fopen(FILE_ASM_NAME, "wb");
    if(asm_file == nullptr)
    {
        printf("ERROR: %s cannot be openned\n", FILE_ASM_NAME);
        disasm_struct->error_code = ERR_OPEN_ASM_FILE;
        disasm_dtor(disasm_struct);
        return disasm_struct->error_code;
    }
    else
    {
        for(disasm_struct->cur_cmd_index = 0; disasm_struct->cur_cmd_index < *disasm_struct->num_bin_cmd;)
        {
            print_flag_func(disasm_struct, asm_file);

            if((disasm_struct->commands[disasm_struct->cur_cmd_index].type == CMD) && (disasm_struct->cur_cmd_index < *disasm_struct->num_bin_cmd))
            {
                fprintf(asm_file, "%s", get_cmd_string(disasm_struct->commands[disasm_struct->cur_cmd_index].value));

                if(disasm_struct->commands[disasm_struct->cur_cmd_index].value == JMP || disasm_struct->commands[disasm_struct->cur_cmd_index].value == JZ)
                {
                    fprintf(asm_file, " :%d\n", disasm_struct->commands[disasm_struct->cur_cmd_index + 1].value);
                    disasm_struct->cur_cmd_index += 2;  
                }
                else if(disasm_struct->commands[disasm_struct->cur_cmd_index].value == CALL)
                {
                    fprintf(asm_file, " FUNCTION%ld:\n", disasm_struct->commands[disasm_struct->cur_cmd_index + 1].value);
                    disasm_struct->cur_cmd_index += 2;
                }
                else if(disasm_struct->commands[disasm_struct->cur_cmd_index + 1].type != CMD)
                {
                    if(disasm_struct->cur_cmd_index + 1 < *disasm_struct->num_bin_cmd)
                    {
                        disasm_struct->cur_cmd_index++;
                    }
                    else
                    {
                        return 0;
                    }

                    switch(disasm_struct->commands[disasm_struct->cur_cmd_index].type)
                    {
                        case VAL:
                            fprintf(asm_file, " %d", disasm_struct->commands[disasm_struct->cur_cmd_index].value);
                            disasm_struct->cur_cmd_index++;
                            fprintf(asm_file, "\n");
                            break;
                        case REG:
                            fprintf(asm_file, " %s", get_cmd_string(disasm_struct->commands[disasm_struct->cur_cmd_index].value));
                            disasm_struct->cur_cmd_index++;
                            fprintf(asm_file, "\n");
                            break;
                        case RAM_VAL:
                            fprintf(asm_file, " [%d]", disasm_struct->commands[disasm_struct->cur_cmd_index].value);
                            disasm_struct->cur_cmd_index++;
                            fprintf(asm_file, "\n");
                            break;
                        case RAM_REG:
                            fprintf(asm_file, " [%s]", get_cmd_string(disasm_struct->commands[disasm_struct->cur_cmd_index].value));
                            disasm_struct->cur_cmd_index++;
                            fprintf(asm_file, "\n");
                            break;
                        case RAM_VAL_REG:
                            fprintf(asm_file, " [%d+%s]", disasm_struct->commands[disasm_struct->cur_cmd_index].value, get_reg_inner_ram(disasm_struct->commands[disasm_struct->cur_cmd_index - 1].value));
                            disasm_struct->cur_cmd_index++;
                            fprintf(asm_file, "\n");
                            break;
                        default:
                            printf("Type: %d\n\n\n", disasm_struct->commands[disasm_struct->cur_cmd_index].type);
                            fprintf(asm_file, "\nERROR CODE DETECTED\n");
                            disasm_struct->cur_cmd_index++;
                            fprintf(asm_file, "\n");
                            break;
                    }
                }
                else
                {
                    disasm_struct->cur_cmd_index++;
                    fprintf(asm_file, "\n");
                }
            }
            else
            {
                fprintf(asm_file, "%s", get_cmd_string(disasm_struct->commands[disasm_struct->cur_cmd_index].value));
            }
        }
    }

    if(fclose(asm_file) == EOF)
    {
        printf("ERROR: %s cannot be closed\n", FILE_ASM_NAME);
        disasm_struct->error_code = ERR_CLOSE_ASM_FILE;
        disasm_dtor(disasm_struct);
        return disasm_struct->error_code;
    }
}

void print_flag_func(disasm_struct* disasm_struct, FILE* asm_file)
{
    if(disasm_struct->commands[disasm_struct->cur_cmd_index].flag_before != 0 && disasm_struct->commands[disasm_struct->cur_cmd_index].func_before != 0)
    {
        fprintf(asm_file, ":%ld\n", disasm_struct->commands[disasm_struct->cur_cmd_index].flag_before);
        fprintf(asm_file, "FUNCTION%ld:\n", disasm_struct->commands[disasm_struct->cur_cmd_index].func_before);
        return;
    }
    if(disasm_struct->commands[disasm_struct->cur_cmd_index].flag_before != 0)
    {
        fprintf(asm_file, ":%ld\n", disasm_struct->commands[disasm_struct->cur_cmd_index].flag_before);
        return;
    }
    else if(disasm_struct->commands[disasm_struct->cur_cmd_index].func_before != 0)
    {
        fprintf(asm_file, "FUNCTION%ld:\n", disasm_struct->commands[disasm_struct->cur_cmd_index].func_before);
        return;
    }
}
