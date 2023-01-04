#include "assembler.h"

int main()
{   
    asm_struct asm_struct = {};
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