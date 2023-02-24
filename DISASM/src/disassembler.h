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
static const char* FILE_ASM_NAME = "asm_code.asm";
static const size_t POISON = 0xDED;

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 */
enum error
{
    STRUCT_OK = 0,
    ERR_OPEN_BIN_FILE = 1,
    ERR_CLOSE_BIN_FILE = 2,
    ERR_OPEN_DUMP_FILE = 3,
    ERR_CLOSE_DUMP_FILE = 4,
    ERR_CALLOC_BIN_BUF  = 5,
    ERR_INV_READ_NUM_CMD =6,
    ERR_CANNOT_READ_CMD = 7,   
    ERR_CALLOC_COMMANDS = 8,
    ERR_OPEN_ASM_FILE   = 9,
    ERR_CLOSE_ASM_FILE  = 10,
};

enum type
{
    empty = 0, /// \brief for initializing
    cmd   = 1, /// \brief 'command'
    reg   = 2, /// \brief 'register'
    val   = 3, /// \brief 'value' 
    ram_val = 4,
    ram_reg = 5,
};

typedef struct command
{
    int value          = 0;
    size_t type        = empty;
    size_t flag_before = 0;
    size_t func_before = 0;
}command;

typedef struct disasm_struct
{
    int* bin_codes_buf   = nullptr;
    command* commands    = nullptr;
    int num_bin_cmd[1]   = {};
    size_t error_code    = STRUCT_OK;
    size_t flag_num      = 0;
    size_t func_num      = 0;
    size_t cur_cmd_index = 0;
}disasm_struct;

enum cmd
{
    HLT          = 0,  
    PUSH_ST      = 33, 
    PUSH_REG     = 65, 
    PUSH_RAM_VAL = 161, 
    PUSH_RAM_REG = 193, 
    
    POP_REG     = 66,
    POP_RAM_VAL = 162,
    POP_RAM_REG = 194,

    DEC  = 1,
    JZ   = 2,
    ADD  = 3,  
    SUB  = 4, 
    MUL  = 5, 
    DIV  = 6, 
    SQRT = 7, 
    OUT  = 8, 
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
 * @brief 
 * 
 * @param assembly_struct 
 * @param FUNCT_NAME 
 * @param FUNCT_LINE 
 * @param FUNCT_FILE 
 */
void dump_disasm(disasm_struct* disasm_struct, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE);

void disasm_dtor(disasm_struct* disasm_struct);

void disasm_ctor(disasm_struct* disasm_struct);

void safe_exit(disasm_struct* disasm_struct, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE, size_t error_code);

void get_cmd_in_buf(disasm_struct* disasm_struct);

const char* enum_struct_err_to_string(size_t code); // for struct

void fill_with_poison(int* arr_ptr, size_t size_arr);

void print_commands(disasm_struct* disasm_struct);

void get_command_types(disasm_struct* disasm_struct);

const char* get_cmd_string(size_t cmd_code);

void write_asm(disasm_struct* disasm_struct);

void check_next_cmd(disasm_struct* disasm_struct);

void put_flag_func(disasm_struct* disasm_struct);

void print_flag_func(disasm_struct* disasm_struct, FILE* asm_file);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif