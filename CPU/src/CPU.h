#ifndef CPU_H
#define CPU_H

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../../STACK/src/stack.h"

#define RAM_SIZE 200
#define REG_NUM 4
#define CALL_QUEUE_SIZE 5
#define JMP_MAP_SIZE 5
#define R_REG_NUM 3
#define POISON 0xDED32
#define STACK_SIZE 5
#define FILE_NAME "code_file.bin"

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 */
typedef struct
{
    stack_type* memmory = nullptr;  //  pointer to the RAM
    Stack* stack = nullptr;
    char* bin_code = {};
    char num_bin_cmd[1] = {};
    size_t curr_cmd = 0;
    size_t call_queue[CALL_QUEUE_SIZE] = {}; 
    size_t jmp_map[JMP_MAP_SIZE] = {};
    stack_type  reg [REG_NUM] = {};       //  registets for values
    stack_type r_reg[R_REG_NUM] = {};       //  registers for adresses
    size_t error_code = 0;
}CPU; 


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

enum error_code
{
    CPU_OK             = 0,
    ERR_NULLPTR_RAM    = 1,
    ERR_RAM_ADDRESSING = 2,
    ERR_OPEN_CODE_FILE = 3,
};

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void pop_reg(CPU* CPU, size_t reg_code);

void push_reg(CPU* CPU, size_t reg_code);

void push_ram(CPU* CPU, size_t ram_index, size_t ram_value);

stack_type pop_ram(CPU* CPU, size_t ram_index);

void get_ram_mem(CPU* CPU);

void cpu_ctor(CPU* CPU, Stack* Stack);

char* convert_enum_cpu(size_t error_code);

void cpu_data_print(CPU* CPU);

void print_ram(CPU* CPU);

void cpu_dtor(CPU* CPU);

void get_cmd_in_buf(CPU* CPU);
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif // CPU_H

