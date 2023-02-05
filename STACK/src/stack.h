#ifndef STACK_H
#define STACK_H

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define FUNC_NAME __func__ // Used in order to get name of the function which called the error
#define FUNC_LINE __LINE__ // Used in order to get the line from which the error was called

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

typedef double stack_type;

typedef struct
{   
    void* stack_pointer           = nullptr; // The pointer to the calloced memory block
    stack_type* data              = nullptr; // The pointer to the stack's data
    size_t* left_canary_position  = nullptr; // The pointer to the left canary 
    size_t* right_canary_position = nullptr; // The pointer to the right canary
    size_t capacity               = 0;       // The number of elements in the stack
    size_t next_empty_cell        = 0;       // The pointer to the next empty cell of the stack's data
    size_t error_code             = 0;       // The error code of stack
    stack_type hash               = 0;       // The value used in oreder to validate actions with the stack
}Stack;

const double POISON_VALUE     = NAN;    // The poison value 
const size_t MAX_LINE_COMMAND = 5;      // The maximum length of the command string
const size_t CANARY           = 0xDEAD; // The canary value

enum error_list_codes 
{
    STACK_IS_OK            = 0, 
    ERR_NULL_DATA          = 1,
    ERR_OUT_OF_STACK_RIGHT = 2,
    ERR_OUT_OF_STACK_LEFT  = 3,
    ERR_LEFT_CANARY_DEAD   = 4,
    ERR_RIGHT_CANARY_DEAD  = 5,
    ERR_HASH_CHANGED       = 6
};

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

const char* Enum_to_string(size_t code);                              // (OK) Converts an enum's int value to the enum's string value
stack_type StackPop(Stack* st);                                       // (OK) Deletes the value from the stack
stack_type Get_cur_value_of_hash(Stack* st);                          // (OK) Calculates the current value of the hash 
void StackCtor(Stack* st);                                            // (OK) Creates and initializes stack
void StackPush(Stack* st, stack_type push_value);                     // (OK) Gets the value and pushes in to the stack
void StackCheck(Stack* st,  const char * FUNCT_NAME, int FUNCT_LINE); // (OK) Checks the stack for the possible errors
void StackDtor(Stack* st);                                            // (OK) Deletes the stack and spoils all stack's data with the poison value
void StackDump(Stack* st,  const char * FUNCT_NAME, int FUNCT_LINE);  // (OK) Outputs the data to the LOG.txt about the stack
void StackMul(Stack* st);                                             // (OK) Multiplies two values of the stack
void StackSub(Stack* st);                                             // (OK) Substracts one value of the stack from another one 
void StackDiv(Stack* st);                                             // (OK) Divides the preceding element by the last element of the stack
void StackPrint(Stack* st);                                           // (OK) (DEBUG ONLY) Prints the stack's current structure in the console
void StackLogic(Stack* st, char* command, stack_type push_value);     // (OK) Calls other functions depending on the entered command 
void StackAdd(Stack* st);                                             // (OK) Adds the entered value to next empty memory cell of the stack
void StackConsoleWork(Stack* st);                                     // (OK) Supports the work of program until 'HLT' was entered in the console
void StackRealocUp(Stack* st);                                        // (OK) Increases the capacity of the stack, reallocs data
void StackRealocDown(Stack* st);                                      // (OK) Decreases the capacity of the stack, reallocs data
void Calculate_hash(Stack* st);                                       // (OK) Recalculates the value of hash everytime when called
void StackOut(Stack * st);                                            // (OK) Prints the stack's current structure in the console
void StackSqrt(Stack * st);                                           // (OK) Gets the root of the value 

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif // STACK_H
