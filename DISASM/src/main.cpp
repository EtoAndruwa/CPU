#include "disassembler.h"

int main()
{   
    disasm_struct disasm_struct = {};
    
    get_cmd_in_buf(&disasm_struct);
    disasm_ctor(&disasm_struct);

    get_command_types(&disasm_struct);
    put_flag_func(&disasm_struct);
    //print_commands(&disasm_struct);
    write_asm(&disasm_struct);

    disasm_dtor(&disasm_struct);

    return 0;
}
