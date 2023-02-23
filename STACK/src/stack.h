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

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define FUNC_NAME __func__ /// \brief Used in order to get name of the function which called the error
#define FUNC_LINE __LINE__ /// \brief Used in order to get the line from which the error was called
#define FUNC_FILE __FILE__ /// \brief Used in order ot get the file from which the error was called
#define LOG_FILE_NAME "dump_log.txt"
#define ACTION_LOG_NAME "Action_log_stack.txt"

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

typedef int stack_type;

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

const stack_type POISON_VALUE = 0xEDA;  /// \brief The poison value 
const size_t MAX_LINE_COMMAND = 5;      /// \brief The maximum length of the command string
const size_t CANARY           = 0xDEAD; /// \brief The canary value

enum error_list_codes 
{
    STACK_IS_OK             = 0, 
    ERR_NULL_DATA           = 1,
    ERR_OUT_OF_STACK_RIGHT  = 2,
    ERR_OUT_OF_STACK_LEFT   = 3,
    ERR_LEFT_CANARY_DEAD    = 4,
    ERR_RIGHT_CANARY_DEAD   = 5,
    ERR_HASH_CHANGED        = 6,
    ERR_TO_CALLOC_STACK     = 7,
    ERR_TO_REALLOC_DOWN     = 8,
    ERR_TO_REALLOC_UP       = 9,
    ERR_TO_CALLOC_CMD_STR   = 10,
    ERR_OPEN_DUMP_FILE      = 11,
    ERR_CLOSE_DUMP_FILE     = 12,
    ERR_OPEN_ACTION_LOG     = 13,
    ERR_CLOSE_ACTION_LOG    = 14,
};

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param code 
 * @return const char* 
 */
const char* Enum_to_string(size_t code);                              /// \brief (OK) Converts an enum's int value to the enum's string value

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 * @return stack_type 
 */
stack_type StackPop(Stack* st);                                       /// \brief (OK) Deletes the value from the stack

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 * @return stack_type 
 */
stack_type Get_cur_value_of_hash(Stack* st);                          /// \brief (OK) Calculates the current value of the hash 

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 * @param stack_size 
 */
void StackCtor(Stack* st, size_t stack_size);                        /// \brief (OK) Creates and initializes stack

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 * @param push_value 
 */
void StackPush(Stack* st, stack_type push_value);                     /// \brief (OK) Gets the value and pushes in to the stack

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 * @param FUNCT_NAME 
 * @param FUNCT_LINE 
 */
void StackCheck(Stack* st,  const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE); /// \brief (OK) Checks the stack for the possible errors

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 */
void StackDtor(Stack* st);                                            /// \brief (OK) Deletes the stack and spoils all stack's data with the poison value

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 * @param FUNCT_NAME 
 * @param FUNCT_LINE 
 */
void StackDump(Stack* st,  const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE);  /// \brief (OK) Outputs the data to the LOG.txt about the stack

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 */
void StackMul(Stack* st);                                             /// \brief (OK) Multiplies two values of the stack

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 */
void StackSub(Stack* st);                                             /// \brief (OK) Substracts one value of the stack from another one 

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 */
void StackDiv(Stack* st);                                             /// \brief (OK) Divides the preceding element by the last element of the stack

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 */
void StackPrint(Stack* st);                                           /// \brief (OK) (DEBUG ONLY) Prints the stack's current structure in the console

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 * @param command 
 * @param push_value 
 */
void StackLogic(Stack* st, char* command, stack_type push_value);     /// \brief (OK) Calls other functions depending on the entered command 

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 */
void StackAdd(Stack* st);                                             /// \brief (OK) Adds the entered value to next empty memory cell of the stack

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 */
void StackConsoleWork(Stack* st);                                     /// \brief (OK) Supports the work of program until 'HLT' was entered in the console

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 */
void StackRealocUp(Stack* st);                                        /// \brief (OK) Increases the capacity of the stack, reallocs data

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 */
void StackRealocDown(Stack* st);                                      /// \brief (OK) Decreases the capacity of the stack, reallocs data

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 */
void Calculate_hash(Stack* st);                                       /// \brief (OK) Recalculates the value of hash everytime when called

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 */
void StackOut(Stack* st);                                            /// \brief (OK) Prints the stack's current structure in the console

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 * @param st 
 */
void StackSqrt(Stack* st);                                           /// \brief (OK) Gets the root of the value 

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif 
