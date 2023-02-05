/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define FILE_1 "test_asm"   // Defines the name of assembly file
#define FILE_2 "test_code"  // Defines the name of translated file
#define FUNC_LINE __LINE__  // Defines the line from which the error was called 
#define FUNC_NAME __func__  // Defines the name of the fucntion which called the line

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

enum asm_errors // The enum used in order to determine the type of error connected with files 
{
    STRUCT_OK                 = 0,
    ERR_ASM_CODE_BUF_NULL     = 1,
    ERR_OPEN_ASM_FILE         = 2,
    ERR_OPEN_TRANSLATED_FILE  = 3,
    ERR_CLOSE_ASM_FILE        = 4,
    ERR_CLOSE_TRANSLATED_FILE = 5,
    ERR_EMPTY_ASM_FILE        = 6, 
    ERR_NO_HLT                = 7,
    ERR_OPEN_LOG_FILE         = 8,
    ERR_CLOSE_LOG_FILE        = 9
};

enum type // The enum used in order to determine the type of token (command, register or value)
{
    empty = 0, // for initializing
    cmd   = 1,   // 'command'
    reg   = 2,   // 'register'
    val   = 3,   // 'value' 
    flg   = 4,    // 'flag'
    fnc   = 5
};

enum token_error_code // The enum is used in order to determine the error connected with token
{
    TOKEN_OK                 = 0, // Example: 'PUSH 10'
    ERR_INVALID_TOKEN        = 1, // Example: 'asdfadfas'
    ERR_TOKEN_WITHOUT_VALUE  = 2, // Example: 'POP 10'
    ERR_TOKEN_WITH_VALUE     = 3, // Example: 'PUSH ______'
    ERR_NO_FLAG              = 4,
    ERR_INVALID_FLAG         = 5,
    ERR_NO_FLAG_TO_JMP       = 6,
    ERR_INVALID_REG          = 7,
    ERR_CALLS_NON_EXISTEN    = 8,
    ERR_NO_FNC_NAME          = 9
};

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
typedef struct tokens
{
    char* text           = nullptr;   // The pointer to the string containing text of the token
    char value           = 0;         // The value reponsible for asm code of the token
    size_t type          = 0;         // The value responsible for type of token ('cmd','reg', 'val', 'flg')
    const char status[3] = {};        // The value responsible for status (valid/invalid) of token ('OK', '---')
    size_t error_code    = TOKEN_OK;  // The value responsible for error code of the token
    size_t line_number   = 0;         // The value responsible for the number of the command's line 
}tokens;

typedef struct asm_struct
{
    char* asm_buf         = nullptr;   // The pointer to the buffer with commands
    FILE* asm_file        = nullptr;   // The pointer to the file with assembly code 
    FILE* translated_file = nullptr;   // The pointer to the file with translated code 
    tokens* toks          = nullptr;   // The pointer to the array with tokens
    size_t err_code       = STRUCT_OK; // The error code of program
    size_t size           = 0;         // The size of the assembly file
    size_t num_toks       = 1;         // The total number of tokens
    size_t num_lines      = 0;         // The total number of lines in the asm file
};

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void file_openning_check(asm_struct* assembly_struct);                                              // (OK) Opens and checks files with assembly code and translated code
void dtor_asm(asm_struct* assembly_struct);                                                         // (OK) Closes all file, frees all pointers, deletes all data of struct
void get_size_asm(asm_struct* assembly_struct);                                                     // (OK) Gets the size of asm code file 
void get_commands_into_buf(asm_struct* assembly_struct);                                            // (OK) Creates buffer for commands and copies all commands into it
void print_struct(asm_struct* assembly_struct);                                                     // (OK) Prints information about the struct
void get_tokens(asm_struct* assembly_struct);                                                       // (OK) Gets all tokens from the buffer
void realloc_toks(asm_struct* asm_sassembly_structtruct, size_t i);                                 // (OK) Reallocs the array with tokens     
void print_all_toks(asm_struct* assembly_struct);                                                   // (OK) Prints all information about the tokens
void translate_to_asm(asm_struct* assembly_struct);                                                 // (OK) Gets asm codes for all tokens
void get_token_value(asm_struct* assembly_struct, size_t i);                                        // () Puts appropriate asm code to the each token
size_t check_num(char* num_text);                                                                   // (OK) Checks does the number contain only digits and .    
void dump_asm(asm_struct* assembly_struct, const char * FUNCT_NAME, int FUNCT_LINE);                // (OK) Creates LOG_FILE.txt with all information about asm_struct
const char* enum_to_string(size_t code);                                                            // (OK) Сonverts an enum's int value to the enum's string value
void listing(asm_struct* assembly_struct);                                                          // (OK) Makes listing of the assembled code
const char* enum_type_to_string(size_t code);                                                       // (OK) Сonverts an enum's int value of type to the enum's string value of type
size_t check_next_token(asm_struct* assembly_struct, size_t i);                                     // (OK) Checks is the next token is a number
const char* enum_token_err_to_string(size_t code);                                                  // (OK) Сonverts an enum's int value to the enum's string value
void write_asm(asm_struct* assembly_struct);                                                        // (OK) Cheks all token for being valid
size_t check_all_valid(asm_struct* assembly_struct);                                                // (OK) Writes all asm code into the translated file
void count_num_of_lines_in_buf(asm_struct* assembly_struct);                                        // (OK) Counts the number of lines
size_t check_brackets(char* token_text);
size_t check_num_int(char* num_text);                                                               // (OK) Checks does the number contain only digits (in integer)
size_t check_flags(asm_struct* assembly_struct);
size_t check_func(asm_struct* assembly_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/














