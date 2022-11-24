#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EPS 1e-7

typedef double stack_type;
typedef struct
{
    stack_type * data = nullptr;
    size_t capacity = 0;
    size_t size = 0;
    size_t error_code = 0;
    size_t left_canary_position = 0;
    size_t right_canary_position = 0; 
}Stack;

const double POISON_VALUE = NAN;

const size_t MAX_LINE_COMMAND = 5;
const size_t MAX_CAPACITY = 0;
const size_t STACK_CAPACITY = 0;
const stack_type CANARY = 0xDEAD;

enum error_list
{
    ERR_NULL_DATA = 1,
    ERR_OUT_OF_STACK_RIGHT = 2,
    ERR_OUT_OF_STACK_LEFT = 3,
    ERR_LEFT_CANARY_DEAD = 4,
    ERR_RIGHT_CANARY_DEAD = 5,
    ERR_DIV_ZERO = 6
    // ERR_RIGHT_BUFFER_CANARY_DEAD = 6,
    // ERR_LEFT_BUFFER_CANARY_DEAD = 7
};

void StackCtor(Stack * st);

void StackPush(Stack * st, stack_type push_value);

void StackDump(Stack * st, const char * FUNCT_NAME, int FUNCT_LINE);

void StackDtor(Stack * st);

void StackCheck(Stack * st, const char * FUNCT_NAME, int FUNCT_LINE);

stack_type StackPop(Stack * st);

void StackMul(Stack * st);

void StackSub(Stack * st);

void StackDiv(Stack * st);

void StackPrint(Stack * st);

void StackLogic(Stack * st, int command_id, stack_type push_value);

void StackAdd(Stack * st);

void StackConsoleWork(Stack * st);

void StackRealocUp(Stack * st);

void StackRealocDown(Stack * st);

void StackConsoleWork(Stack * st, FILE * test_code);

void file_openning_check(Stack * st);


#endif // STACK_H
