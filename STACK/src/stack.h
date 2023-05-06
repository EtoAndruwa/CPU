#ifndef STACK_H
#define STACK_H

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @file stack.h
 * @author EtoAndruwa (https://github.com/EtoAndruwa)
 * @brief 
 * @version 0.1
 * @date 2023-02-18
 * 
 * @copyright Copyright (c) 2023
 */

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../../graphviz/src/debugger.h"

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define FUNC_NAME __func__                                   /// \brief Used in order to get name of the function which called the error
#define FUNC_LINE __LINE__                                   /// \brief Used in order to get the line from which the error was called
#define FUNC_FILE __FILE__                                   /// \brief Used in order ot get the file from which the error was called
static const char* LOG_FILE_NAME   = "dump_log.txt";          /// \brief Defines the name of the logfile
static const char* ACTION_LOG_NAME = "action_log_stack.txt";  /// \brief Defines the name of the action log file

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

typedef float stack_type;

typedef struct
{   
    void* stack_pointer           = nullptr; /// \brief The pointer to the calloced memory block
    stack_type* data              = nullptr; /// \brief The pointer to the stack's data
    size_t* left_canary_position  = nullptr; /// \brief The pointer to the left canary 
    size_t* right_canary_position = nullptr; /// \brief The pointer to the right canary
    size_t capacity               = 0;       /// \brief The number of elements in the stack
    size_t next_empty_cell        = 0;       /// \brief The pointer to the next empty cell of the stack's data
    size_t error_code             = 0;       /// \brief The error code of stack
    stack_type hash               = 0;       /// \brief The value used in oreder to validate actions with the stack
}Stack;

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

const stack_type POISON_VALUE = 0xEDA;  /// \brief The poison value 
const size_t MAX_LINE_COMMAND = 5;      /// \brief The maximum length of the command string
const size_t CANARY           = 0xDEAD; /// \brief The canary value
#define EPS 1e-7


/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

enum error_codes_stack
{
    STACK_IS_OK            = 0, 
    ERR_NULL_DATA          = -1,
    ERR_OUT_OF_STACK_RIGHT = -2,
    ERR_OUT_OF_STACK_LEFT  = -3,
    ERR_LEFT_CANARY_DEAD   = -4,
    ERR_RIGHT_CANARY_DEAD  = -5,
    ERR_HASH_CHANGED       = -6,
    ERR_TO_CALLOC_STACK    = -7,
    ERR_TO_REALLOC_DOWN    = -8,
    ERR_TO_REALLOC_UP      = -9,
    ERR_TO_CALLOC_CMD_STR  = -10,
    ERR_OPEN_DUMP_FILE     = -11,
    ERR_CLOSE_DUMP_FILE    = -12,
    ERR_OPEN_ACTION_LOG    = -13,
    ERR_CLOSE_ACTION_LOG   = -14,
    ERR_DIV_TO_ZERO        = -15,
    ERR_UNKNOWN_STACK_CMD  = -16,
    ERR_SQRT_FROM_NEGATIVE = -17, 
};

enum return_codes_stack
{
    RETURN_OK,
    IS_POSITIVE,
    IS_ZERO,
    IS_NEGATIVE,


};

const char* Enum_to_string(int code);                              
stack_type StackPop(Stack* stack_struct);                                      
stack_type Get_cur_value_of_hash(Stack* stack_struct);                         
int StackCtor(Stack* stack_struct, size_t stack_size);                        
int StackPush(Stack* stack_struct, stack_type push_value);                     
void StackCheck(Stack* stack_struct,  const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE); 
void StackDtor(Stack* stack_struct);                                            
void StackDump(Stack* stack_struct,  const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE);  
int StackMul(Stack* stack_struct);                                             
int StackSub(Stack* stack_struct);                                             
int StackDiv(Stack* stack_struct);                                            
void StackPrint(Stack* stack_struct);                                          
int StackLogic(Stack* stack_struct, char* command, stack_type push_value);    
int StackAdd(Stack* stack_struct);                                             
void StackConsoleWork(Stack* stack_struct);                                     
int StackRealocUp(Stack* stack_struct);                                        
int StackRealocDown(Stack* stack_struct);                                    
void Calculate_hash(Stack* stack_struct);                                      
void StackOut(Stack* stack_struct);                                           
int StackSqrt(Stack* stack_struct);                                           
int check_is_positive(double value);

#endif 
