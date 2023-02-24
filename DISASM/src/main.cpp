#include "disassembler.h"

int main()
{   
    disasm_struct disasm_struct = {};
    
    get_cmd_in_buf(&disasm_struct);
    disasm_ctor(&disasm_struct);

    print_commands(&disasm_struct);

    disasm_dtor(&disasm_struct);

    return 0;
}