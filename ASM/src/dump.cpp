#include "assembler.h"

/**
 * @brief                  | (OK) Makes listing of the assembled code
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void listing(asm_struct* assembly_struct)
{
    FILE* listing_file = fopen("asm_listing.txt", "wb");

    fprintf(listing_file,"|NUMB|\t\tCOMMAND\t\t|    TYPE    |ASM|    STATUS    |\n");
    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {   
        fprintf(listing_file,"|%04ld|		%-4s		|    %s     |%03d|      %s      |", i, assembly_struct->toks[i].text, enum_type_to_string(assembly_struct->toks[i].type), assembly_struct->toks[i].value, assembly_struct->toks[i].status);
        if(strcmp(assembly_struct->toks[i].status, "--") == 0)
        {
            fprintf(listing_file, " <----- %s", enum_token_err_to_string(assembly_struct->toks[i].error_code)); 
        }
        fprintf(listing_file, "\n");
    }

    if(assembly_struct->err_code == ERR_NO_HLT)
    {
        fprintf(listing_file,"|    |\t\t       \t\t|            |   |              | <----- MISSING HLT\n");
    }

    fclose(listing_file);
}

/**
 * @brief                  | (OK) Creates LOG_FILE.txt with all information about asm_struct
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 * @param FUNCT_NAME       | The string containing the name of the function which called the error
 * @param FUNCT_LINE       | The number of the line which called the error
 */
void dump_asm(asm_struct* assembly_struct, const char * FUNCT_NAME, int FUNCT_LINE) 
{
    FILE* logfile = fopen("LOG_FILE.txt", "wb");

    if(logfile == nullptr)
    {
        printf("ERROR: LOG_FILE.txt cannot be openned\n");
        assembly_struct->err_code = ERR_OPEN_LOG_FILE;
        dtor_asm(assembly_struct);
        exit(-1);
    }
    else
    {
        fprintf(logfile, "-------------------------------------------------\n");
        fprintf(logfile, "assembly_struct->asm_buf: %p\n", assembly_struct->asm_buf);
        fprintf(logfile, "assembly_struct->asm_file: %p\n", assembly_struct->asm_file);
        fprintf(logfile, "assembly_struct->err_code: %ld (%s)\n", assembly_struct->err_code, enum_struct_err_to_string(assembly_struct->err_code));
        fprintf(logfile, "FUNC_NAME: %s\n", FUNCT_NAME);
        fprintf(logfile, "FUNC_LINE: %d\n", FUNCT_LINE);  
        fprintf(logfile, "assembly_struct->num_toks:: %ld\n", assembly_struct->num_toks);
        fprintf(logfile, "assembly_struct->size: %ld\n", assembly_struct->size);
        fprintf(logfile, "assembly_struct->toks: %p\n", assembly_struct->toks);
        fprintf(logfile, "assembly_struct->translated_file: %p\n", assembly_struct->translated_file);
        fprintf(logfile, "TIME: %s\n", __TIME__);
        fprintf(logfile, "DATE: %s\n", __DATE__);
        fprintf(logfile, "FILE: %s\n", __FILE__);
        fprintf(logfile, "-------------------------------------------------\n\n");
    }

    if(fclose(logfile) == EOF)
    {
        printf("ERROR: LOG_FILE.txt cannot be closed\n");
        assembly_struct->err_code = ERR_CLOSE_LOG_FILE;
        dtor_asm(assembly_struct);
        exit(-1);
    }
}

/**
 * @brief                  | (OK) Prints all information about all tokens
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void print_all_toks(asm_struct* assembly_struct)
{
    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {
        printf("\nTOKEN_TEXT: %s\n", assembly_struct->toks[i].text);
        printf("TOKEN_VALUE: %d\n", assembly_struct->toks[i].value);
        printf("TOKEN_TYPE: %ld\n", assembly_struct->toks[i].type);
        printf("TOKEN_STATUS: %s\n", assembly_struct->toks[i].status);
        printf("TOKEN_ERROR_CODE: %ld (%s)\n", assembly_struct->toks[i].error_code, enum_token_err_to_string(assembly_struct->toks[i].error_code));
    }
}

/**
 * @brief                  | (OK) Prints information about the struct 
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void print_struct(asm_struct* assembly_struct) 
{
    printf("\nassembly_struct->asm_buf: %p\n", assembly_struct->asm_buf);
    printf("assembly_struct->asm_file: %p\n", assembly_struct->asm_file);
    printf("assembly_struct->translated_file: %p\n", assembly_struct->translated_file);
    printf("assembly_struct->toks: %p\n", assembly_struct->toks);
    printf("assembly_struct->err_code: %ld\n", assembly_struct->err_code);
    printf("assembly_struct->size: %ld\n", assembly_struct->size);
    printf("assembly_struct->num_toks: %ld\n\n", assembly_struct->num_toks);
}