#ifndef CPU_H
#define CPU_H

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

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

#define RAM_SIZE 400
#define SCREEN_SIZE 20
#define REG_NUM 4
#define R_REG_NUM 3
#define STACK_SIZE 100
#define CALL_STACK_SIZE 20
#define FILE_NAME "code_file.bin"
#define MUL_CONST 100

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/    

/**
 * @brief 
 * 
 */
typedef struct
{
    Stack* stack = nullptr;
    stack_type ram[RAM_SIZE] = {};  //  pointer to the RAM
    int* bin_code = {};
    int num_bin_cmd[1] = {};
    size_t curr_cmd = 0;
    stack_type  reg [REG_NUM] = {};       //  registets for values
    stack_type r_reg[R_REG_NUM] = {};       //  registers for adresses
    size_t error_code = 0;
}CPU; 

typedef struct 
{   
    stack_type call_stack[CALL_STACK_SIZE] = {};
    size_t cur_index = 0;
}Call_stack;

enum cmd
{
    HLT      = 0,  //ok
    PUSH_ST  = 33, //ok
    PUSH_REG = 65, //ok
    PUSH_RAM_VAL = 161, //ok
    PUSH_RAM_REG = 193, 
    
    POP_REG  = 66,
    POP_RAM_VAL = 162,
    POP_RAM_REG = 194,

    ADD  = 3, //ok 
    SUB  = 4, //ok
    MUL  = 5, //ok
    DIV  = 6, //ok
    SQRT = 7, //ok
    OUT  = 8, //ok
    INT  = 9,
    RET  = 10, //ok
    JMP  = 11, //ok
    ax   = 21, //ok
    bx   = 22, //ok
    cx   = 23, //ok
    dx   = 24, //ok
    rax  = 25, //ok
    rbx  = 26, //ok
    rcx  = 27, //ok
    CALL = 30  //ok
};

enum error_code
{
    CPU_OK              = 0,
    ERR_NULLPTR_RAM     = 1,
    ERR_RAM_ADDRESSING  = 2,
    ERR_OPEN_CODE_FILE  = 3,
    ERR_CALL_STACK_FULL = 4,
    ERR_CALL_STACK_EMPT = 5,
};

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void pop_reg(CPU* CPU, size_t reg_code);

void push_reg(CPU* CPU, size_t reg_code);

void push_ram_val(CPU* CPU, size_t ram_index); // from ram to stack

void push_ram_reg(CPU* CPU, size_t reg_id); // from ram to stack

void pop_ram_reg(CPU* CPU, size_t reg_id); // from stack to ram

void pop_ram_val(CPU* CPU, size_t ram_index); // from stack to ram

void cpu_ctor(CPU* CPU, Stack* Stack);

char* convert_enum_cpu(size_t error_code);

void print_cpu_data(CPU* CPU);

void print_ram(CPU* CPU);

void cpu_dtor(CPU* CPU);

void get_cmd_in_buf(CPU* CPU);

void cpu_work(CPU* CPU, Call_stack* Call_stack);

void call_stack_ctor_dtor(Call_stack* Call_stack);

void print_call_stack(Call_stack* Call_stack);

void push_ret(CPU* CPU, Call_stack* Call_stack, size_t index_to_jmp);

void jmp_ret(CPU* CPU, Call_stack* Call_stack);

void fill_with_posion(stack_type* arr_ptr, size_t size_arr);

void jmp_flag(CPU* CPU, size_t index_to_jmp);

void print_ram_screen(CPU* CPU);



/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif // CPU_H

