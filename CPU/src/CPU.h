#ifndef CPU_H
#define CPU_H

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @file CPU.h
 * @author EtoAndruwa (https://github.com/EtoAndruwa)
 * @brief 
 * @version 0.1
 * @date 2023-02-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

// Shifts for commands 

// RAM << 7
// REG << 6
// VAL << 5

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../../STACK/src/stack.h"

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

static const size_t RAM_SIZE        = 400;            /// \brief The size of the RAM
static const size_t SCREEN_SIZE     = 20;             /// \brief The resolution of the screen   
static const size_t REG_NUM         = 4;              /// \brief The number of general purpose registers
static const size_t R_REG_NUM       = 3;              /// \brief The number of additional registers
static const size_t STACK_SIZE      = 10;             /// \brief The capacity of the stack 
static const size_t CALL_STACK_SIZE = 20;             /// \brief The capacity of the call stack 
static const size_t MUL_CONST       = 100;            /// \brief Constant used in order to calculate with precision of 2 digits after the floating point
static const char* BIN_NAME         = "bin_code.bin"; /// \brief The name of the file with binary code 
static const char* DUMP_NAME        = "dump_log.txt"; /// \brief The name of the dump log file 

#define FUNC_NAME __func__            /// \brief Used in order to get name of the function which called the error
#define FUNC_LINE __LINE__            /// \brief Used in order to get the line from which the error was called
#define FUNC_FILE __FILE__            /// \brief Used in order ot get the file from which the error was called

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/    

/**
 * @brief 
 * 
 */
typedef struct
{
    Stack* stack                = nullptr; /// \brief
    stack_type ram[RAM_SIZE]    = {};      /// \brief  pointer to the RAM
    int* bin_code               = {};      /// \brief
    int num_bin_cmd[1]          = {};      /// \brief
    size_t curr_cmd             = 0;       /// \brief     
    stack_type reg [REG_NUM]    = {};      /// \brief  registets for values
    stack_type r_reg[R_REG_NUM] = {};      /// \brief  registers for adresses
    size_t error_code           = 0;       /// \brief
}CPU; 

/**
 * @brief 
 * 
 */
typedef struct 
{   
    stack_type call_stack[CALL_STACK_SIZE] = {}; //
    size_t cur_index                       = 0;  //         
}Call_stack;

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

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

enum error_code
{
    CPU_OK                = 0,
    ERR_NULLPTR_RAM       = 1,
    ERR_RAM_ADDRESSING    = 2,
    ERR_OPEN_BIN_FILE     = 3,
    ERR_CALL_STACK_FULL   = 4,
    ERR_CALL_STACK_EMPT   = 5,
    ERR_OPEN_DMP_FILE     = 6,
    ERR_CLOSE_DMP_FILE    = 7,
    ERR_INVALID_REG       = 8,
    ERR_UNKNOWN_CMD       = 9,
    ERR_INV_READ_NUM_CMD  = 10,
    ERR_CANNOT_READ_CMD   = 11,
    ERR_CALLOC_BIN_CODE   = 12,
    ERR_CLOSE_BIN_FILE    = 13,
    ERR_BIN_NULL_BEF_DTOR = 14
};

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 * @param reg_code 
 */
void pop_reg(CPU* CPU, size_t reg_code);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 * @param reg_code 
 */
void push_reg(CPU* CPU, size_t reg_code);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 * @param ram_index 
 */
void push_ram_val(CPU* CPU, size_t ram_index); // from ram to stack

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 * @param reg_id 
 */
void push_ram_reg(CPU* CPU, size_t reg_id); // from ram to stack

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 * @param reg_id 
 */
void pop_ram_reg(CPU* CPU, size_t reg_id); // from stack to ram

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 * @param ram_index 
 */
void pop_ram_val(CPU* CPU, size_t ram_index); // from stack to ram

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 * @param Stack 
 */
void cpu_ctor(CPU* CPU, Stack* Stack);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param error_code 
 * @return char* 
 */
char* convert_enum_cpu(size_t error_code);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 */
void print_cpu_data(CPU* CPU);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 */
void print_ram(CPU* CPU);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 */
void cpu_dtor(CPU* CPU);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Get the cmd in buf object
 * 
 * @param CPU 
 */
void get_cmd_in_buf(CPU* CPU);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 * @param Call_stack 
 */
void cpu_work(CPU* CPU, Call_stack* Call_stack);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param Call_stack 
 */
void call_stack_ctor_dtor(Call_stack* Call_stack);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param Call_stack 
 */
void print_call_stack(Call_stack* Call_stack);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 * @param Call_stack 
 * @param index_to_jmp 
 */
void push_ret(CPU* CPU, Call_stack* Call_stack, size_t index_to_jmp);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 * @param Call_stack 
 */
void jmp_ret(CPU* CPU, Call_stack* Call_stack);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param arr_ptr 
 * @param size_arr 
 */
void fill_with_posion(stack_type* arr_ptr, size_t size_arr);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 * @param index_to_jmp 
 */
void jmp_flag(CPU* CPU, size_t index_to_jmp);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 */
void print_ram_screen(CPU* CPU);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 * @param FUNCT_NAME 
 * @param FUNCT_LINE 
 * @param FUNCT_FILE 
 */
void dump_cpu(CPU* CPU, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 * @param FUNCT_NAME 
 * @param FUNCT_LINE 
 * @param FUNCT_FILE 
 * @param error_code 
 */
void safe_exit(CPU* CPU, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE, size_t error_code);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif
