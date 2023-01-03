#include "CPU.h"

int main()
{
    Stack st = {};
    StackCtor(&st);
    StackPrint(&st);
    StackPush(&st, 5);
    StackPrint(&st);
    StackDtor(&st);

    return 0;
}