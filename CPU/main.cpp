#include "CPU.h"

int main()
{    
    Stack stack = {};
    
    StackCtor(&stack);
    // StackPrint(&stack);
    file_openning_check(&stack);
    StackDtor(&stack);
     
    return 0;
}