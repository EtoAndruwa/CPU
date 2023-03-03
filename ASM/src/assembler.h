#ifndef ASSEMBLER_H
#define ASSEMBLER_H

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

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Defines used in the code
 */
#define FUNC_LINE __LINE__                  /// \brief Defines the line from which the error was called 
#define FUNC_NAME __func__                  /// \brief Defines the name of the function which called the line
#define FUNC_FILE __FILE__                  /// \brief Defines the name of the file from which dump was called 

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

static const char* FILE_ASM_NAME     = "asm_code.asm";    /// \brief Defines the name of assembly file
static const char* FILE_CODE_NAME    = "bin_code.bin";    /// \brief Defines the name of translated file
static const char* FILE_LOG_NAME     = "LOG_FILE.txt";    /// \brief Defines the name of the log file
static const char* FILE_LISTING_NAME = "asm_listing.txt"; /// \brief Defines the name of the listing file

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief The enum used in order to determine the type of error connected with files
 */
enum asm_errors 
{
    STRUCT_OK                 = 0,
    ERR_ASM_CODE_BUF_NULL     = 1,
    ERR_OPEN_ASM_FILE         = 2,
    ERR_OPEN_BIN_FILE         = 3,
    ERR_CLOSE_ASM_FILE        = 4,
    ERR_CLOSE_BIN_FILE        = 5,
    ERR_EMPTY_ASM_FILE        = 6, 
    ERR_OPEN_LOG_FILE         = 7,
    ERR_CLOSE_LOG_FILE        = 8,
    ERR_TO_WRITE_CODE         = 9,
    ERR_TO_CALLOC_TOKS        = 10,
    ERR_TO_CALLOC_ASM_BUF     = 11,
    ERR_READ_TO_ASM_BUF       = 12,
    ERR_TO_CALLOC_BIN_CODES   = 13,
    ERR_TO_REALLOC_TOKS       = 14,
    ERR_OPEN_LISTING          = 15,
    ERR_CLOSE_LISTING         = 16
};

/**
 * @brief The enum used in order to determine the type of token (command, register or value)
 */
enum type
{
    empty = 0, /// \brief for initializing
    cmd   = 1, /// \brief 'command'
    reg   = 2, /// \brief 'register'
    val   = 3, /// \brief 'value' 
    flg   = 4, /// \brief 'flag'
    fnc   = 5, /// \brief 'function'
};

/**
 * @brief The enum is used in order to determine the error connected with token
 */
enum token_error_code 
{
    TOKEN_OK                     = 0,  /// \brief Example: 'PUSH 10'
    ERR_INVALID_TOKEN            = 1,  /// \brief Example: 'asdfadfas'
    ERR_TOKEN_WITHOUT_VALUE      = 2,  /// \brief Example: 'POP 10'
    ERR_TOKEN_WITH_VALUE         = 3,  /// \brief Example: 'PUSH ______'
    ERR_NO_FLAG                  = 4,  /// \brief Example: 'JMP _____'
    ERR_INVALID_FLAG             = 5,  /// \brief Example: ':abc'
    ERR_NO_FLAG_TO_JMP           = 6,  
    ERR_INVALID_REG              = 7,   
    ERR_CALLS_NON_EXISTEN_FNC    = 8,  
    ERR_NO_FNC_NAME              = 9,  
    ERR_DOUBLE_DECL_OF_FNC       = 10, 
    ERR_FIRST_DECL_OF_FNC        = 11,
    ERR_TO_CHECK_INNER_RAM       = 12,
    ERR_DOUBLE_DECL_OF_FLAG      = 13,
    ERR_FIRST_DECL_OF_FLAG       = 14,
    ERR_INVAL_RAM_ADDRESSING     = 15,
};  

enum ret_codes
{
    INNER_RAM_INVALID  = 0,
    INNER_REG          = 1,
    INNER_VAL          = 2,
    INNER_VAL_REG      = 3,
    NEXT_TOKEN_CMD     = 4,
    NEXT_TOKEN_VAL     = 5,
    ALL_TOKENS_VALID   = 6,
    SOME_TOKEN_INVALID = 7,
    BRACKETS_OKEY      = 8,
    BRACKETS_NOT_OKEY  = 9,
    ALL_FUNCS_OK       = 10,
    SOME_FUNC_NOT_OK   = 11, 
    TOKEN_IS_INT       = 12,
    TOKEN_IS_NOT_INT   = 13,
    ALL_CALLS_OK       = 14,
    SOME_CALL_NOT_OKEY = 15,
    ALL_FLAGS_OKEY     = 16,
    SOME_FLAG_NOT_OK   = 17,
    NEXT_TOKEN_IS_REG  = 18,
    NEXT_TOKEN_NOT_REG = 19,
    ALL_JMPS_OKEY      = 20,
    SOME_JMP_NOT_OK    = 21,
};

