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

void get_token_value(asm_struct* assembly_struct, size_t i) // Puts appropriate asm code to the each token 
{
    if(((assembly_struct->num_toks - 1) == i) && (strcmp(assembly_struct->toks[i].text, "HLT") != 0))
    {
        strcpy((char*)assembly_struct->toks[i].status, "--");
        assembly_struct->err_code = ERR_NO_HLT;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE);
    }
    else if(strcmp(assembly_struct->toks[i].text, "PUSH") == 0)
    {  
        if(check_next_token(assembly_struct, i) == 1)
        {
            assembly_struct->toks[i].value = 1;
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_TOKEN_WITH_VALUE;
        }
    }
    else if(strcmp(assembly_struct->toks[i].text, "POP") == 0)
    {   
        if(check_next_token(assembly_struct, i) == 0)
        {
            assembly_struct->toks[i].value = 2;
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
        else
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_TOKEN_WITHOUT_VALUE;
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
        if((assembly_struct->num_toks - 1) != i)
        {
            strcpy((char*)assembly_struct->toks[i].status, "--");
            assembly_struct->toks[i].error_code = ERR_TOKEN_WITHOUT_VALUE;
        }
        else
        {
            assembly_struct->toks[i].value = 0;
            assembly_struct->toks[i].type = cmd;
            strcpy((char*)assembly_struct->toks[i].status, "OK");
        }
    }
    else if(strcmp(assembly_struct->toks[i].text, "OUT") == 0)
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
    else
    {
        strcpy((char*)assembly_struct->toks[i].status, "--");
        assembly_struct->toks[i].error_code = ERR_INVALID_TOKEN;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE);
    }
}

void get_commands_into_buf(asm_struct* assembly_struct) // (OK) Creates buffer for commands and copies all commands into it
{
    rewind(assembly_struct->asm_file); // Puts the pointer inside the file to the start of the file 

    assembly_struct->asm_buf = (char*)calloc(1, sizeof(char) * (assembly_struct->size + 1)); // Allocates enough memmory for the buffer of chars  
    size_t num_read = fread(assembly_struct->asm_buf, sizeof(char), assembly_struct->size, assembly_struct->asm_file); // Reads the file into the buffer
    printf("in buffer : %ld\n", num_read);
    assembly_struct->asm_buf[assembly_struct->size] = '\0'; // Makes form file null-terminated string

    rewind(assembly_struct->asm_file); // Puts the pointer inside the file to the start of the file
}

void get_size_asm(asm_struct* assembly_struct) // (OK) Gets the size of asm code file 
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

void dtor_asm(asm_struct* assembly_struct) // (OK) Closes all file, frees all pointers, deletes all data of struct
{
    dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE);
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
    
    // size_t token_num = 0;
    size_t line_num = 0;
    while (token != NULL)                        
    {   
        realloc_toks(assembly_struct, line_num);
        assembly_struct->toks[line_num].text = token;
        // size_t length_line = strlen(token);
        // char* line_start = (char*)calloc(1, (length_line + 1) * sizeof(char));
        // strcpy(line_start, token);
        // char* line_tok = strtok(line_start," ");
        // printf("line_tok: %s\n", line_tok);
        // while ((line_tok != NULL) && ((line_tok-line_start) <=length_line))                        
        // {   
        //     realloc_toks(assembly_struct, token_num);
        //     printf("line: %ld token %ld: %s\n", line_num, token_num, line_tok);
        //     assembly_struct->toks[token_num].text = line_tok;
        //     assembly_struct->toks[token_num].error_code = TOKEN_OK;
        //     assembly_struct->toks[token_num].type = empty;
        //     assembly_struct->toks[token_num].value = 0;
        //     assembly_struct->toks[token_num].line_number = line_num;
        //     line_tok = strtok (NULL, " ");
        //     token_num++;
        // }
        printf("token %ld: %s\n", line_num, token);
        token = strtok (NULL, " \n\r");
        line_num++;
    }

    free(token);
}

void print_struct(asm_struct* assembly_struct) // (OK) Prints information about the struct 
{
    printf("\nassembly_struct->asm_buf: %p\n", assembly_struct->asm_buf);
    printf("assembly_struct->asm_file: %p\n", assembly_struct->asm_file);
    printf("assembly_struct->translated_file: %p\n", assembly_struct->translated_file);
    printf("assembly_struct->toks: %p\n", assembly_struct->toks);
    printf("assembly_struct->err_code: %ld\n", assembly_struct->err_code);
    printf("assembly_struct->size: %ld\n", assembly_struct->size);
    printf("assembly_struct->num_toks: %ld\n\n", assembly_struct->num_toks);
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
        printf("\nTOKEN_TEXT: %s\n", assembly_struct->toks[i].text);
        printf("TOKEN_VALUE: %ld\n", assembly_struct->toks[i].value);
        printf("TOKEN_TYPE: %ld\n", assembly_struct->toks[i].type);
        printf("TOKEN_STATUS: %s\n", assembly_struct->toks[i].status);
        printf("TOKEN_ERROR_CODE: %ld (%s)\n", assembly_struct->toks[i].error_code, enum_token_err_to_string(assembly_struct->toks[i].error_code));
        printf("TOKEN_LINE: %ld\n\n", assembly_struct->toks[i].line_number);
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
            return "STRUCT_OK"; 
            break;
    }
}

void listing(asm_struct* assembly_struct) // (OK) Makes listing of the assembled code
{
    FILE* listing_file = fopen("asm_listing.txt", "wb");

    fprintf(listing_file,"|LINE|\t\tCOMMAND\t\t|    TYPE    |ASM|    STATUS    |\n");
    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {   
        fprintf(listing_file,"|%04ld|		%-4s		|    %s     |%03ld|      %s      |", i, assembly_struct->toks[i].text, enum_type_to_string(assembly_struct->toks[i].type), assembly_struct->toks[i].value, assembly_struct->toks[i].status);
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

const char* enum_type_to_string(size_t code) // (OK) Сonverts an enum's int value to the enum's string value
{
    switch(code)
    {
        case cmd:
            return "cmd";
            break;
        case reg:
            return "reg";
            break;
        case val:
            return "val";
            break;
        default:
            return "---";
            break;
    }
}

size_t check_next_token(asm_struct* assembly_struct, size_t i) // (OK) Checks is the next token is a number
{
    if(check_num(assembly_struct->toks[i+1].text))
    {
        return 1; // Returns 1 if the next token is number
    }
}

const char* enum_token_err_to_string(size_t code) // (OK) Сonverts an enum's int value to the enum's string value
{
    size_t check_code = code;
    switch(check_code)
    {
        case TOKEN_OK:
            return "OK";
            break;
        case ERR_TOKEN_WITH_VALUE:
            return "ERR_TOKEN_WITH_VALUE";
            break;
        case ERR_TOKEN_WITHOUT_VALUE:
            return "ERR_TOKEN_WITHOUT_VALUE";
            break;
        case ERR_INVALID_TOKEN:
            return "ERR_INVALID_TOKEN";
            break;
    }
}

size_t check_all_valid(asm_struct* assembly_struct) // (OK) Cheks all token for being valid
{
    size_t flag = 1;

    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {
        if((assembly_struct->err_code != STRUCT_OK) || (assembly_struct->toks[i].error_code != TOKEN_OK))
        {   
            flag = 0;
            break;  
        }
    }

    return flag;
}

void write_asm(asm_struct* assembly_struct) // (OK) Writes all asm code into the translated file
{
    if(check_all_valid(assembly_struct))
    {
        for(size_t i = 0; i < assembly_struct->num_toks; i++)
        {
            char* ptr_end_strtod = nullptr;
            if(assembly_struct->toks[i].value == 1)    
            {
                fprintf(assembly_struct->translated_file, "%ld %lf\n", assembly_struct->toks[i].value, strtod(assembly_struct->toks[i+1].text, &ptr_end_strtod));
            }
            else
            {
                fprintf(assembly_struct->translated_file, "%ld\n", assembly_struct->toks[i].value);
            }
        }
        printf("Success\n");
    }
    else
    {
        printf("ERROR: asm.txt cannot be translated into binary file. Check LOG_FILE.txt and asm_listing.txt\n");
    }
}

void count_num_of_lines_in_buf(asm_struct* assembly_struct) // (OK) Counts the number of lines
{
    size_t number_of_lines = 0;

    for(size_t i = 0; i < assembly_struct->size; i++)
    {       
        if(assembly_struct->asm_buf[i] == '\n')
        {  
            number_of_lines++;
        }
        if((assembly_struct->asm_buf[i] != '\n') && (i == (assembly_struct->size - 1))) // If it is the last line without \n
        {
            assembly_struct->asm_buf[assembly_struct->size] = '\n';
            assembly_struct->size++;
            number_of_lines++;
            break;
        }
    }
    assembly_struct->num_lines = number_of_lines;
    printf("assembly_struct->num_line: %ld\n\n", assembly_struct->num_lines);
}

// size_t strlen_slash_n_my_no_spaces(char* str) // (OK) Returns the length of the string without \r, \n and spaces
// {
//     size_t i = 0;
//     size_t count_chars = 0;
//     while (str[i] != '\n')
//     {
//         if((isspace(str[i]) == 0) && (str[i] != '\r'))
//         {
//             count_chars++;
//         }
//         i++;
//     }
//     return count_chars;
// }

// void create_array_line(asm_struct* assembly_struct) // (OK) Creates the array of strings 
// {
//     assembly_struct->arr_lines = (char**)calloc(1, assembly_struct->num_lines * sizeof(char*));   
// }

// char* get_string(asm_struct* assembly_struct) // (OK) Gets the pointer to the string
// {
//     char* string = nullptr;
//     char* start_of_string = &(assembly_struct->asm_buf[assembly_struct->]); // Stores the old position of start 
//     char* end_of_string = strchr_slash_n_my(assembly_struct); // Stores position of the end of the string
    
//     string = (char*)calloc(1, ((end_of_string - start_of_string) + 1) * sizeof(char)); 
//     // if(string == nullptr)
//     // {
//     //     onegin->error_code = ERR_NULLPTR_STRING;
//     //     onegin_dump(onegin, FUNC_NAME, FUNC_LINE);
//     //     onegin_dtor(onegin);
//     //     exit(ERR_NULLPTR_STRING);
//     // }
//     string = strncpy(string, start_of_string, (end_of_string - start_of_string) + 1); // Copies characters from the buffer to the allocated memory cell
//     return string;
// }

// void fill_the_array (asm_struct* assembly_struct) // (OK) Fills the array with pointers to the string
// {
//     for(size_t i = 0; i < assembly_struct->num_lines; i++)
//     {
//         assembly_struct->arr_lines[i] = get_string(assembly_struct); // Gets the pointer to the next string form the buffer
//     }
// }

// char* strchr_slash_n_my(asm_struct* assembly_struct) // (OK) Searches the end of the next line 
// {    
//     char* position = nullptr;

//     while(assembly_struct->position_in_buffer < assembly_struct->size)     
//     {
//         if(assembly_struct->asm_buf[assembly_struct->position_in_buffer] == '\n')
//         {   
//             position = &(assembly_struct->asm_buf[assembly_struct->position_in_buffer]); // Makes the end of the previous line into start of the new one
//             assembly_struct->position_in_buffer++;
//             return position;
//         }
//         else
//         {
//             assembly_struct->position_in_buffer++;
//         }
//     }                                                                            
// }