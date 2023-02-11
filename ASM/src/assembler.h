/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @file assembler.h
 * @author EtoAndruwa (https://github.com/EtoAndruwa)
 * @brief 
 * @version 1.0
 * @date 2023-02-06
 * 
 * @copyright Copyright (c) 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief | Defines used in the code
 */
#define FILE_1 "test_asm"   // Defines the name of assembly file
#define FILE_2 "test_code"  // Defines the name of translated file
#define FUNC_LINE __LINE__  // Defines the line from which the error was called 
#define FUNC_NAME __func__  // Defines the name of the fucntion which called the line

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief | The enum used in order to determine the type of error connected with files
 */
enum asm_errors 
{
    STRUCT_OK                 = 0,
    ERR_ASM_CODE_BUF_NULL     = 1,
    ERR_OPEN_ASM_FILE         = 2,
    ERR_OPEN_TRANSLATED_FILE  = 3,
    ERR_CLOSE_ASM_FILE        = 4,
    ERR_CLOSE_TRANSLATED_FILE = 5,
    ERR_EMPTY_ASM_FILE        = 6, 
    ERR_OPEN_LOG_FILE         = 7,
    ERR_CLOSE_LOG_FILE        = 8
};

/**
 * @brief | The enum used in order to determine the type of token (command, register or value)
 */
enum type
{
    empty = 0, // for initializing
    cmd   = 1, // 'command'
    reg   = 2, // 'register'
    val   = 3, // 'value' 
    flg   = 4, // 'flag'
    fnc   = 5, // 'function'
    ret   = 6  // 'return' 
};

/**
 * @brief | The enum is used in order to determine the error connected with token
 */
enum token_error_code 
{
    TOKEN_OK                     = 0,  // Example: 'PUSH 10'
    ERR_INVALID_TOKEN            = 1,  // Example: 'asdfadfas'
    ERR_TOKEN_WITHOUT_VALUE      = 2,  // Example: 'POP 10'
    ERR_TOKEN_WITH_VALUE         = 3,  // Example: 'PUSH ______'
    ERR_NO_FLAG                  = 4,  // Example: 'JMP _____'
    ERR_INVALID_FLAG             = 5,  // Example: ':abc'
    ERR_NO_FLAG_TO_JMP           = 6,  // Example: ''
    ERR_INVALID_REG              = 7,  // Example: '' 
    ERR_CALLS_NON_EXISTEN_FNC    = 8,  // Example: ''
    ERR_NO_FNC_NAME              = 9,  // Example: ''
    ERR_DOUBLE_DECL_OF_FNC       = 10, // Example: ''
    ERR_FIRST_DECL_OF_FNC        = 11  // Example: ''
};  

enum cmd
{
    HLT      = 0,
    PUSH_ST  = 33,
    PUSH_REG = 65,
    PUSH_RAM = 129,
    POP_REG  = 66,
    POP_ST   = 34,
    POP_RAM  = 130, 

    ADD  = 3,
    SUB  = 4,
    MUL  = 5,
    DIV  = 6,
    SQRT = 7,
    OUT  = 8,
    INT  = 9,
    RET  = 10,
    JMP  = 11,
    ax   = 21,
    bx   = 22,
    cx   = 23,
    dx   = 24, 
    rax  = 25, 
    rbx  = 26,
    rcx  = 27,
    CALL = 30
};

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief | The struct of the token
 */
typedef struct tokens
{
    char* text           = nullptr;   // The pointer to the string containing text of the token
    char value           = 0;         // The value reponsible for asm code of the token
    size_t type          = 0;         // The value responsible for type of token ('cmd','reg', 'val', 'flg')
    const char status[3] = {};        // The value responsible for status (valid/invalid) of token ('OK', '---')
    size_t error_code    = TOKEN_OK;  // The value responsible for error code of the token
    size_t line_number   = 0;         // The value responsible for the number of the command's line 
}tokens;

/**
 * @brief | The struct of the whole program
 */
typedef struct asm_struct
{
    char* asm_buf         = nullptr;   // The pointer to the buffer with commands
    FILE* asm_file        = nullptr;   // The pointer to the file with assembly code 
    FILE* translated_file = nullptr;   // The pointer to the file with translated code 
    tokens* toks          = nullptr;   // The pointer to the array with tokens
    size_t err_code       = STRUCT_OK; // The error code of program
    size_t size           = 0;         // The size of the assembly file
    size_t num_toks       = 1;         // The total number of tokens (1 for initializing, then will be realloced)
    int* asm_codes        = nullptr;
};

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief                  | (OK) Opens and checks files with assembly code and translated code   
 *  
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void file_openning_check(asm_struct* assembly_struct);

/**
 * @brief                  | (OK) Closes all file, frees all pointers, deletes all data of struct
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void dtor_asm(asm_struct* assembly_struct); 

/**
 * @brief                  | (OK) Gets the size of asm code file 
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void get_size_asm(asm_struct* assembly_struct);

/**
 * @brief                  | (OK) Creates buffer for commands and copies all commands into it
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void get_commands_into_buf(asm_struct* assembly_struct); 

/**
 * @brief                  | (OK) Prints information about the struct 
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void print_struct(asm_struct* assembly_struct);

/**
 * @brief                  | (OK) Gets all tokens from the buffer
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void get_tokens(asm_struct* assembly_struct);

/**
 * @brief                  | (OK) Reallocs the array with tokens
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 * @param i                | The position of the token in the array of tokens
 */
void realloc_toks(asm_struct* assembly_struct, size_t i);

/**
 * @brief                  | (OK) Prints all information about all tokens
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void print_all_toks(asm_struct* assembly_struct); 

/**
 * @brief                  | (OK) Gets asm codes for all tokens 
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void translate_to_asm(asm_struct* assembly_struct);  

/**
 * @brief                  | (OK) Puts an appropriate asm code to the each token
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 * @param i                | The positon of the token in the array
 */
void get_token_value(asm_struct* assembly_struct, size_t i);     

/**
 * @brief           | (OK) Checks does the number contain only digits and .
 * 
 * @param num_text  | The string that must be checked
 * @return size_t   | Returns '1' if all characters are digit or contain '.'
 */
size_t check_num(char* num_text);     

/**
 * @brief                  | (OK) Creates LOG_FILE.txt with all information about asm_struct
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 * @param FUNCT_NAME       | The string containing the name of the function which called the error
 * @param FUNCT_LINE       | The number of the line which called the error
 */
void dump_asm(asm_struct* assembly_struct, const char * FUNCT_NAME, int FUNCT_LINE);

/**
 * @brief               | (OK) Сonverts an enum's int value to the enum's string value
 * 
 * @param code          | The enum code of the command
 * @return const char*  | Returns the string value of the asm struct's error code  
 */
const char* enum_struct_err_to_string(size_t code);

/**
 * @brief                  | (OK) Makes listing of the assembled code
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void listing(asm_struct* assembly_struct);

/**
 * @brief              | (OK) Сonverts an enum's int value to the enum's string value
 * 
 * @param code         | The enum code of the command
 * @return const char* | Returns the string value of the token's type code 
 */
const char* enum_type_to_string(size_t code);

/**
 * @brief                  | (OK) Checks is the next token is a number
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct 
 * @param i                | The total number of tokens
 * @return size_t          | Returns '1' if the next token is number
 */
size_t check_next_token(asm_struct* assembly_struct, size_t i);

/**
 * @brief               | (OK) Сonverts an enum's int value to the enum's string value
 * 
 * @param code          | The enum code of the command
 * @return const char*  | Returns the string value of the tokens's error code 
 */
const char* enum_token_err_to_string(size_t code);

/**
 * @brief                  | (OK) Writes all asm code into the translated file
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 */
void write_asm(asm_struct* assembly_struct);

/**
 * @brief                  | (OK) Checks all token for being valid
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 * @return size_t          | Returns '1' if all tokens are valid and code can be converted into assembly 
                           | code OR returns '0' if some token is invalid or asm struct has an error
 */
size_t check_all_valid(asm_struct* assembly_struct);     

// /**
//  * @brief                  | (OK) Counts the number of lines in the buffer
//  * 
//  * @param assembly_struct  | The struct containing all information about the asm struct
//  */
//void count_num_of_lines_in_buf(asm_struct* assembly_struct); 

/**
 * @brief             | (FOR_FUTURE) Checks the valid memmory addressing in the command
 * 
 * @param token_text  | The token's text that must be checked for closing brackets 
 * @return size_t     | Returns '1' if brackets are closed
 */
size_t check_brackets(char* token_text);

/**
 * @brief           | (OK) Checks does the number contain only digits (is an integer)
 * 
 * @param num_text  | The token's text that must be checked for being an integer
 * @return size_t   | Returns '1' if all characters are digits (word is an integer)
 */
size_t check_num_int(char* num_text); 

/**
 * @brief                  | (OK) Checks all flags for existence 
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 * @return size_t          | Returns '1' if all flags are ok and '0' if there is some flag missing
 */
size_t check_flags(asm_struct* assembly_struct);

/**
 * @brief                  | (OK) Checks all function calls 
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 * @return size_t          | Returns '1' if all CALL commands call declared functions and '0' if call undeclared functions
 */
size_t check_func(asm_struct* assembly_struct);

/**
 * @brief                  | (OK) Checks all function declarations for double declaration
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 * @return size_t          | Returns '1' if all declarations of functions are uniqe and '0' if double declarations are exist in the code
 */
size_t check_fnc_declaration(asm_struct* assembly_struct); 

/**
 * @brief                  | (OK)
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 * @param i                | The position of the token in the array of tokens
 * @return size_t          | Returns '1' if the next token has type 'reg' and '0' if another type
 */
size_t check_next_reg(asm_struct* assembly_struct, size_t i);

void get_arr_asm_codes(asm_struct* assembly_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/