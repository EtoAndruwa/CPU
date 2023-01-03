#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define FILE_1 "test_asm"   // Defines the name of assembly file
#define FILE_2 "test_code"  // Defines the name of translated file
#define FUNC_LINE __LINE__  // Defines the line from which the error was called 
#define FUNC_NAME __func__  // Defines the name of the fucntion which called the line

typedef struct tokens
{
    char* text = nullptr;
    int value  = 0;
    int type   = 0;
    char status[2];
}tokens;

typedef struct asm_struct
{
    char* asm_buf         = nullptr; // The pointer to the buffer with commands
    FILE* asm_file        = nullptr; // The pointer to the file with assembly code 
    FILE* translated_file = nullptr; // The pointer to the file with translated code 
    tokens* toks          = nullptr; // The pointer to the array with tokens
    size_t err_code       = 0;       // The error code of program
    size_t size           = 0;       // The size of the assembly file
    size_t num_toks       = 1;       // The total number of tokens
}asm_struct;

enum asm_errors
{
    OK                        = 0,
    ERR_ASM_CODE_BUF_NULL     = 1,
    ERR_OPEN_ASM_FILE         = 2,
    ERR_OPEN_TRANSLATED_FILE  = 3,
    ERR_CLOSE_ASM_FILE        = 4,
    ERR_CLOSE_TRANSLATED_FILE = 5,
    ERR_EMPTY_ASM_FILE        = 6, 
    ERR_LEXICAL_ERROR         = 7,
    ERR_NO_HLT                = 8,
    ERR_OPEN_LOG_FILE         = 9,
    ERR_CLOSE_LOG_FILE        = 10
};

enum type
{
    cmd = 1,
    reg = 2,
    val = 3
};

void file_openning_check(asm_struct* assembly_struct);                                              // (OK) Opens and checks files with assembly code and translated code
// void translate_logic(FILE * test_asm, FILE * test_code, char * command, double push_value);      //
// void write_code_push(FILE * test_asm, FILE * test_code, int command_id, double push_value);      //
// void translate_to_assembly(FILE * test_asm, FILE * test_code);                                   //
// void write_code_other(FILE * test_asm, FILE * test_code, int command_id);                        //
void dtor_asm(asm_struct* assembly_struct);                                                         // (OK) Closes all file, frees all pointers, deletes all data of struct
void get_size_asm(asm_struct* assembly_struct);                                                     // (OK) Gets the size of asm code file 
void get_commands_into_buf(asm_struct* assembly_struct);                                            // (OK) Creates buffer for commands and copies all commands into it
void print_struct(asm_struct* assembly_struct);                                                     // (OK) Prints information about the struct
void get_tokens(asm_struct* assembly_struct);                                                       // (OK) Gets all tokens from the buffer
void realloc_toks(asm_struct* asm_sassembly_structtruct, size_t i);                                 // (OK) Reallocs the array with tokens     
void print_all_toks(asm_struct* assembly_struct);                                                   // (OK) Prints all information about the tokens
void translate_to_asm(asm_struct* assembly_struct);                                                 // (OK) Gets asm codes for all tokens
void get_token_value(asm_struct* assembly_struct, size_t i);                                        // (OK) Puts appropriate asm code to the each token
size_t check_num(char* num_text);                                                                   // (OK) Checks does the number contain only digits and .    
void dump_asm(asm_struct* assembly_struct, const char * FUNCT_NAME, int FUNCT_LINE);                // (OK) Creates LOG_FILE.txt with all information about asm_struct
const char* enum_to_string(size_t code);                                                            // (OK) Сonverts an enum's int value to the enum's string value


