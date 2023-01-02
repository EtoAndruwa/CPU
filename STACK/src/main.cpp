#include  "stack.h"

int main()
{   
    Stack stack = {};

    StackCtor(&stack);
    StackOut(&stack);
    StackConsoleWork(&stack);
    StackDtor(&stack);
     
    return 0;
}









