#include "assembler.h"

void file_openning_check(asm_struct* assembly_struct) // (OK) Opens and checks files with assembly code and translated code
{   
    FILE* test_asm = fopen("test.asm", "rb"); // Opens file with text
    FILE* test_code = fopen("test_code.txt", "wb"); // Opens empty file

    if(test_asm == nullptr)
    {
        assembly_struct->err_code = ERR_OPEN_ASM_FILE;
        printf("ERROR: unable to open file %s.\n", FILE_1);
    }
    if(test_code == nullptr)
    {   
        assembly_struct->err_code = ERR_OPEN_TRANSLATED_FILE;
        printf("ERROR: unable to open file %s.\n", FILE_2);
    }
    if(assembly_struct->err_code != 0)
    {
        dtor_asm(assembly_struct);
        exit(-1);
    }
    else
    {   
        printf("OK\n");
        assembly_struct->asm_file = test_asm;
        assembly_struct->translated_file = test_code;
    }
}


void get_token_value(asm_struct* assembly_struct, size_t i) // (OK) Puts appropriate asm code to the each token 
{
    if(strcmp(assembly_struct->toks[i].text, "PUSH") == 0)
    {  
        assembly_struct->toks[i].value = 1;
        assembly_struct->toks[i].type = cmd;
    }
    else if(strcmp(assembly_struct->toks[i].text, "POP") == 0)
    {   
        assembly_struct->toks[i].value = 2;
        assembly_struct->toks[i].type = cmd;
    }
    else if(strcmp(assembly_struct->toks[i].text, "ADD") == 0)
    {   
        assembly_struct->toks[i].value = 3;
        assembly_struct->toks[i].type = cmd;
    }
    else if(strcmp(assembly_struct->toks[i].text, "SUB") == 0)
    {   
        assembly_struct->toks[i].value = 4;
        assembly_struct->toks[i].type = cmd;
    }
    else if(strcmp(assembly_struct->toks[i].text, "MUL") == 0)
    {   
        assembly_struct->toks[i].value = 5;
        assembly_struct->toks[i].type = cmd;
    }
    else if(strcmp(assembly_struct->toks[i].text, "DIV") == 0)
    {   
        assembly_struct->toks[i].value = 6;
        assembly_struct->toks[i].type = cmd;
    }
    else if(strcmp(assembly_struct->toks[i].text, "SQRT") == 0)
    {   
        assembly_struct->toks[i].value = 7;
        assembly_struct->toks[i].type = cmd;
    }
    else if(strcmp(assembly_struct->toks[i].text, "HLT") == 0)
    {   
        assembly_struct->toks[i].value = 0;
        assembly_struct->toks[i].type = cmd;
    }
    else if(strcmp(assembly_struct->toks[i].text, "OUT") == 0)
    {   
        assembly_struct->toks[i].value = 8;
        assembly_struct->toks[i].type = cmd;
    }
    else if(check_num(assembly_struct->toks[i].text) == 1)
    {
        assembly_struct->toks[i].value = 9;
        assembly_struct->toks[i].type = val;
    }
    else if(((assembly_struct->num_toks - 1) == i) && (strcmp(assembly_struct->toks[i].text, "HLT") != 0))
    {
        assembly_struct->err_code = ERR_NO_HLT;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE);
        dtor_asm(assembly_struct);
    }
    else
    {
        assembly_struct->err_code = ERR_LEXICAL_ERROR;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE);
        dtor_asm(assembly_struct);
    }
}

// void write_code_push(FILE * test_asm, FILE * test_code, int command_id, double push_value)
// {   
//     fprintf(test_code, "%d %f\n", command_id, push_value);
// }

// void write_code_other(FILE * test_asm, FILE * test_code, int command_id)
// {   
//     fprintf(test_code, "%d\n", command_id);
// }

void get_commands_into_buf(asm_struct* assembly_struct) // (OK) Creates buffer for commands and copies all commands into it
{
    rewind(assembly_struct->asm_file);

    assembly_struct->asm_buf = (char*)calloc(1, sizeof(char) * (assembly_struct->size + 1));
    fread(assembly_struct->asm_buf, sizeof(char), assembly_struct->size, assembly_struct->asm_file);
    assembly_struct->asm_buf[assembly_struct->size] = '\0';

    rewind(assembly_struct->asm_file);
}

void get_size_asm(asm_struct* assembly_struct) // (OK) Gets the size of asm code file 
{
    rewind(assembly_struct->asm_file);
    fseek(assembly_struct->asm_file, 0, SEEK_END);
    assembly_struct->size = ftell(assembly_struct->asm_file);

    if(assembly_struct->size == 0)
    {
        assembly_struct->err_code = ERR_EMPTY_ASM_FILE; 

        dtor_asm(assembly_struct);
    } 

    rewind(assembly_struct->asm_file);
}

void dtor_asm(asm_struct* assembly_struct) // (OK) Closes all file, frees all pointers, deletes all data of struct
{
    free(assembly_struct->asm_buf);
    free(assembly_struct->toks);
    if(fclose(assembly_struct->asm_file) == EOF)
    {
        printf("ERROR: %s.txt cannot be closed\n", FILE_1);
        assembly_struct->err_code = ERR_EMPTY_ASM_FILE;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE);
        exit(-1);
    }
    if(fclose(assembly_struct->translated_file) == EOF)
    {   
        printf("ERROR: %s.txt cannot be closed\n", FILE_2);
        assembly_struct->err_code = ERR_CLOSE_TRANSLATED_FILE;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE);
        exit(-1);
    }

    assembly_struct->toks = nullptr;
    assembly_struct->asm_file = nullptr;
    assembly_struct->translated_file = nullptr;
    assembly_struct->asm_buf = nullptr;
    assembly_struct->err_code = 0;
    assembly_struct->size = 0;
    assembly_struct->num_toks = 0;
    
}

void get_tokens(asm_struct* assembly_struct) // (OK) Gets all tokens from the buffer 
{
    char* token = strtok(assembly_struct->asm_buf," \n\r");
    assembly_struct->toks = (tokens*)calloc(1, sizeof(tokens));
    
    int i = 0;
    while (token != NULL)                        
    {   
        realloc_toks(assembly_struct, i);
        printf("token %d: %s\n", i,token);
        assembly_struct->toks[i].text = token;
        token = strtok (NULL, " \n\r");
        i++;
    }

    free(token);
}

void print_struct(asm_struct* assembly_struct) // (OK) Prints information about the struct 
{
    printf("\nasm_buf: %p\n", assembly_struct->asm_buf);
    printf("asm_file: %p\n", assembly_struct->asm_file);
    printf("translated_file: %p\n", assembly_struct->translated_file);
    printf("size: %ld\n", assembly_struct->size);
    printf("err_code: %ld\n\n", assembly_struct->err_code);
}

void realloc_toks(asm_struct* assembly_struct, size_t i) // (OK) Reallocs the array with tokens
{
    if(assembly_struct->num_toks == i)
    {
        assembly_struct->num_toks++;
        assembly_struct->toks = (tokens*)realloc(assembly_struct->toks, assembly_struct->num_toks * sizeof(tokens));
    }
}

void print_all_toks(asm_struct* assembly_struct) // (OK) Prints all information about the tokens
{
    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {
        printf("TOKEN_TEXT: %s\n", assembly_struct->toks[i].text);
        printf("TOKEN_VALUE: %d\n", assembly_struct->toks[i].value);
        printf("TOKEN_TYPE: %d\n\n", assembly_struct->toks[i].type);
    }
}

void translate_to_asm(asm_struct* assembly_struct) // (OK) Gets asm codes for all tokens 
{
    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {
        get_token_value(assembly_struct, i);
    }
}

size_t check_num(char* num_text) // (OK) Checks does the number contain only digits and .
{
    size_t flag = 1;    
    size_t length_text = strlen(num_text);

    for(size_t i  = 0; i < length_text; i++)
    {
        char check_char = num_text[i];

        if((isdigit(check_char) == 0) && (check_char != '.'))
        {
            flag = 0;
        }
    }

    return flag;
}

void dump_asm(asm_struct* assembly_struct, const char * FUNCT_NAME, int FUNCT_LINE) // (OK) Creates LOG_FILE.txt with all information about asm_struct
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
        fprintf(logfile, "assembly_struct->err_code: %ld (%s)\n", assembly_struct->err_code, enum_to_string(assembly_struct->err_code));
        fprintf(logfile, "FUNC_NAME: %s\n", FUNC_NAME);
        fprintf(logfile, "FUNC_LINE: %d\n", FUNC_LINE);  
        fprintf(logfile, "assembly_struct->num_toks:: %ld\n", assembly_struct->num_toks);
        fprintf(logfile, "assembly_struct->size: %ld\n", assembly_struct->size);
        fprintf(logfile, "assembly_struct->toks: %p\n", assembly_struct->toks);
        fprintf(logfile, "assembly_struct->translated_file: %p\n", assembly_struct->translated_file);
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

const char* enum_to_string(size_t code) // (OK) Сonverts an enum's int value to the enum's string value
{
    switch(code)
    {
        case ERR_ASM_CODE_BUF_NULL:
            return "ERR_ASM_CODE_BUF_NULL";
            break;
        case ERR_CLOSE_ASM_FILE:
            return "ERR_CLOSE_ASM_FILE";
            break;
        case ERR_CLOSE_LOG_FILE:
            return "ERR_CLOSE_LOG_FILE";
            break;
        case ERR_CLOSE_TRANSLATED_FILE:
            return "ERR_CLOSE_TRANSLATED_FILE";
            break;
        case ERR_EMPTY_ASM_FILE:
            return "ERR_EMPTY_ASM_FILE";
            break;
        case ERR_LEXICAL_ERROR:
            return "ERR_LEXICAL_ERROR";
            break;
        case ERR_NO_HLT:
            return "ERR_NO_HLT";
            break;
        case ERR_OPEN_ASM_FILE:
            return "ERR_OPEN_ASM_FILE";
            break;
        case ERR_OPEN_LOG_FILE:
            return "ERR_OPEN_LOG_FILE";
            break;
        case ERR_OPEN_TRANSLATED_FILE:
            return "ERR_OPEN_TRANSLATED_FILE";
            break;
        default:
            return "IS OK"; 
            break;
    }
}


void listing()
{
    FILE* listing_file = fopen("asm_listing.txt", "wb");

    fprintf();






    fprintf();

    fclose(listing_file);
}

