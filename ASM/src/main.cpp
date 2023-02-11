#include "assembler.h"

/*
#   CMD:        CODE:   BINARY:

1   PUSH        1       00000001
2   POP         2       00000010
4   ADD         3       00000011
3   SUB         4       00000100
5   MUL         5       00000101
6   DIV         6       00000110
7   SQRT        7       00000111
8   OUT         8       00001000
9   INT         9       00001001
10  HLT         0       00000000

11  :FLAG       -       --------
12  JMP: FLAG   11      00001011

15  ax          21      00010101
16  bx          22      00010110
17  cx          23      00010111
18  dx          24      00011000

19  rax         25      00011001
20  rbx         26      00011010
21  rcx         27      00011011

22  CALL        30      00011110
23  FUNCT:      31      00011111
24  JMPR        32      00100000
25  RET         33      10
*/

int main()
{   
    asm_struct asm_struct = {};
    //print_struct(&asm_struct);
    file_openning_check(&asm_struct);
    get_size_asm(&asm_struct);
    get_commands_into_buf(&asm_struct);
    //count_num_of_lines_in_buf(&asm_struct);
    get_tokens(&asm_struct);
    translate_to_asm(&asm_struct);
    //print_all_toks(&asm_struct);
    write_asm(&asm_struct);
    listing(&asm_struct);
    dtor_asm(&asm_struct);
    //print_struct(&asm_struct);
    return 0;
}