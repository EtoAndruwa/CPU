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

void get_token_value(asm_struct* assembly_struct, size_t cur_tok_chk) 
{
    if((strcmp(assembly_struct->toks[cur_tok_chk].text, "ax") == 0) || (strcmp(assembly_struct->toks[cur_tok_chk].text, "bx") == 0) || (strcmp(assembly_struct->toks[cur_tok_chk].text, "cx") == 0) || (strcmp(assembly_struct->toks[cur_tok_chk].text, "dx") == 0))
    {  
        if((((assembly_struct->num_toks - 1) > cur_tok_chk) && (check_next_token(assembly_struct, cur_tok_chk) == 0) && !(check_next_reg(assembly_struct, cur_tok_chk))) || ((assembly_struct->num_toks - 1) == cur_tok_chk))
        {
            if(strcmp(assembly_struct->toks[cur_tok_chk].text, "ax") == 0)
            {
                assembly_struct->toks[cur_tok_chk].value = 21; 
            }
            else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "bx") == 0)
            {
                assembly_struct->toks[cur_tok_chk].value = 22;
            }
            else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "cx") == 0)
            {
                assembly_struct->toks[cur_tok_chk].value = 23;
            }
            else
            {   
                assembly_struct->toks[cur_tok_chk].value = 24;
            }
            assembly_struct->toks[cur_tok_chk].type = reg;  
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
        }
        else
        {
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
            assembly_struct->toks[cur_tok_chk].error_code = ERR_TOKEN_WITHOUT_VALUE;
        }
        assembly_struct->cur_tok_chk++;
    }
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "PUSH") == 0)
    {  
        if(((assembly_struct->num_toks - 1) > cur_tok_chk) && (check_next_token(assembly_struct, cur_tok_chk)))
        {   
            assembly_struct->toks[cur_tok_chk].value = 1 | (1 << 5);
            assembly_struct->toks[cur_tok_chk].type = cmd;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
            assembly_struct->cur_tok_chk++;
        }
        else
        {   
            if(((assembly_struct->num_toks - 1) > cur_tok_chk) && check_next_reg(assembly_struct, cur_tok_chk))
            {
                assembly_struct->toks[cur_tok_chk].value = 1 | (1 << 6);
                assembly_struct->toks[cur_tok_chk].type = cmd;
                strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
                assembly_struct->cur_tok_chk++;
            }
            else if(((assembly_struct->num_toks - 1) > cur_tok_chk) && (check_ram(assembly_struct, assembly_struct->toks[cur_tok_chk + 1].text, cur_tok_chk + 1) == 1))
            {
                assembly_struct->toks[cur_tok_chk].value = 1 | (5 << 5);
                assembly_struct->toks[cur_tok_chk].type = cmd;
                strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
                assembly_struct->cur_tok_chk = assembly_struct->cur_tok_chk + 2; // Skips [val] token
            }
            else if(((assembly_struct->num_toks - 1) > cur_tok_chk) && (check_ram(assembly_struct, assembly_struct->toks[cur_tok_chk + 1].text, cur_tok_chk + 1) == 2))
            {
                assembly_struct->toks[cur_tok_chk].value = 1 | (3 << 6);
                assembly_struct->toks[cur_tok_chk].type = cmd;
                strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
                assembly_struct->cur_tok_chk = assembly_struct->cur_tok_chk + 2; // Skips [reg] token
            }
            else
            {
                strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
                assembly_struct->toks[cur_tok_chk].error_code = ERR_TOKEN_WITH_VALUE;
                assembly_struct->cur_tok_chk++;
            }
        }
    }
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "POP") == 0)
    {     
        if(((assembly_struct->num_toks - 1) > cur_tok_chk) && check_next_reg(assembly_struct, cur_tok_chk))
        {
            assembly_struct->toks[cur_tok_chk].value = 2 | (1 << 6);
            assembly_struct->toks[cur_tok_chk].type = cmd;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
            assembly_struct->cur_tok_chk++;
        }
        else if(((assembly_struct->num_toks - 1) > cur_tok_chk) && (check_ram(assembly_struct, assembly_struct->toks[cur_tok_chk + 1].text, cur_tok_chk + 1) == 1))
        {
            assembly_struct->toks[cur_tok_chk].value = 2 | (5 << 5);
            assembly_struct->toks[cur_tok_chk].type = cmd;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
            assembly_struct->cur_tok_chk = assembly_struct->cur_tok_chk + 2; // Skips [val] token
        }
        else if(((assembly_struct->num_toks - 1) > cur_tok_chk) && (check_ram(assembly_struct, assembly_struct->toks[cur_tok_chk + 1].text, cur_tok_chk + 1) == 2))
        {
            assembly_struct->toks[cur_tok_chk].value = 2 | (3 << 6);
            assembly_struct->toks[cur_tok_chk].type = cmd;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
            assembly_struct->cur_tok_chk = assembly_struct->cur_tok_chk + 2; // Skips [reg] token
        }
        else
        {
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
            assembly_struct->toks[cur_tok_chk].error_code = ERR_TOKEN_WITH_VALUE;
            assembly_struct->cur_tok_chk++;
        }
    }
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "ADD") == 0)
    {   
        if((((assembly_struct->num_toks - 1) > cur_tok_chk) && !check_next_token(assembly_struct, cur_tok_chk) && !(check_next_reg(assembly_struct, cur_tok_chk))) || ((assembly_struct->num_toks - 1) == cur_tok_chk))
        {
            assembly_struct->toks[cur_tok_chk].value = 3;
            assembly_struct->toks[cur_tok_chk].type = cmd;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
            assembly_struct->cur_tok_chk++;
        }
        else
        {
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
            assembly_struct->toks[cur_tok_chk].error_code = ERR_TOKEN_WITHOUT_VALUE;
            assembly_struct->cur_tok_chk++;
        }
    }
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "SUB") == 0)
    {   
        if((((assembly_struct->num_toks - 1) > cur_tok_chk) && !check_next_token(assembly_struct, cur_tok_chk) && !(check_next_reg(assembly_struct, cur_tok_chk))) || ((assembly_struct->num_toks - 1) == cur_tok_chk))
        {
            assembly_struct->toks[cur_tok_chk].value = 4;
            assembly_struct->toks[cur_tok_chk].type = cmd;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
            assembly_struct->cur_tok_chk++;
        }
        else
        {
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
            assembly_struct->toks[cur_tok_chk].error_code = ERR_TOKEN_WITHOUT_VALUE;
            assembly_struct->cur_tok_chk++;
        }
    }
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "MUL") == 0)
    {   
        if((((assembly_struct->num_toks - 1) > cur_tok_chk) && !check_next_token(assembly_struct, cur_tok_chk) && !(check_next_reg(assembly_struct, cur_tok_chk))) || ((assembly_struct->num_toks - 1) == cur_tok_chk))
        {
            assembly_struct->toks[cur_tok_chk].value = 5;
            assembly_struct->toks[cur_tok_chk].type = cmd;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
            assembly_struct->cur_tok_chk++;
        }
        else
        {
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
            assembly_struct->toks[cur_tok_chk].error_code = ERR_TOKEN_WITHOUT_VALUE;
            assembly_struct->cur_tok_chk++;
        }
    }
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "DIV") == 0)
    {   
        if((((assembly_struct->num_toks - 1) > cur_tok_chk) && !check_next_token(assembly_struct, cur_tok_chk) && !(check_next_reg(assembly_struct, cur_tok_chk))) || ((assembly_struct->num_toks - 1) == cur_tok_chk))
        {
            assembly_struct->toks[cur_tok_chk].value = 6;
            assembly_struct->toks[cur_tok_chk].type = cmd;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
            assembly_struct->cur_tok_chk++;
        }
        else
        {
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
            assembly_struct->toks[cur_tok_chk].error_code = ERR_TOKEN_WITHOUT_VALUE;
            assembly_struct->cur_tok_chk++;
        }
    }
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "SQRT") == 0)
    {   
        if((((assembly_struct->num_toks - 1) > cur_tok_chk) && !check_next_token(assembly_struct, cur_tok_chk) && !(check_next_reg(assembly_struct, cur_tok_chk))) || ((assembly_struct->num_toks - 1) == cur_tok_chk))
        {
            assembly_struct->toks[cur_tok_chk].value = 7;
            assembly_struct->toks[cur_tok_chk].type = cmd;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
            assembly_struct->cur_tok_chk++;
        }
        else
        {
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
            assembly_struct->toks[cur_tok_chk].error_code = ERR_TOKEN_WITHOUT_VALUE;
            assembly_struct->cur_tok_chk++;
        }
    }
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "HLT") == 0)
    {   
        if((((assembly_struct->num_toks - 1) > cur_tok_chk) && !check_next_token(assembly_struct, cur_tok_chk) && !(check_next_reg(assembly_struct, cur_tok_chk))) || ((assembly_struct->num_toks - 1) == cur_tok_chk))
        {
            assembly_struct->toks[cur_tok_chk].value = 0;
            assembly_struct->toks[cur_tok_chk].type = cmd;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
            assembly_struct->cur_tok_chk++;
        }
        else
        {
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
            assembly_struct->toks[cur_tok_chk].error_code = ERR_TOKEN_WITHOUT_VALUE;
            assembly_struct->cur_tok_chk++;
        }
    }
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "OUT") == 0)
    {   
        if((((assembly_struct->num_toks - 1) > cur_tok_chk) && !check_next_token(assembly_struct, cur_tok_chk) && !(check_next_reg(assembly_struct, cur_tok_chk))) || ((assembly_struct->num_toks - 1) == cur_tok_chk))
        {   
            assembly_struct->toks[cur_tok_chk].value = 8;
            assembly_struct->toks[cur_tok_chk].type = cmd;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
            assembly_struct->cur_tok_chk++;
        }
        else
        {
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
            assembly_struct->toks[cur_tok_chk].error_code = ERR_TOKEN_WITHOUT_VALUE;
            assembly_struct->cur_tok_chk++;
        }
    }
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "JMP") == 0)
    {
        if(((assembly_struct->num_toks - 1) > cur_tok_chk) && (strlen(assembly_struct->toks[cur_tok_chk + 1].text) > 1) && (check_num_int(assembly_struct->toks[cur_tok_chk + 1].text + 1) == 1))
        {
            assembly_struct->toks[cur_tok_chk].value = 11;
            assembly_struct->toks[cur_tok_chk].type = cmd;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
            assembly_struct->cur_tok_chk++;
        }
        else
        {
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
            assembly_struct->toks[cur_tok_chk].error_code = ERR_NO_FLAG;
            assembly_struct->cur_tok_chk++;
        }
    }
    else if(check_num(assembly_struct->toks[cur_tok_chk].text) == 1)
    {
        if((((assembly_struct->num_toks - 1) > cur_tok_chk) && (check_next_token(assembly_struct, cur_tok_chk) == 0) && !(check_next_reg(assembly_struct, cur_tok_chk))) || ((assembly_struct->num_toks - 1) == cur_tok_chk))
        {
            assembly_struct->toks[cur_tok_chk].value = atoi(assembly_struct->toks[cur_tok_chk].text);
            assembly_struct->toks[cur_tok_chk].type = val;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
            assembly_struct->cur_tok_chk++;
        }
        else
        {
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
            assembly_struct->toks[cur_tok_chk].error_code = ERR_TOKEN_WITHOUT_VALUE;
            assembly_struct->cur_tok_chk++;
        }
    }
    else if((assembly_struct->toks[cur_tok_chk].text[0] == ':') && (strlen(assembly_struct->toks[cur_tok_chk].text) > 1))
    {
        if(check_num_int(assembly_struct->toks[cur_tok_chk].text + 1) == 1)
        {   
            assembly_struct->toks[cur_tok_chk].type = flg;
            assembly_struct->toks[cur_tok_chk].value = 0;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK"); 
            assembly_struct->cur_tok_chk++;
        }
        else
        {   
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
            assembly_struct->toks[cur_tok_chk].error_code = ERR_INVALID_FLAG;
            assembly_struct->cur_tok_chk++;
        }
    }
    else if((strcmp(assembly_struct->toks[cur_tok_chk].text, "rax") == 0) || (strcmp(assembly_struct->toks[cur_tok_chk].text, "rbx") == 0) || (strcmp(assembly_struct->toks[cur_tok_chk].text, "rcx") == 0))
    {
        if((((assembly_struct->num_toks - 1) > cur_tok_chk) && (check_next_token(assembly_struct, cur_tok_chk) == 0) && !(check_next_reg(assembly_struct, cur_tok_chk))) || ((assembly_struct->num_toks - 1) == cur_tok_chk))
        {   
            if(strcmp(assembly_struct->toks[cur_tok_chk].text, "rax") == 0)
            {
                assembly_struct->toks[cur_tok_chk].value = 25; 
            }
            else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "rbx") == 0)
            {
                assembly_struct->toks[cur_tok_chk].value = 26;
            }
            else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "rcx") == 0)
            {
                assembly_struct->toks[cur_tok_chk].value = 27;
            }
            assembly_struct->toks[cur_tok_chk].type = reg;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
            assembly_struct->cur_tok_chk++;
        }
        else    
        {
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
            assembly_struct->toks[cur_tok_chk].error_code = ERR_TOKEN_WITHOUT_VALUE;
            assembly_struct->cur_tok_chk++;
        }
    }
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "CALL") == 0)
    {
        if(((assembly_struct->num_toks - 1) > cur_tok_chk) && (check_next_token(assembly_struct, cur_tok_chk) == 0) && (assembly_struct->toks[cur_tok_chk+1].text[(strlen(assembly_struct->toks[cur_tok_chk+1].text) - 1)] == ':'))
        {
            assembly_struct->toks[cur_tok_chk].value = 30;
            assembly_struct->toks[cur_tok_chk].type = cmd;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
            assembly_struct->cur_tok_chk++;
        }
        else
        {
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
            assembly_struct->toks[cur_tok_chk].error_code = ERR_NO_FNC_NAME;
            assembly_struct->cur_tok_chk++;
        }
    }
    else if((assembly_struct->toks[cur_tok_chk].text[(strlen(assembly_struct->toks[cur_tok_chk].text) - 1)] == ':'))
    {
        assembly_struct->toks[cur_tok_chk].type = fnc;
        assembly_struct->toks[cur_tok_chk].value = 0;
        strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
        assembly_struct->cur_tok_chk++;
    }
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "RET") == 0)
    {
        if((((assembly_struct->num_toks - 1) > cur_tok_chk) && !check_next_token(assembly_struct, cur_tok_chk) && !(check_next_reg(assembly_struct, cur_tok_chk))) || ((assembly_struct->num_toks - 1) == cur_tok_chk))
        {
            assembly_struct->toks[cur_tok_chk].value = 10;
            assembly_struct->toks[cur_tok_chk].type = ret;
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");
            assembly_struct->cur_tok_chk++;
        }
        else
        {
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
            assembly_struct->toks[cur_tok_chk].error_code = ERR_TOKEN_WITHOUT_VALUE;
            assembly_struct->cur_tok_chk++;
        }
    }
    else
    {
        strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
        assembly_struct->toks[cur_tok_chk].error_code = ERR_INVALID_TOKEN;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE);
        assembly_struct->cur_tok_chk++;
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
    assembly_struct->cur_tok_chk = 0;
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
    while(assembly_struct->cur_tok_chk < assembly_struct->num_toks)
    {
        get_token_value(assembly_struct, assembly_struct->cur_tok_chk);
    }
}

void write_asm(asm_struct* assembly_struct) 
{   
    put_new_index(assembly_struct); // Gets new indexes of all tokens

    if(check_all_valid(assembly_struct) && check_flags(assembly_struct) && check_func(assembly_struct) && check_fnc_declaration(assembly_struct)) // Rules
    {
        fwrite(assembly_struct->asm_codes, sizeof(char), assembly_struct->num_toks + 1, assembly_struct->translated_file);
        
        printf("Success\n");
    }
    else
    {
        printf("ERROR: asm.txt cannot be translated into binary file. Check LOG_FILE.txt and asm_listing.txt\n");
    }
}

void get_arr_asm_codes(asm_struct* assembly_struct)
{
    assembly_struct->asm_codes = (char*)calloc(assembly_struct->num_toks + 1, sizeof(int));
    assembly_struct->asm_codes[0] = (char)assembly_struct->num_toks;
    
    size_t j = 1;

    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {
        assembly_struct->asm_codes[j] = (char)assembly_struct->toks[i].value;
        j++;
    }

    // printf("\nASM_ARR");
    // for(size_t i = 0; i < assembly_struct->num_toks; i++)
    // {   
    //     printf(" %d ", assembly_struct->asm_codes[i]);
    // }
    // printf("\n");
}

