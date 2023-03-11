#ifndef DISASM_H
#define DISASM_H

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define FUNC_LINE __LINE__                  /// \brief Defines the line from which the error was called 
#define FUNC_NAME __func__                  /// \brief Defines the name of the function which called the line
#define FUNC_FILE __FILE__                  /// \brief Defines the name of the file from which dump was called 

static const char* FILE_DUMP_NAME = "dump_log.txt";
static const char* FILE_ASM_NAME  = "asm_code.asm";
static const size_t POISON        = 0xDED;

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 */
enum error
{
    STRUCT_OK            = 0,
    ERR_OPEN_BIN_FILE    = 1,
    ERR_CLOSE_BIN_FILE   = 2,
    ERR_OPEN_DUMP_FILE   = 3,
    ERR_CLOSE_DUMP_FILE  = 4,
    ERR_CALLOC_BIN_BUF   = 5,
    ERR_INV_READ_NUM_CMD = 6,
    ERR_CANNOT_READ_CMD  = 7,   
    ERR_CALLOC_COMMANDS  = 8,
    ERR_OPEN_ASM_FILE    = 9,
    ERR_CLOSE_ASM_FILE   = 10,
};

/**
 * @brief 
 * 
 */
enum type
{
    EMPTY       = 0, /// \brief for initializing
    CMD         = 1, /// \brief 'command'
    REG         = 2, /// \brief 'register'
    VAL         = 3, /// \brief 'value' 
    RAM_VAL     = 4,
    RAM_REG     = 5,
    RAM_VAL_REG = 6
};

/**
 * @brief 
 * 
 */
typedef struct command
{
    int value          = 0;
    size_t type        = EMPTY;
    size_t flag_before = 0;
    size_t func_before = 0;
}command;

/**
 * @brief 
 * 
 */
typedef struct disasm_struct
{
    int* bin_codes_buf   = nullptr;
    command* commands    = nullptr;
    FILE* bin_file_ptr   = nullptr;
    int num_bin_cmd[1]   = {};
    size_t error_code    = STRUCT_OK;
    size_t cur_cmd_index = 0;
}disasm_struct;

#define DEF_CMD_ID_CODE
#include "../../ASM/src/enums.h"

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

size_t check_code_file(disasm_struct* disasm_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param disasm_struct 
 */
void disasm_dtor(disasm_struct* disasm_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param disasm_struct 
 * @return size_t 
 */
size_t  disasm_ctor(disasm_struct* disasm_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param disasm_struct 
 * @param FUNCT_NAME 
 * @param FUNCT_LINE 
 * @param FUNCT_FILE 
 * @param error_code 
 * @return size_t 
 */
size_t safe_exit(disasm_struct* disasm_struct, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE, size_t error_code);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Get the cmd in buf object
 * 
 * @param disasm_struct 
 * @return size_t 
 */
size_t get_cmd_in_buf(disasm_struct* disasm_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param code 
 * @return const char* 
 */
const char* enum_struct_err_to_string(size_t code); // for struct

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param arr_ptr 
 * @param size_arr 
 */
void fill_with_poison(int* arr_ptr, size_t size_arr);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param disasm_struct 
 */
void print_commands(disasm_struct* disasm_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Get the command types object
 * 
 * @param disasm_struct 
 */
void get_command_types(disasm_struct* disasm_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Get the cmd string object
 * 
 * @param cmd_code 
 * @return const char* 
 */
const char* get_cmd_string(size_t cmd_code);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param disasm_struct 
 * @return size_t 
 */
size_t write_asm(disasm_struct* disasm_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param disasm_struct 
 */
void check_next_cmd(disasm_struct* disasm_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param disasm_struct 
 */
void put_flag_func(disasm_struct* disasm_struct);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param disasm_struct 
 * @param asm_file 
 */
void print_flag_func(disasm_struct* disasm_struct, FILE* asm_file);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

char* get_reg_inner_ram(int command_code);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

size_t dump_disasm(disasm_struct* disasm_struct, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif
