#include "CPU.h"

int main()
{
    Stack st = {};
    CPU CPU={};
    StackCtor(&st);
    StackPrint(&st);
    StackPush(&st, 5);
    StackPrint(&st);
    StackDtor(&st);
    // push_reg(&CPU, 21, 8);
    // push_reg(&CPU, 22, 9);
    // push_reg(&CPU, 23, 10);
    // push_reg(&CPU, 24, 11);
    // push_reg(&CPU, 25, 12);
    // push_reg(&CPU, 26, 13);
    // push_reg(&CPU, 27, 14);
    print_regs_val(&CPU);

    return 0;
}