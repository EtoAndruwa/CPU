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

#define FUNC_NAME __func__                      /// \brief Used in order to get name of the function which called the error
#define FUNC_LINE __LINE__                      /// \brief Used in order to get the line from which the error was called
#define FUNC_FILE __FILE__                      /// \brief Used in order ot get the file from which the error was called
static const char* LOG_FILE_NAME   ="dump_log.txt";          /// \brief Defines the name of the logfile
static const char* ACTION_LOG_NAME ="Action_log_stack.txt";  /// \brief Defines the name of the action log file

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

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

const stack_type POISON_VALUE = 0xEDA;  /// \brief The poison value 
const size_t MAX_LINE_COMMAND = 5;      /// \brief The maximum length of the command string
const size_t CANARY           = 0xDEAD; /// \brief The canary value

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

enum error_list_codes 
{
    STACK_IS_OK            = 0, 
    ERR_NULL_DATA          = 1,
    ERR_OUT_OF_STACK_RIGHT = 2,
    ERR_OUT_OF_STACK_LEFT  = 3,
    ERR_LEFT_CANARY_DEAD   = 4,
    ERR_RIGHT_CANARY_DEAD  = 5,
    ERR_HASH_CHANGED       = 6,
    ERR_TO_CALLOC_STACK    = 7,
    ERR_TO_REALLOC_DOWN    = 8,
    ERR_TO_REALLOC_UP      = 9,
    ERR_TO_CALLOC_CMD_STR  = 10,
    ERR_OPEN_DUMP_FILE     = 11,
    ERR_CLOSE_DUMP_FILE    = 12,
    ERR_OPEN_ACTION_LOG    = 13,
    ERR_CLOSE_ACTION_LOG   = 14,
    ERR_DIV_TO_ZERO        = 15
};

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Converts an enum's int value to the enum's string value
 * 
 * @param code Error code of the stack struct
 * @return const char* The enum's code converted into the string value
 */
const char* Enum_to_string(size_t code);                              

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Deletes the value from the stack
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 * @return stack_type Returns the popped value from the stack
 */
stack_type StackPop(Stack* stack_struct);                                      

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Calculates the current value of the hash 
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 * @return stack_type Returns the current value of the stack's hash
 */
stack_type Get_cur_value_of_hash(Stack* stack_struct);                         

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Creates and initializes stack
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 * @param stack_size The total number of elements in the stack
 */


/**
 * @brief Creates and initializes stack
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 * @param stack_size The total number of elements in the stack
 * @return size_t The error code of the function
 */
size_t StackCtor(Stack* stack_struct, size_t stack_size);                        

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Gets the value and pushes in to the stack
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 * @param push_value The value that must be pushed into the stack
 */
void StackPush(Stack* stack_struct, stack_type push_value);                     

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Checks the stack for the possible errors
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 * @param FUNCT_NAME The function name which called the check
 * @param FUNCT_LINE The line of the file, from which the check was called
 * @param FUNCT_FILE The name of the file, from which the check was called 
 */
void StackCheck(Stack* stack_struct,  const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE); 

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Deletes the stack and spoils all stack's data with the poison value
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 */
void StackDtor(Stack* stack_struct);                                            

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Outputs the data to the LOG.txt about the stack
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 * @param FUNCT_NAME The function name which called the check
 * @param FUNCT_LINE The line of the file, from which the check was called
 * @param FUNCT_FILE The name of the file, from which the check was called 
 */
void StackDump(Stack* stack_struct,  const char* FUNCT_NAME, int FUNCT_LINE, const char* FUNCT_FILE);  

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Multiplies two values of the stack
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 */
void StackMul(Stack* stack_struct);                                             

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Substracts one value of the stack from another one
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 */
void StackSub(Stack* stack_struct);                                             

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Divides the preceding element by the last element of the stack
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 */
void StackDiv(Stack* stack_struct);                                             

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief (DEBUG ONLY) Prints the stack's current structure in the console
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 */
void StackPrint(Stack* stack_struct);                                          

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Calls other functions depending on the entered command
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 * @param command The text of the command
 * @param push_value The value that must be pushed into the stack
 */
void StackLogic(Stack* stack_struct, char* command, stack_type push_value);    

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Adds the entered value to next empty memory cell of the stack
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 */
void StackAdd(Stack* stack_struct);                                             

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Supports the work of program until 'HLT' was entered in the console
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 */
void StackConsoleWork(Stack* stack_struct);                                     

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Increases the capacity of the stack, reallocs data
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 */
void StackRealocUp(Stack* stack_struct);                                        

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Decreases the capacity of the stack, reallocs data
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 */
void StackRealocDown(Stack* stack_struct);                                    

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Recalculates the value of hash everytime when called
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 */
void Calculate_hash(Stack* stack_struct);                                      
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Prints the stack's current structure in the console
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 */
void StackOut(Stack* stack_struct);                                           

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Gets the root of the value 
 * 
 * @param stack_struct The main struct which is containing all data about the stack
 */
void StackSqrt(Stack* stack_struct);                                           

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif 
