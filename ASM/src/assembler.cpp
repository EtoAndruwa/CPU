#include "assembler.h"

void file_openning_check(asm_struct* assembly_struct) 
{   
    FILE* test_asm = fopen("test.asm", "rb"); // Opens the file with text
    FILE* test_code = fopen("test_code.bin", "wb"); // Opens an empty file

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
        printf("Files are openned\n");
        assembly_struct->asm_file = test_asm;
        assembly_struct->translated_file = test_code;
    }
}
void get_token_value(asm_struct* assembly_struct, size_t i) 
{
    if((strcmp(assembly_struct->toks[i].text, "ax") == 0) || (strcmp(assembly_struct->toks[i].text, "bx") == 0) || (strcmp(assembly_struct->toks[i].text, "cx") == 0) || (strcmp(assembly_struct->toks[i].text, "dx") == 0))
    {  
        if((((assembly_struct->num_toks - 1) > i) && (check_next_token(assembly_struct, i) == 0) && !(check_next_reg(assembly_struct, i))) || ((assembly_struct->num_toks - 1) == i))
        {
            if(strcmp(assembly_struct->toks[i].text, "ax") == 0)
            {
                assembly_struct->toks[i].value = 21; 
            }
            else if(strcmp(assembly_struct->toks[i].text, "bx") == 0)
            {
                assembly_struct->toks[i].value = 22;
            }
            else if(strcmp(assembly_struct->toks[i].text, "cx") == 0)
            {
                assembly_struct->toks[i].value = 23;
            }
            else
            {   
                assembly_struct->toks[i].value = 24;
            }
            assembly_struct->toks[i].type = reg;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_TOKEN_WITHOUT_VALUE;
        }
    }
    else if(strcmp(assembly_struct->toks[i].text, "PUSH") == 0)
    {  
        if(((assembly_struct->num_toks - 1) > i) && (check_next_token(assembly_struct, i)))
        {   
            assembly_struct->toks[i].value = 1 | (1 << 5);
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {   
            if(((assembly_struct->num_toks - 1) > i) && check_next_reg(assembly_struct, i))
            {
                assembly_struct->toks[i].value = 1 | (1 << 6);
                assembly_struct->toks[i].type = cmd;
                strcpy((char*)assembly_struct->toks[i].status, "OK");
            }
            else
            {
                strcpy((char*)assembly_struct->toks[i].status, "--");
                assembly_struct->toks[i].error_code = ERR_TOKEN_WITH_VALUE;
            }
        }
    }
    else if(strcmp(assembly_struct->toks[i].text, "POP") == 0)
    {     
        if(((assembly_struct->num_toks - 1) > i) && check_next_reg(assembly_struct, i))
        {
            assembly_struct->toks[i].value = 2 | (1 << 6);
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_TOKEN_WITH_VALUE;
        }
    }
    else if(strcmp(assembly_struct->toks[i].text, "ADD") == 0)
    {   
        if((((assembly_struct->num_toks - 1) > i) && !check_next_token(assembly_struct, i) && !(check_next_reg(assembly_struct, i))) || ((assembly_struct->num_toks - 1) == i))
        {
            assembly_struct->toks[i].value = 3;
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_TOKEN_WITHOUT_VALUE;
        }
    }
    else if(strcmp(assembly_struct->toks[i].text, "SUB") == 0)
    {   
        if((((assembly_struct->num_toks - 1) > i) && !check_next_token(assembly_struct, i) && !(check_next_reg(assembly_struct, i))) || ((assembly_struct->num_toks - 1) == i))
        {
            assembly_struct->toks[i].value = 4;
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_TOKEN_WITHOUT_VALUE;
        }
    }
    else if(strcmp(assembly_struct->toks[i].text, "MUL") == 0)
    {   
        if((((assembly_struct->num_toks - 1) > i) && !check_next_token(assembly_struct, i) && !(check_next_reg(assembly_struct, i))) || ((assembly_struct->num_toks - 1) == i))
        {
            assembly_struct->toks[i].value = 5;
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_TOKEN_WITHOUT_VALUE;
        }
    }
    else if(strcmp(assembly_struct->toks[i].text, "DIV") == 0)
    {   
        if((((assembly_struct->num_toks - 1) > i) && !check_next_token(assembly_struct, i) && !(check_next_reg(assembly_struct, i))) || ((assembly_struct->num_toks - 1) == i))
        {
            assembly_struct->toks[i].value = 6;
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_TOKEN_WITHOUT_VALUE;
        }
    }
    else if(strcmp(assembly_struct->toks[i].text, "SQRT") == 0)
    {   
        if((((assembly_struct->num_toks - 1) > i) && !check_next_token(assembly_struct, i) && !(check_next_reg(assembly_struct, i))) || ((assembly_struct->num_toks - 1) == i))
        {
            assembly_struct->toks[i].value = 7;
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_TOKEN_WITHOUT_VALUE;
        }
    }
    else if(strcmp(assembly_struct->toks[i].text, "HLT") == 0)
    {   
        if((((assembly_struct->num_toks - 1) > i) && !check_next_token(assembly_struct, i) && !(check_next_reg(assembly_struct, i))) || ((assembly_struct->num_toks - 1) == i))
        {
            assembly_struct->toks[i].value = 0;
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_TOKEN_WITHOUT_VALUE;
        }
    }
    else if(strcmp(assembly_struct->toks[i].text, "OUT") == 0)
    {   
        if((((assembly_struct->num_toks - 1) > i) && !check_next_token(assembly_struct, i) && !(check_next_reg(assembly_struct, i))) || ((assembly_struct->num_toks - 1) == i))
        {   
            assembly_struct->toks[i].value = 8;
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_TOKEN_WITHOUT_VALUE;
        }
    }
    else if(strcmp(assembly_struct->toks[i].text, "JMP") == 0)
    {
        if(((assembly_struct->num_toks - 1) > i) && (strlen(assembly_struct->toks[i+1].text) > 1) && (check_num_int(assembly_struct->toks[i+1].text + 1) == 1))
        {
            assembly_struct->toks[i].value = 11;
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_NO_FLAG;
        }
    }
    else if(check_num(assembly_struct->toks[i].text) == 1)
    {
        if((((assembly_struct->num_toks - 1) > i) && (check_next_token(assembly_struct, i) == 0) && !(check_next_reg(assembly_struct, i))) || ((assembly_struct->num_toks - 1) == i))
        {
            assembly_struct->toks[i].value = 9;
            assembly_struct->toks[i].type = val;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_TOKEN_WITHOUT_VALUE;
        }
    }
    else if((assembly_struct->toks[i].text[0] == ':') && (strlen(assembly_struct->toks[i].text) > 1))
    {
        if(check_num_int(assembly_struct->toks[i].text + 1) == 1)
        {   
            assembly_struct->toks[i].type = flg;
            strcpy((char*)assembly_struct->toks[i].status, "OK"); 
        }
        else
        {   
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_INVALID_FLAG;;
        }
    }
    else if((strcmp(assembly_struct->toks[i].text, "rax") == 0) || (strcmp(assembly_struct->toks[i].text, "rbx") == 0) || (strcmp(assembly_struct->toks[i].text, "rcx") == 0))
    {
        if((((assembly_struct->num_toks - 1) > i) && (check_next_token(assembly_struct, i) == 0) && !(check_next_reg(assembly_struct, i))) || ((assembly_struct->num_toks - 1) == i))
        {   
            if(strcmp(assembly_struct->toks[i].text, "rax") == 0)
            {
                assembly_struct->toks[i].value = 25; 
            }
            else if(strcmp(assembly_struct->toks[i].text, "rbx") == 0)
            {
                assembly_struct->toks[i].value = 26;
            }
            else if(strcmp(assembly_struct->toks[i].text, "rcx") == 0)
            {
                assembly_struct->toks[i].value = 27;
            }
            assembly_struct->toks[i].type = reg;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else    
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_TOKEN_WITHOUT_VALUE;
        }
    }
    else if(strcmp(assembly_struct->toks[i].text, "CALL") == 0)
    {
        if(((assembly_struct->num_toks - 1) > i) && (check_next_token(assembly_struct, i) == 0) && (assembly_struct->toks[i+1].text[(strlen(assembly_struct->toks[i+1].text) - 1)] == ':'))
        {
            assembly_struct->toks[i].value = 30;
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_NO_FNC_NAME;
        }
    }
    else if((assembly_struct->toks[i].text[(strlen(assembly_struct->toks[i].text) - 1)] == ':'))
    {
        assembly_struct->toks[i].type = fnc;
        strcpy((char*)assembly_struct->toks[i].status, "OK");
    }
    else if(strcmp(assembly_struct->toks[i].text, "RET") == 0)
    {
        if((((assembly_struct->num_toks - 1) > i) && !check_next_token(assembly_struct, i) && !(check_next_reg(assembly_struct, i))) || ((assembly_struct->num_toks - 1) == i))
        {
            assembly_struct->toks[i].value = 10;
            assembly_struct->toks[i].type = ret;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_TOKEN_WITHOUT_VALUE;
        }
    }
    else
    {
        strcpy((char*)assembly_struct->toks[i].status, "--");
        assembly_struct->toks[i].error_code = ERR_INVALID_TOKEN;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE);
    }
}
void get_commands_into_buf(asm_struct* assembly_struct) 
{
    rewind(assembly_struct->asm_file); // Puts the pointer inside the file to the start of the file 

    assembly_struct->asm_buf = (char*)calloc(1, sizeof(char) * (assembly_struct->size + 1)); // Allocates enough memmory for the buffer of chars  
    size_t num_read = fread(assembly_struct->asm_buf, sizeof(char), assembly_struct->size, assembly_struct->asm_file); // Reads the file into the buffer
    assembly_struct->asm_buf[assembly_struct->size] = '\0'; // Makes form the file null-terminated string

    rewind(assembly_struct->asm_file); // Puts the pointer inside the file to the start of the file
}
void get_size_asm(asm_struct* assembly_struct) 
{
    rewind(assembly_struct->asm_file); // Puts the pointer inside the file to the start of the file 

    fseek(assembly_struct->asm_file, 0, SEEK_END); // Puts the pointer inside the file to the end of it
    assembly_struct->size = ftell(assembly_struct->asm_file); // Get the size of the file with '\r'!

    if(assembly_struct->size == 0) 
    {
        assembly_struct->err_code = ERR_EMPTY_ASM_FILE; 
        dtor_asm(assembly_struct);
        exit(-1);
    } 

    rewind(assembly_struct->asm_file); // Puts the pointer inside the file to the start of the file 
}
void dtor_asm(asm_struct* assembly_struct) 
{
    dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE);

    free(assembly_struct->asm_codes);
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

    assembly_struct->asm_codes = nullptr;
    assembly_struct->toks = nullptr;
    assembly_struct->asm_file = nullptr;
    assembly_struct->translated_file = nullptr;
    assembly_struct->asm_buf = nullptr;
    assembly_struct->err_code = 0;
    assembly_struct->size = 0;
    assembly_struct->num_toks = 0;
}
void get_tokens(asm_struct* assembly_struct) 
{
    char* token = strtok(assembly_struct->asm_buf," \n\r");
    assembly_struct->toks = (tokens*)calloc(1, sizeof(tokens));

    size_t toks_num = 0;
    while (token != NULL)                        
    {   
        realloc_toks(assembly_struct, toks_num); // Reallocs the struct with tokens
        assembly_struct->toks[toks_num].text = token; // Adds the new token to the array
        token = strtok(NULL, " \n\r");
        toks_num++;
    }

}
void realloc_toks(asm_struct* assembly_struct, size_t i) 
{
    if(assembly_struct->num_toks == i)
    {
        assembly_struct->num_toks++;
        assembly_struct->toks = (tokens*)realloc(assembly_struct->toks, assembly_struct->num_toks * sizeof(tokens)); // The pointer to the array of structs
    }
}
void translate_to_asm(asm_struct* assembly_struct)  
{
    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {
        get_token_value(assembly_struct, i);
    }
}
void write_asm(asm_struct* assembly_struct) 
{   
    if(check_all_valid(assembly_struct) && check_flags(assembly_struct) && check_func(assembly_struct) && check_fnc_declaration(assembly_struct)) // Rules
    {
        for(size_t i = 0; i < assembly_struct->num_toks; i++)
        {   
            char* ptr_end_strtod = nullptr;
            if((assembly_struct->toks[i].type == flg))
            {
                if((i > 0) && (assembly_struct->toks[i-1].value == 11))
                {
                    fprintf(assembly_struct->translated_file, "%d\n", assembly_struct->toks[i].value);
                }
                else
                {   
                    i++;
                }
            }
            else if(assembly_struct->toks[i].type == fnc)
            {
                if((i > 0) && (assembly_struct->toks[i-1].value == 30))
                {
                    fprintf(assembly_struct->translated_file, "%d\n", assembly_struct->toks[i].value);
                }
                else
                {   
                    fputc('\n', assembly_struct->translated_file);
                    i++;
                }
            }
            else if(assembly_struct->toks[i].type == val)
            {
                float code = atof(assembly_struct->toks[i].text);
                fwrite(&code, sizeof(code), 1, assembly_struct->translated_file);
                fputc('\n', assembly_struct->translated_file);
            }
            else 
            {
                fprintf(assembly_struct->translated_file, "%d\n", assembly_struct->toks[i].value);
            }
        }
        printf("Success\n");
    }
    else
    {
        printf("ERROR: asm.txt cannot be translated into binary file. Check LOG_FILE.txt and asm_listing.txt\n");
    }
}

void get_arr_asm_codes(asm_struct* assembly_struct)
{
    assembly_struct->asm_codes = (int*)calloc(assembly_struct->num_toks, sizeof(int));

    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {
        assembly_struct->asm_codes[i] = assembly_struct->toks[i].value;
    }

    printf("ASM_ARR");
    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {   
        printf("%d ", assembly_struct->asm_codes[i]);
    }
    printf("\n");
}