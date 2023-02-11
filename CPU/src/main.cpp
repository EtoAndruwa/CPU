#include "CPU.h"

int main()
{
    CPU CPU = {};
    Stack Stack = {};
    cpu_ctor(&CPU, &Stack);

    push_reg(&CPU, 21, 8);
    cpu_data_print(&CPU);
    printf("\nPopped value from reg: %f\n", pop_reg(&CPU, 21));
    cpu_data_print(&CPU);
    push_ram(&CPU, 10, 3);
    print_ram(&CPU);
    cpu_dtor(&CPU);
    cpu_data_print(&CPU);
    // push_reg(&CPU, 22, 9);
    // push_reg(&CPU, 23, 10);
    // push_reg(&CPU, 24, 11);
    // push_reg(&CPU, 25, 12);
    // push_reg(&CPU, 26, 13);
    // push_reg(&CPU, 27, 14);

    return 0;
}