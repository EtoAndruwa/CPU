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
 * @brief The main struct which is containing all information about CPU struct
 * 
 */
typedef struct
{
    Stack* stack                = nullptr; /// \brief The pointer to the stack
    stack_type ram[RAM_SIZE]    = {};      /// \brief The array with cells of RAM
    int* bin_code               = {};      /// \brief The pointer to the array with binary codes 
    int* num_bin_cmd            = nullptr;      /// \brief The number of the commands in the array of the binary codes
    size_t curr_cmd             = 0;       /// \brief The index of the current command in the array with binary codes  
    stack_type reg [REG_NUM]    = {};      /// \brief The array registers for values
    stack_type r_reg[R_REG_NUM] = {};      /// \brief The array with registers for adresses
    size_t error_code           = 0;       /// \brief The error code of the struct
    FILE* bin_file              = nullptr;
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

/**
 * @brief The codes of the asm commands
 * 
 */
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
    POP  = 2,
    DEC  = 12,
    JZ   = 13,
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
    ERR_BIN_NULL_BEF_DTOR = 14,
};

// enum return_codes
// {



// };

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Pushes the value from the stack to the register
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 * @param reg_code The code of the register
 */
void pop_reg(CPU* CPU, size_t reg_code);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Pushes the value from the register to the stack
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 * @param reg_code The code of the register
 */
void push_reg(CPU* CPU, size_t reg_code);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Pushes the value from the RAM to the stack using val addressing to the RAM
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 * @param ram_index The index of the RAM cell whose value will be pushed to the stack
 */
void push_ram_val(CPU* CPU, size_t ram_index); 

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Pushes the value from the RAM to the stack using reg addressing to the RAM
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 * @param reg_id The code of the register whose value will be used in order to address to the RAM
 */
void push_ram_reg(CPU* CPU, size_t reg_id); 

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Pushes from the stack to the RAM
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 * @param reg_id The code of the register whose value will be used in order to address to the RAM
 */
void pop_ram_reg(CPU* CPU, size_t reg_id); 

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Pushes from the stack to the RAM
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 * @param ram_index The index of the RAM cell to which will be pushed the value from the stack
 */
void pop_ram_val(CPU* CPU, size_t ram_index); 

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Creates and initializes the CPU struct
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 * @param Stack The pointer to the stack from StackCtor
 * @return size_t  Returns the error code of the function
 */
size_t cpu_ctor(CPU* CPU, Stack* Stack);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Converts the error code to the strings equivalent
 * 
 * @param error_code The error code of the CPU struct
 * @return char* The enum's error code's text equivalent converted to the string 
 */
char* convert_enum_cpu(size_t error_code);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Prints all CPU struct's field's data
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 */
void print_cpu_data(CPU* CPU);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Prints all RAM cells data
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 */
void print_ram(CPU* CPU);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Deletes all data about CPU struct and calls the StackDtor
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 * @return size_t Returns the error code of the function
 */
size_t cpu_dtor(CPU* CPU);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Reads all codes from the binary code file
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 * @return size_t Returns the error code of the function
 */
size_t get_cmd_in_buf(CPU* CPU);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Continues the work of the program until the 'HLT' command is met
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 * @param Call_stack The pointer to the call stack
 */
void cpu_work(CPU* CPU, Call_stack* Call_stack);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Creates/deletes the call stack by initializing all values with poison value 
 * 
 * @param Call_stack The pointer to the call stack
 */
void call_stack_ctor_dtor(Call_stack* Call_stack);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Prints all cells of the call stack
 * 
 * @param Call_stack The pointer to the call stack
 */
void print_call_stack(Call_stack* Call_stack);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Pushes the index of return to the call stack 
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 * @param Call_stack The pointer to the call stack
 * @param index_to_jmp The index of return that will be pushed to the call stack
 */
void push_ret(CPU* CPU, Call_stack* Call_stack, size_t index_to_jmp);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Jumps to the return index from the call stack
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 * @param Call_stack The pointer to the call stack array
 */
void jmp_ret(CPU* CPU, Call_stack* Call_stack);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Sets given array's element's values to the poison value
 * 
 * @param arr_ptr The pointer to the array that must be poisoned
 * @param size_arr The size of the the array that must be poisoned
 */
void fill_with_poison(stack_type* arr_ptr, size_t size_arr);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Jumps to the given index by setting curr_cmd to the given index
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 * @param index_to_jmp The index that must be set as current index
 */
void jmp_flag(CPU* CPU, size_t index_to_jmp);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Prints all RAM cell's data
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 */
void print_ram_screen(CPU* CPU);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Creates dump file and prints all data about RAM, stack, call stack, all regs 
 * 
 * @param CPU The main struct which is containing all information about CPU struct 
 * @param FUNCT_NAME The name of the function which is called the dump
 * @param FUNCT_LINE The line from which the dump was called
 * @param FUNCT_FILE The file from which the dump was called
 * @return size_t Returns the error code of the function
 */
size_t dump_cpu(CPU* CPU, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Exits from the programm with given error code, creates dump file and call cpu_dtor
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 * @param FUNCT_NAME The name of the function which is called the dump  
 * @param FUNCT_LINE The line from which the dump was called
 * @param FUNCT_FILE The file from which the dump was called
 * @param error_code The error code of the struct
 *@return size_t The error code of the function
 */
size_t safe_exit(CPU* CPU, const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE, size_t error_code);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Jumps to the index if register CX equal to the 0
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 * @param index_to_jmp The index that must be set as current index
 */
void jmp_flag_jz(CPU* CPU, size_t index_to_jmp);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Decreases the value of the given register
 * 
 * @param CPU The main struct which is containing all information about CPU struct
 * @param reg_code The code of the register 
 */
void dec(CPU* CPU, size_t reg_code);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif
