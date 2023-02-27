#include "CPU.h"

int main()
{
    CPU CPU = {};
    Stack Stack = {};
    Call_stack Call_stack = {};

    cpu_ctor(&CPU, &Stack);
    call_stack_ctor_dtor(&Call_stack);

    get_cmd_in_buf(&CPU);
    cpu_work(&CPU, &Call_stack);
    print_ram_screen(&CPU);

    call_stack_ctor_dtor(&Call_stack);
    cpu_dtor(&CPU);
    return 0;
}
