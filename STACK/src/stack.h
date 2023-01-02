#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef double stack_type;
typedef struct
{   
    void* stack_pointer = nullptr; // The pointer to the calloced memory block
    stack_type* data = nullptr; // The pointer to the stack's data
    size_t* left_canary_position = nullptr; // The pointer to the left canary 
    size_t* right_canary_position = nullptr; // The pointer to the right canary
    size_t capacity = 0; // The number of elements in the stack
    size_t next_empty_cell = 0; // The pointer to the next empty cell of the stack's data
    size_t error_code = 0; // The error code of stack
    stack_type hash = 0; // The value used in oreder to validate actions with the stack
}Stack;

const double POISON_VALUE = NAN; // The poison value 
const size_t MAX_LINE_COMMAND = 5; // The maximum length of the command string
const size_t CANARY = 0xDEAD; // The canary value

enum error_list_codes 
{
    ERR_NULL_DATA = 1,
    ERR_OUT_OF_STACK_RIGHT = 2,
    ERR_OUT_OF_STACK_LEFT = 3,
    ERR_LEFT_CANARY_DEAD = 4,
    ERR_RIGHT_CANARY_DEAD = 5,
    ERR_HASH_CHANGED = 6,
    STACK_IS_OK = 0
};


const char* Enum_to_string(size_t code); // Converts an enum's int value to the enum's string value
void StackCtor(Stack* st); // Creates and initializes stack
void StackPush(Stack* st, stack_type push_value); // Gets the value and pushes in to the stack
void StackCheck(Stack* st,  const char * FUNCT_NAME, int FUNCT_LINE); // Checks the stack for the possible errors
void StackDtor(Stack* st); // Deletes the stack and spoils all stack's data with the poison value
void StackDump(Stack* st,  const char * FUNCT_NAME, int FUNCT_LINE); // Outputs the data to the LOG.txt about the stack
stack_type StackPop(Stack* st); // Deletes the value from the stack
void StackMul(Stack* st); // Multiplies two values of the stack
void StackSub(Stack* st);  // Substracts one value of the stack from another one 
void StackDiv(Stack* st); // Divides the preceding element by the last element of the stack
void StackPrint(Stack* st); // (DEBUG ONLY) Prints the stack's current structure in the console
void StackLogic(Stack* st, char* command, stack_type push_value); // Aalls other functions depending on the entered command 
void StackAdd(Stack* st); // Adds the entered value to next empty memory cell of the stack
void StackConsoleWork(Stack* st); // Supports the work of program until 'HLT' was entered in the console
void StackRealocUp(Stack* st); // Increases the capacity of the stack, reallocs data
void StackRealocDown(Stack* st); // Decreases the capacity of the stack, reallocs data
void Calculate_hash(Stack* st); // Recalculates the value of hash everytime when called
stack_type Get_cur_value_of_hash(Stack* st); // Calculates the current value of the hash 
void StackOut(Stack * st); // Prints the stack's current structure in the console
void StackSqrt(Stack * st); // Gets the root of the value 


#endif // STACK_H
