#include "assembler.h"

/**
 * @brief                  | (OK) Opens and checks files with assembly code and translated code   
 *  
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void file_openning_check(asm_struct* assembly_struct) 
{   
    FILE* test_asm = fopen("test.asm", "rb"); // Opens the file with text
    FILE* test_code = fopen("test_code.txt", "wb"); // Opens an empty file

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

/**
 * @brief                  | (OK) Puts an appropriate asm code to the each token
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 * @param i                | The positon of the token in the array
 */
void get_token_value(asm_struct* assembly_struct, size_t i) 
{
    if(((assembly_struct->num_toks - 1) == i) && (strcmp(assembly_struct->toks[i].text, "HLT") != 0)) // Checks if the last token 'HLT' is missing
    {
        assembly_struct->err_code = ERR_NO_HLT;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE);
    }
    else if((strcmp(assembly_struct->toks[i].text, "ax") == 0) || (strcmp(assembly_struct->toks[i].text, "bx") == 0) || (strcmp(assembly_struct->toks[i].text, "cx") == 0) || (strcmp(assembly_struct->toks[i].text, "dx") == 0))
    {  
        if((check_next_token(assembly_struct, i) == 0) && ((strcmp(assembly_struct->toks[i+1].text, "ax") != 0) && (strcmp(assembly_struct->toks[i+1].text, "bx") != 0) && (strcmp(assembly_struct->toks[i+1].text, "cx") != 0)))
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
        if(check_next_token(assembly_struct, i) == 1)
        {   
            assembly_struct->toks[i].value = 1 | (1 << 5);
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {   
            if(strcmp(assembly_struct->toks[i+1].text, "ax") == 0 || strcmp(assembly_struct->toks[i+1].text, "bx") == 0 || strcmp(assembly_struct->toks[i+1].text, "cx") == 0 || strcmp(assembly_struct->toks[i+1].text, "dx") == 0)
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
        if((check_next_token(assembly_struct, i) == 0) && ((strcmp(assembly_struct->toks[i+1].text, "ax") != 0) && (strcmp(assembly_struct->toks[i+1].text, "bx") != 0) && (strcmp(assembly_struct->toks[i+1].text, "cx") != 0)))
        {
            assembly_struct->toks[i].value = 2 | (1 << 5);
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {   
            if(strcmp(assembly_struct->toks[i+1].text, "ax") == 0 || strcmp(assembly_struct->toks[i+1].text, "bx") == 0 || strcmp(assembly_struct->toks[i+1].text, "cx") == 0)
            {
                assembly_struct->toks[i].value = 2 | (1 << 6);
                assembly_struct->toks[i].type = cmd;
                strcpy((char*)assembly_struct->toks[i].status, "OK");
            }
            else
            {
                strcpy((char*)assembly_struct->toks[i].status, "--");
                assembly_struct->toks[i].error_code = ERR_TOKEN_WITHOUT_VALUE;
            }
        }
    }
    else if(strcmp(assembly_struct->toks[i].text, "ADD") == 0)
    {   
        if(check_next_token(assembly_struct, i) == 0)
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
        if(check_next_token(assembly_struct, i) == 0)
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
        if(check_next_token(assembly_struct, i) == 0)
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
        if(check_next_token(assembly_struct, i) == 0)
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
        if(check_next_token(assembly_struct, i) == 0)
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
        if((assembly_struct->num_toks - 1) == i) // Checks if it is the last token
        {
            assembly_struct->toks[i].value = 0;
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            if(check_next_token(assembly_struct, i) == 0)
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
    }
    else if(strcmp(assembly_struct->toks[i].text, "OUT") == 0)
    {   
        if((assembly_struct->num_toks - 1) == i)
        {   
            assembly_struct->toks[i].value = 8;
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            if(check_next_token(assembly_struct, i) == 0)
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
    }
    else if(strcmp(assembly_struct->toks[i].text, "JMP") == 0)
    {
        if(check_num_int(assembly_struct->toks[i+1].text + 1) == 1)
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
        if(check_next_token(assembly_struct, i) == 0)
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
    else if(strcmp(assembly_struct->toks[i].text, "JMPR") == 0)
    {
        if(strcmp(assembly_struct->toks[i+1].text, "rax") == 0 || strcmp(assembly_struct->toks[i+1].text, "rbx") == 0 || strcmp(assembly_struct->toks[i+1].text, "rcx") == 0)
            {
                assembly_struct->toks[i].value = 32;
                assembly_struct->toks[i].type = cmd;
                strcpy((char*)assembly_struct->toks[i].status, "OK");
            }
            else
            {
                strcpy((char*)assembly_struct->toks[i].status, "--");
                assembly_struct->toks[i].error_code = ERR_INVALID_REG;
            }
    }
    else if((strcmp(assembly_struct->toks[i].text, "rax") == 0) || (strcmp(assembly_struct->toks[i].text, "rbx") == 0) || (strcmp(assembly_struct->toks[i].text, "rcx") == 0))
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
    else if(strcmp(assembly_struct->toks[i].text, "CALL") == 0)
    {
        if((check_next_token(assembly_struct, i) == 0) && (assembly_struct->toks[i+1].text[(strlen(assembly_struct->toks[i+1].text) - 1)] == ':'))
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
    else if(assembly_struct->toks[i].text[(strlen(assembly_struct->toks[i].text) - 1)] == ':')
    {
        assembly_struct->toks[i].type = fnc;
        strcpy((char*)assembly_struct->toks[i].status, "OK");
    }
    else
    {
        strcpy((char*)assembly_struct->toks[i].status, "--");
        assembly_struct->toks[i].error_code = ERR_INVALID_TOKEN;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE);
    }
}

/**
 * @brief                  | (OK) Creates buffer for commands and copies all commands into it
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void get_commands_into_buf(asm_struct* assembly_struct) 
{
    rewind(assembly_struct->asm_file); // Puts the pointer inside the file to the start of the file 

    assembly_struct->asm_buf = (char*)calloc(1, sizeof(char) * (assembly_struct->size + 1)); // Allocates enough memmory for the buffer of chars  
    size_t num_read = fread(assembly_struct->asm_buf, sizeof(char), assembly_struct->size, assembly_struct->asm_file); // Reads the file into the buffer
    assembly_struct->asm_buf[assembly_struct->size] = '\0'; // Makes form the file null-terminated string

    rewind(assembly_struct->asm_file); // Puts the pointer inside the file to the start of the file
}

/**
 * @brief                  | (OK) Gets the size of asm code file 
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
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

/**
 * @brief                  | (OK) Closes all file, frees all pointers, deletes all data of struct
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void dtor_asm(asm_struct* assembly_struct) 
{
    dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE);

    for(size_t i = 0; i < assembly_struct->num_toks; i ++)
    {
        assembly_struct->toks[i].error_code = 0;
        assembly_struct->toks[i].line_number = 0;
        assembly_struct->toks[i].text = nullptr;
        strcpy((char*)assembly_struct->toks[i].status, "--"); 
        assembly_struct->toks[i].value = 0;
        assembly_struct->toks[i].type = 0;
    }

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

/**
 * @brief                  | (OK) Gets all tokens from the buffer
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void get_tokens(asm_struct* assembly_struct) 
{
    char* token = strtok(assembly_struct->asm_buf," \n\r");
    assembly_struct->toks = (tokens*)calloc(1, sizeof(tokens));
    
    size_t  tok_num = 0;
    while (token != NULL)                        
    {   
        realloc_toks(assembly_struct, tok_num); // Reallocs the struct with tokens
        assembly_struct->toks[tok_num].text = token; // Adds the new token to the array

        token = strtok(NULL, " \n\r");
        tok_num++;
    }

    free(token);
}

/**
 * @brief                  | (OK) Reallocs the array with tokens
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 * @param i                | The position of the token in the array of tokens
 */
void realloc_toks(asm_struct* assembly_struct, size_t i) 
{
    if(assembly_struct->num_toks == i)
    {
        assembly_struct->num_toks++;
        assembly_struct->toks = (tokens*)realloc(assembly_struct->toks, assembly_struct->num_toks * sizeof(tokens)); // The pointer to the array of structs
    }
}

/**
 * @brief                  | (OK) Gets asm codes for all tokens 
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void translate_to_asm(asm_struct* assembly_struct)  
{
    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {
        get_token_value(assembly_struct, i);
    }
}

/**
 * @brief                  | (OK) Writes all asm code into the translated file
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void write_asm(asm_struct* assembly_struct) 
{
    if(check_all_valid(assembly_struct) && check_flags(assembly_struct) && check_func(assembly_struct) && check_fnc_declaration(assembly_struct)) // Rules
    {
        for(size_t i = 0; i < assembly_struct->num_toks; i++)
        {
            char* ptr_end_strtod = nullptr;
            if(assembly_struct->toks[i].value == 33)    
            {
                fprintf(assembly_struct->translated_file, "%d %lf\n", assembly_struct->toks[i].value, strtod(assembly_struct->toks[i+1].text, &ptr_end_strtod));
                i++;
            }
            else if(assembly_struct->toks[i].type == flg)
            {
                fprintf(assembly_struct->translated_file, "%s\n", assembly_struct->toks[i].text);
            }
            else if(assembly_struct->toks[i].type == fnc)
            {
                fprintf(assembly_struct->translated_file, "%s\n", assembly_struct->toks[i].text);
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

// /**
//  * @brief                  | (OK) Counts the number of lines in the buffer
//  * 
//  * @param assembly_struct  | The struct containing all information about the asm struct
//  */
// void count_num_of_lines_in_buf(asm_struct* assembly_struct) 
// {
//     size_t number_of_lines = 0;

//     for(size_t i = 0; i < assembly_struct->size; i++)
//     {       
//         if(assembly_struct->asm_buf[i] == '\n')
//         {  
//             number_of_lines++;
//         }
//         if((assembly_struct->asm_buf[i] != '\n') && (i == (assembly_struct->size - 1))) // If it is the last line without '\n'
//         {
//             assembly_struct->asm_buf[assembly_struct->size] = '\n';
//             assembly_struct->size++;
//             number_of_lines++;
//             break;
//         }
//     }

//     assembly_struct->num_lines = number_of_lines;
// }
