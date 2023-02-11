#ifndef CPU_H
#define CPU_H

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../../STACK/src/stack.h"

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 */
typedef struct
{
    stack_type* memmory = nullptr;
    stack_type ax  = 0;
    stack_type bx  = 0;
    stack_type cx  = 0;
    stack_type dx  = 0;
    stack_type rax = 0;
    stack_type rcx = 0;
    stack_type rbx = 0;
}CPU; 

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param CPU 
 */
void print_regs_val(CPU* CPU);
/**
 * @brief 
 * 
 * @param CPU 
 * @param reg_code 
 */
void pop_reg(CPU* CPU, size_t reg_code);
/**
 * @brief 
 * 
 * @param CPU 
 * @param reg_code 
 * @param push_value 
 */
void push_reg(CPU* CPU, size_t reg_code, stack_type push_value);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif // CPU_H

