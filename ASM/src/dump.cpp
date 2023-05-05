#include "assembler.h"

size_t listing(asm_struct* assembly_struct)
{
    FILE* listing_file = fopen(FILE_LISTING_NAME, "wb");

    if(listing_file == nullptr)
    {
        assembly_struct->err_code = ERR_OPEN_LISTING;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        dtor_asm(assembly_struct);
        return assembly_struct->err_code;
    }

    fprintf(listing_file,"| ID |		%-*s		|    TYPE    |		%-*s		|    STATUS    |\n", assembly_struct->length_listing, "COMMAND", assembly_struct->length_listing - 4, "ASM");
    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {   
        fprintf(listing_file,"|%03d|		%-*s		|    %s     |		%-*d		|      %s      |", assembly_struct->toks[i].new_index, assembly_struct->length_listing, assembly_struct->toks[i].text, enum_type_to_string(assembly_struct->toks[i].type), assembly_struct->length_listing - 4, assembly_struct->toks[i].value, assembly_struct->toks[i].status);
        if(strcmp(assembly_struct->toks[i].status, "--") == 0)
        {
            fprintf(listing_file, " <----- %s", enum_token_err_to_string(assembly_struct->toks[i].error_code)); 
        }
        fprintf(listing_file, "\n");
    }

    if(fclose(listing_file) == EOF)
    {
        assembly_struct->err_code = ERR_CLOSE_LISTING;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        dtor_asm(assembly_struct);
        return assembly_struct->err_code;
    }
}

size_t dump_asm(asm_struct* assembly_struct, const char* func_name, int func_line, const char* func_file) 
{
    FILE* logfile = fopen(FILE_LOG_NAME, "wb");

    if(logfile == nullptr)
    {
        assembly_struct->err_code = ERR_OPEN_LOG_FILE;
        dtor_asm(assembly_struct);
        return assembly_struct->err_code;
    }
    else
    {
        fprintf(logfile, "\n-------------------STRUCT_DATA-------------------\n");
        fprintf(logfile, "ERROR CODE: %ld (%s)\n", assembly_struct->err_code, enum_struct_err_to_string(assembly_struct->err_code));
        fprintf(logfile, "ASM BUFFER ADDRESS: %p\n", assembly_struct->asm_buf);
        fprintf(logfile, "ASM FILE PTR %p\n", assembly_struct->asm_file);
        fprintf(logfile, "NUMBER OF TOKENS: %ld\n", assembly_struct->num_toks);
        fprintf(logfile, "SIZE OF THE FILE: %ld\n", assembly_struct->size);
        fprintf(logfile, "TOKENS PTR: %p\n", assembly_struct->toks);
        fprintf(logfile, "TRANSLATED FILE PTR: %p\n", assembly_struct->translated_file);
        fprintf(logfile, "-------------------STRUCT_DATA-------------------\n");

        fprintf(logfile, "\n-------------------DUMP_DATA-------------------\n");
        fprintf(logfile, "File name: %s\n", func_file);
        fprintf(logfile, "Function name: %s\n", func_name);
        fprintf(logfile, "Line: %d\n", func_line);
        fprintf(logfile, "Time: %s\n", __TIME__);
        fprintf(logfile, "Date: %s\n", __DATE__);
        fprintf(logfile, "-------------------DUMP_DATA-------------------\n");
    }

    if(fclose(logfile) == EOF)
    {
        assembly_struct->err_code = ERR_CLOSE_LOG_FILE;
        dtor_asm(assembly_struct);
        return assembly_struct->err_code;
    }
}

void print_all_toks(asm_struct* assembly_struct)
{
    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {
        printf("\nTOKEN_TEXT: %s\n", assembly_struct->toks[i].text);
        printf("TOKEN_VALUE: %d\n", assembly_struct->toks[i].value);
        printf("TOKEN_TYPE: %ld\n", assembly_struct->toks[i].type);
        printf("TOKEN_STATUS: %s\n", assembly_struct->toks[i].status);
        printf("TOKEN_NEW_INDEX: %d\n", assembly_struct->toks[i].new_index);
        printf("TOKEN_ERROR_CODE: %ld (%s)\n", assembly_struct->toks[i].error_code, enum_token_err_to_string(assembly_struct->toks[i].error_code));
    }
}

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
