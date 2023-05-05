#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#define DEF_ASM_STRUCT_ERR_CODE
#define DEF_TOKEN_TYPE
#define DEF_TOKEN_ERR_CODE
#define DEF_RET_CODES_ASM
#define DEF_CMD_ID_CODE

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
#include "enums.h"
#include "../graphviz/src/debugger.h"

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Defines used in the code
 */
#define FUNC_LINE __LINE__                  /// \brief Defines the line from which the error was called 
#define FUNC_NAME __func__                  /// \brief Defines the name of the function which called the line
#define FUNC_FILE __FILE__                  /// \brief Defines the name of the file from which dump was called 

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

static const char* FILE_ASM_NAME     = "asm_code.txt";    /// \brief Defines the name of assembly file
static const char* FILE_CODE_NAME    = "bin_code.bin";    /// \brief Defines the name of translated file
static const char* FILE_LOG_NAME     = "log_file.txt";    /// \brief Defines the name of the log file
static const char* FILE_LISTING_NAME = "asm_listing.txt"; /// \brief Defines the name of the listing file

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
    int* bin_codes        = nullptr;   /// \brief Contains ready to be written binary codes of the tokens
    size_t err_code       = STRUCT_OK; /// \brief The error code of program
    size_t size           = 0;         /// \brief The size of the assembly file
    size_t num_toks       = 1;         /// \brief The total number of tokens (1 for initializing, then will be realloced)
    size_t cur_tok_chk    = 0;         /// \brief The index of the current token
    size_t length_listing = 7;         /// \brief The minimum length of the cell in the listing with the names of tokens for pretty log print
};

/*#####################################################################################################################################################################################*/

size_t file_openning_check(asm_struct* assembly_struct);
size_t dtor_asm(asm_struct* assembly_struct);
size_t get_size_asm(asm_struct* assembly_struct);
size_t get_commands_into_buf(asm_struct* assembly_struct); 
void print_struct(asm_struct* assembly_struct);
size_t get_tokens(asm_struct* assembly_struct);
size_t realloc_toks(asm_struct* assembly_struct, size_t i); 
void print_all_toks(asm_struct* assembly_struct); 
void translate_to_asm(asm_struct* assembly_struct);  
void get_token_value(asm_struct* assembly_struct, size_t i);     

/*#####################################################################################################################################################################################*/

size_t check_is_number(char* num_text);     
size_t check_next_token(asm_struct* assembly_struct, size_t i);\
size_t check_all_valid(asm_struct* assembly_struct);     
size_t check_brackets(char* token_text);
size_t check_num_int(char* num_text); 
size_t check_flags(asm_struct* assembly_struct);
size_t check_func(asm_struct* assembly_struct);
size_t check_fnc_declaration(asm_struct* assembly_struct); 
size_t check_next_reg(asm_struct* assembly_struct, size_t i);
size_t check_ram(asm_struct* assembly_struct, char* token_text, size_t index);
size_t check_reg_inner(asm_struct* assembly_struct, char* inner_text);
size_t check_flag_declaration(asm_struct* assembly_struct);
size_t check_is_float(char* num_text) ;

/*#####################################################################################################################################################################################*/


size_t dump_asm(asm_struct* assembly_struct, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE);
const char* enum_struct_err_to_string(size_t code);
size_t listing(asm_struct* assembly_struct);
const char* enum_type_to_string(size_t code);
const char* enum_token_err_to_string(size_t code);
size_t write_asm(asm_struct* assembly_struct);

size_t get_arr_bin_codes(asm_struct* assembly_struct);
void new_index_tok(asm_struct* assembly_struct, size_t index_cmd);
void put_new_index(asm_struct* assembly_struct);
int  get_new_num_toks(asm_struct* assembly_struct); 
void max_len_tok(asm_struct* assembly_struct);
void put_inner_values(asm_struct* assembly_struct, size_t index, char* value_text_ptr, char* register_text_ptr);
const char* get_cmd_string(size_t cmd_code);

/*#####################################################################################################################################################################################*/

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif
