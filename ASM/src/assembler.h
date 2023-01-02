#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_1 "test_asm"
#define FILE_2 "test_code"
 
void file_openning_check();

void translate_logic(FILE * test_asm, FILE * test_code, char * command, double push_value);

void write_code_push(FILE * test_asm, FILE * test_code, int command_id, double push_value);

void translate_to_assembly(FILE * test_asm, FILE * test_code);

void write_code_other(FILE * test_asm, FILE * test_code, int command_id);
