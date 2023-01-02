#include "disassembler.h"

void file_openning_check()
{   
    FILE * test_asm = fopen("test.asm", "wb"); // Opens empty file
    FILE * test_code = fopen("test_code.txt", "rb"); // Opens file with code 

    if(test_asm == nullptr)
    {
        printf("ERROR: unable to open file %s.\n", FILE_1);
        abort();
    }
    if(test_code == nullptr)
    {
        printf("ERROR: unable to open file %s.\n", FILE_2);
        abort();
    }
    else
    {   
        printf("OK\n");

        translate_to_code(test_asm, test_code);
    }
}

void translate_logic(FILE * test_asm, int command_id, double push_value)
{
    switch (command_id)
    {
        case 1:
            write_code_push(test_asm, "PUSH", push_value);
            break;
        case 2:
            write_code_other(test_asm, "POP");
            break;
        case 3:
            write_code_other(test_asm, "ADD");
            break;
        case 4:
            write_code_other(test_asm, "SUB");
            break;
        case 5:
            write_code_other(test_asm, "MUL");
            break;
        case 6:
            write_code_other(test_asm, "DIV");
            break;
        default:
            break;
    }
}

void translate_to_code(FILE * test_asm, FILE * test_code)
{
    int command = 0;
    double push_value = 0;

    do
    {
        fscanf(test_code, "%d", &command);
        if(command == 1)
        {
            fscanf(test_code, " %lf", &push_value);
        }
        translate_logic(test_asm, command, push_value);
    }
    while(command != 0)    ;
    fprintf(test_asm, "%s", "HLT");
    fclose(test_asm);
    fclose(test_code);
}

void write_code_push(FILE * test_asm, const char command_string [5], double push_value)
{   
    fprintf(test_asm, "%s %f\n", command_string, push_value);
}

void write_code_other(FILE * test_asm, const char command_string [5])
{   
    fprintf(test_asm, "%s\n", command_string);      
}