#include "assembler.h"

size_t listing(asm_struct* assembly_struct)
{
    FILE* listing_file = fopen(FILE_LISTING_NAME, "wb");

    if(listing_file == nullptr)
    {
        assembly_struct->err_code = ERR_OPEN_LISTING;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, assembly_struct->err_code)
        return assembly_struct->err_code;
    }

    fprintf(listing_file,"| ID |		%-*s		|    TYPE    |		%-*s		|    STATUS    |\n", assembly_struct->length_listing, "COMMAND", assembly_struct->length_listing - 4, "ASM");
    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {   
        if(check_is_float(assembly_struct->toks[i].text) == TOKEN_IS_FLT)
        {
            fprintf(listing_file,"|%03d|		%-*s		|    %s     |		%-*lf		|      %s      |", assembly_struct->toks[i].new_index, assembly_struct->length_listing, assembly_struct->toks[i].text, get_tok_type_string(assembly_struct->toks[i].type), assembly_struct->length_listing - 4, assembly_struct->toks[i].value.flt_val, assembly_struct->toks[i].status);
        }
        else
        {
            fprintf(listing_file,"|%03d|		%-*s		|    %s     |		%-*d		|      %s      |", assembly_struct->toks[i].new_index, assembly_struct->length_listing, assembly_struct->toks[i].text, get_tok_type_string(assembly_struct->toks[i].type), assembly_struct->length_listing - 4, assembly_struct->toks[i].value.int_val, assembly_struct->toks[i].status);
        }
        if(strcmp(assembly_struct->toks[i].status, "--") == 0)
        {
            fprintf(listing_file, " <----- %s", get_tok_err_code_string(assembly_struct->toks[i].error_code)); 
        }
        fprintf(listing_file, "\n");
    }

    if(fclose(listing_file) == EOF)
    {
        assembly_struct->err_code = ERR_CLOSE_LISTING;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        ERROR_MESSAGE(stderr, assembly_struct->err_code)
        return assembly_struct->err_code;
    }
}

size_t dump_asm(asm_struct* assembly_struct, const char* func_name, int func_line, const char* func_file) 
{
    FILE* logfile = fopen(FILE_LOG_NAME, "wb");

    if(logfile == nullptr)
    {
        assembly_struct->err_code = ERR_OPEN_LOG_FILE;
        ERROR_MESSAGE(stderr, assembly_struct->err_code)
        return assembly_struct->err_code;
    }
    else
    {
        fprintf(logfile, "\n-------------------STRUCT_DATA-------------------\n");
        fprintf(logfile, "ERROR CODE: %ld (%s)\n", assembly_struct->err_code, get_asm_err_code_string(assembly_struct->err_code));
        fprintf(logfile, "ASM BUFFER ADDRESS: %p\n", assembly_struct->asm_buf);
        fprintf(logfile, "ASM FILE PTR %p\n", assembly_struct->asm_file_ptr);
        fprintf(logfile, "NUMBER OF TOKENS: %ld\n", assembly_struct->num_toks);
        fprintf(logfile, "SIZE OF THE FILE: %ld\n", assembly_struct->size);
        fprintf(logfile, "TOKENS PTR: %p\n", assembly_struct->toks);
        fprintf(logfile, "TRANSLATED FILE PTR: %p\n", assembly_struct->bin_file_ptr);
        fprintf(logfile, "-------------------STRUCT_DATA-------------------\n");

        fprintf(logfile, "\n-------------------DUMP_DATA-------------------\n");
        fprintf(logfile, "FILE NAME: %s\n", func_file);
        fprintf(logfile, "FUNCTION NAME: %s\n", func_name);
        fprintf(logfile, "LINE: %d\n", func_line);
        fprintf(logfile, "TIME: %s\n", __TIME__);
        fprintf(logfile, "DATE: %s\n", __DATE__);
        fprintf(logfile, "-------------------DUMP_DATA-------------------\n");
    }

    if(fclose(logfile) == EOF)
    {
        assembly_struct->err_code = ERR_CLOSE_LOG_FILE;
        ERROR_MESSAGE(stderr, assembly_struct->err_code)
        return assembly_struct->err_code;
    }
}

void print_all_toks(asm_struct* assembly_struct) // CHECKED
{
    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {
        printf("\n##################################################\n");
        printf("TOKEN_TEXT: %s\n", assembly_struct->toks[i].text);

        if(check_is_float(assembly_struct->toks[i].text) == TOKEN_IS_FLT)
        {
            printf("TOKEN_VALUE: %f\n", assembly_struct->toks[i].value.flt_val);
        }
        else
        {
            printf("TOKEN_VALUE: %d\n", assembly_struct->toks[i].value.int_val);
        }
        printf("TOKEN_TYPE: %ld\n", assembly_struct->toks[i].type);
        printf("TOKEN_STATUS: %s\n", assembly_struct->toks[i].status);
        printf("TOKEN_NEW_INDEX: %d\n", assembly_struct->toks[i].new_index);
        printf("TOKEN_ERROR_CODE: %d (%s)\n", assembly_struct->toks[i].error_code, get_tok_err_code_string(assembly_struct->toks[i].error_code));
        printf("##################################################\n");
    }
}

void print_struct(asm_struct* assembly_struct) // CHECKED
{
    printf("\nassembly_struct->asm_buf: %p\n", assembly_struct->asm_buf);
    printf("assembly_struct->asm_file_ptr: %p\n", assembly_struct->asm_file_ptr);
    printf("assembly_struct->bin_file_ptr: %p\n", assembly_struct->bin_file_ptr);
    printf("assembly_struct->toks: %p\n", assembly_struct->toks);
    printf("assembly_struct->err_code: %ld\n", assembly_struct->err_code);
    printf("assembly_struct->size: %ld\n", assembly_struct->size);
    printf("assembly_struct->num_toks: %ld\n\n", assembly_struct->num_toks);
}
