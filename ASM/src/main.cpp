#include "assembler.h"

/*

#   CMD:        CODE:   BINARY:

1   PUSH        1       00000001
2   POP         2       00000010
3   ADD         3       00000011
4   SUB         4       00000100
5   MUL         5       00000101
6   DIV         6       00000110
7   SQRT        7       00000111
8   OUT         8       00001000
9   HLT         0       00000000
10  INT         9       00001001
11  :FLAG       10      00001010
12  JMP: FLAG   11      00001011 
15  REG         14

*/


int main()
{   
    asm_struct asm_struct = {};

    // printf("Result: %ld\n", check_brackets("[R}"));

    print_struct(&asm_struct);
    file_openning_check(&asm_struct);
    get_size_asm(&asm_struct);
    get_commands_into_buf(&asm_struct);
    count_num_of_lines_in_buf(&asm_struct);
    get_tokens(&asm_struct);
    translate_to_asm(&asm_struct);
    listing(&asm_struct);
    print_all_toks(&asm_struct);
    write_asm(&asm_struct);
    dtor_asm(&asm_struct);
    print_struct(&asm_struct);
    return 0;
}