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
#include "DSL.h"
#include "../../../graphviz/src/debugger.h"

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

static const size_t RAM_SIZE        = 400;            /// \brief The size of the RAM
static const size_t SCREEN_SIZE     = 20;             /// \brief The resolution of the screen   
static const size_t REG_NUM         = 8;              /// \brief The number of general purpose registers
static const size_t STACK_SIZE      = 10;             /// \brief The capacity of the stack 
static const size_t CALL_STACK_SIZE = 20;             /// \brief The capacity of the call stack 
// static const size_t MUL_CONST       = 100;            /// \brief Constant used in order to calculate with precision of 2 digits after the floating point
static const char* BIN_NAME         = "bin_code.bin"; /// \brief The name of the file with binary code 
static const char* DUMP_NAME        = "dump_log.txt"; /// \brief The name of the dump log file 

#define FUNC_NAME __func__            /// \brief Used in order to get name of the function which called the error
#define FUNC_LINE __LINE__            /// \brief Used in order to get the line from which the error was called
#define FUNC_FILE __FILE__            /// \brief Used in order ot get the file from which the error was called
#define EPS 1e-7

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define DEF_CMD_ID_CODE
#include "../../ASM/src/enums.h"


enum error_code
{
    CPU_OK                  = 0,
    ERR_NULLPTR_RAM         = -1,
    ERR_RAM_ADDRESSING      = -2,
    ERR_OPEN_BIN_FILE       = -3,
    ERR_CALL_STACK_FULL     = -4,
    ERR_CALL_STACK_EMPT     = -5,
    ERR_OPEN_DMP_FILE       = -6,
    ERR_CLOSE_DMP_FILE      = -7,
    ERR_NEW_REG             = -8,
    ERR_UNKNOWN_CMD         = -9,
    ERR_INV_READ_NUM_CMD    = -10,
    ERR_CANNOT_READ_CMD     = -11,
    ERR_CALLOC_BIN_CODE     = -12,
    ERR_CLOSE_BIN_FILE      = -13,
    ERR_BIN_NULL_BEF_DTOR   = -14,
    ERR_POP_VALUE_ERROR     = -15,
};

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/    

/**
 * @brief The main struct which is containing all information about CPU struct
 * 
 */
typedef struct
{
    Stack* stack                = nullptr; /// \brief The pointer to the stack
    FILE* bin_file              = nullptr; /// \breif 
    float num_bin_cmd[1]        = {}; /// \brief The number of the commands in the array of the binary codes
    stack_type ram[RAM_SIZE]    = {};      /// \brief The array with cells of RAM
    float* bin_code             = nullptr ;      /// \brief The pointer to the array with binary codes 
    stack_type reg[REG_NUM]     = {};      /// \brief The array registers for values
    size_t curr_cmd             = 0;       /// \brief The index of the current command in the array with binary codes  
    int error_code              = CPU_OK;       /// \brief The error code of the struct
}CPU; 

/**
 * @brief The struct which is used in order to control returns after call of the functions
 * 
 */
typedef struct 
{   
    stack_type call_stack[CALL_STACK_SIZE] = {}; /// \brief The array of the call stack
    size_t cur_index                       = 0;  /// \brief The current index in the call stack         
}Call_stack;

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int pop_reg(CPU* CPU, float reg_code);
int push_reg(CPU* CPU, float reg_code);
int push_ram_val(CPU* CPU, float ram_index); 
int push_ram_reg(CPU* CPU, float reg_id); 
int pop_ram_reg(CPU* CPU, float reg_id); 
int pop_ram_val(CPU* CPU, float ram_index); 
int cpu_ctor(CPU* CPU, Stack* Stack);
char* convert_enum_cpu(int error_code);
void print_cpu_data(CPU* CPU);
void print_ram(CPU* CPU);
void cpu_dtor(CPU* CPU);
int get_cmd_in_buf(CPU* CPU);
int cpu_work(CPU* CPU, Call_stack* Call_stack);
void call_stack_ctor_dtor(Call_stack* Call_stack);
void print_call_stack(Call_stack* Call_stack);
int push_ret(CPU* CPU, Call_stack* Call_stack, float index_to_jmp);
int jmp_ret(CPU* CPU, Call_stack* Call_stack);
void fill_with_poison(stack_type* arr_ptr, size_t size_arr);
int jmp_flag(CPU* CPU, float index_to_jmp);
void print_ram_screen(CPU* CPU);
int dump_cpu(CPU* CPU, const char* func_name, int func_line, const char* func_file);
int safe_exit(CPU* CPU, const char* func_name, int func_line, const char* func_file, int error_code);
int jmp_flag_jz(CPU* CPU, float index_to_jmp);
int dec(CPU* CPU, float reg_code);
int push_ram_reg_val(CPU* CPU, float push_id, float shift_value);
int pop_ram_reg_val(CPU* CPU, float pop_id, float shift_value);
int cpu_logic(float cmd_code, CPU* CPU, Call_stack* Call_stack);
int inc(CPU* CPU, float reg_code);
int inp(CPU* CPU, float reg_code);
int jmp_flag_je(CPU* CPU, float index_to_jmp);
int jmp_flag_jge(CPU* CPU, float index_to_jmp);
int jmp_flag_jne(CPU* CPU, float index_to_jmp);
int jmp_flag_jg(CPU* CPU, float index_to_jmp);
int prt(CPU* CPU, float reg_code);


#endif