enum cmd
{  
    PUSH_ST      = 33, 
    PUSH_REG     = 65, 
    PUSH_RAM_VAL = 161, 
    PUSH_RAM_REG = 193, 
    
    POP_REG      = 66, 
    POP_ST       = 34,
    POP_RAM_VAL  = 162,
    POP_RAM_REG  = 194,

    HLT  = 0,
    PUSH = 1,
    POP = 2,
    DEC  = 12,
    JZ   = 13,
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
 * @brief The struct of the token
 */
typedef struct tokens
{
    char* text           = nullptr;   /// \brief The pointer to the string containing text of the token
    int value            = 0;         /// \brief The value reponsible for asm code of the token
    size_t type          = 0;         /// \brief The value responsible for type of token ('cmd','reg', 'val', 'flg')
    const char status[3] = {};        /// \brief The value responsible for status (valid/invalid) of token ('OK', '---')
    size_t error_code    = TOKEN_OK;  /// \brief The value responsible for error code of the token
    int new_index        = 0;         /// \brief The new index of the token without flags and function declarations
}tokens;

/**
 * @brief The struct of the whole program
 */
typedef struct asm_struct
{
    char* asm_buf         = nullptr;   /// \brief The pointer to the buffer with commands
    FILE* asm_file        = nullptr;   /// \brief The pointer to the file with assembly code 
    FILE* translated_file = nullptr;   /// \brief The pointer to the file with translated code 
    tokens* toks          = nullptr;   /// \brief The pointer to the array with tokens
    size_t err_code       = STRUCT_OK; /// \brief The error code of program
    size_t size           = 0;         /// \brief The size of the assembly file
    size_t num_toks       = 1;         /// \brief The total number of tokens (1 for initializing, then will be realloced)
    int* bin_codes        = nullptr;   /// \brief Contains ready to be written binary codes of the tokens
    size_t cur_tok_chk    = 0;         /// \brief The index of the current token
    size_t length_listing = 7;         /// \brief The minimum length of the cell in the listing with the names of tokens
};

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Opens and checks files with assembly code and translated code
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @return size_t 
 */
size_t file_openning_check(asm_struct* assembly_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Closes all file, frees all pointers, deletes all data of struct
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @return size_t 
 */
size_t dtor_asm(asm_struct* assembly_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Gets the size of asm code file
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @return size_t 
 */
size_t get_size_asm(asm_struct* assembly_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Creates buffer for commands and copies all commands into it
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @return size_t 
 */
size_t get_commands_into_buf(asm_struct* assembly_struct); 

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Prints information about the struct 
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 */
void print_struct(asm_struct* assembly_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Gets all tokens from the buffer
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @return size_t 
 */
size_t get_tokens(asm_struct* assembly_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Reallocs the array with tokens
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @param i The position of the token in the array of tokens
 * @return size_t 
 */
size_t realloc_toks(asm_struct* assembly_struct, size_t i); 

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Prints all information about all tokens
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 */
void print_all_toks(asm_struct* assembly_struct); 

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Gets asm codes for all tokens 
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 */
void translate_to_asm(asm_struct* assembly_struct);  

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Puts an appropriate asm code to the each token
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @param i The positon of the token in the array
 */
void get_token_value(asm_struct* assembly_struct, size_t i);     

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Checks does the number contain only digits and .
 * 
 * @param num_text The string that must be checked
 * @return size_t Returns '1' if all characters are digit or contain '.'
 */
size_t check_num(char* num_text);     

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Creates LOG_FILE.txt with all information about asm_struct
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @param FUNCT_NAME The string containing the name of the function which called the error
 * @param FUNCT_LINE The number of the line which called the error
 * @return size_t 
 */
size_t dump_asm(asm_struct* assembly_struct, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Сonverts an enum's int value to the enum's string value
 * 
 * @param code The enum code of the command
 * @return const char* Returns the string value of the asm struct's error code  
 */
const char* enum_struct_err_to_string(size_t code);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Makes listing of the assembled code
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @return size_t 
 */
size_t listing(asm_struct* assembly_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Сonverts an enum's int value to the enum's string value
 * 
 * @param code The enum code of the command
 * @return const char* Returns the string value of the token's type code 
 */
const char* enum_type_to_string(size_t code);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Checks is the next token is a number
 * 
 * @param assembly_struct The struct containing all information about the asm struct 
 * @param i The total number of tokens
 * @return size_t Returns '1' if the next token is number
 */
size_t check_next_token(asm_struct* assembly_struct, size_t i);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Сonverts an enum's int value to the enum's string value
 * 
 * @param code The enum code of the command
 * @return const char* Returns the string value of the tokens's error code 
 */
const char* enum_token_err_to_string(size_t code);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Writes all asm code into the translated file
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @return size_t 
 */
size_t write_asm(asm_struct* assembly_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Checks all token for being valid
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @return size_t  Returns '1' if all tokens are valid and code can be converted into assembly code OR returns '0' if some token is invalid or asm struct has an error
 */
size_t check_all_valid(asm_struct* assembly_struct);     

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Checks the valid memmory addressing in the command
 * 
 * @param token_text The token's text that must be checked for closing brackets 
 * @return size_t Returns '1' if brackets are closed
 */
size_t check_brackets(char* token_text);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Checks does the number contain only digits (is an integer)
 * 
 * @param num_text The token's text that must be checked for being an integer
 * @return size_t Returns '1' if all characters are digits (word is an integer)
 */
size_t check_num_int(char* num_text); 

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Checks all flags for existence 
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @return size_t Returns '1' if all flags are ok and '0' if there is some flag missing
 */
size_t check_flags(asm_struct* assembly_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Checks all function calls 
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @return size_t Returns '1' if all CALL commands call declared functions and '0' if call undeclared functions
 */
size_t check_func(asm_struct* assembly_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Checks all function declarations for double declaration
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @return size_t Returns '1' if all declarations of functions are uniqe and '0' if double declarations are exist in the code
 */
size_t check_fnc_declaration(asm_struct* assembly_struct); 

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Checks the next token for being register or not
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @param i The position of the token in the array of tokens
 * @return size_t Returns '1' if the next token has type 'reg' and '0' if another type
 */
size_t check_next_reg(asm_struct* assembly_struct, size_t i);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Creates buffer for number of commands without jmp and func
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @return size_t 
 */
size_t get_arr_bin_codes(asm_struct* assembly_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Checks the RAM addressing inside token's text 
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @param token_text The full text of the token with brackets
 * @param index The index of the token that must be checked
 * @return size_t Returns 1 if 
 */
size_t check_ram(asm_struct* assembly_struct, char* token_text, size_t index);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Checks the token with brackets in order to check for RAM addressing
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @param inner_text Text inside the brackets
 * @return size_t Returns 1 if RAM addressed using value or 2 if RAM addressed using register
 */
size_t check_reg_inner(asm_struct* assembly_struct, char* inner_text);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Calculates the new index of the current command
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @param index_cmd New index of the command
 */
void new_index_tok(asm_struct* assembly_struct, size_t index_cmd);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Puts new indexes for all tokens
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 */
void put_new_index(asm_struct* assembly_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Calculates new number of tokens to be written to the bin file
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @return size_t The number of tokens with right indexes
 */
size_t get_new_num_toks(asm_struct* assembly_struct); 

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Checks all flags declarations for double declaration
 * 
 * @param assembly_struct The struct containing all information about the asm struct
 * @return size_t size_t Returns '1' if all declarations of flags are uniqe and '0' if double declarations are exist in the code
 */
size_t check_flag_declaration(asm_struct* assembly_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param assembly_struct 
 */

void max_len_tok(asm_struct* assembly_struct);
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param assembly_struct 
 * @param index 
 * @param value_text_ptr 
 * @param register_text_ptr 
 */
void put_inner_values(asm_struct* assembly_struct, size_t index, char* value_text_ptr, char* register_text_ptr);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Get the cmd string object
 * 
 * @param cmd_code 
 * @return const char* 
 */
const char* get_cmd_string(size_t cmd_code);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif
