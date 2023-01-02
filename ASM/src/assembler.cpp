#include "assembler.h"

void file_openning_check()
{   
    FILE * test_asm = fopen("test.asm", "rb");//opens file with text
    FILE * test_code = fopen("test_code.txt", "wb");//opens empty file

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

        translate_to_assembly(test_asm, test_code);
    }
}

void translate_logic(FILE * test_asm, FILE * test_code, char * command, double push_value)
{
    if(strcmp(command, "PUSH") == 0)
    {  
        write_code_push(test_asm, test_code, 1, push_value);
    }
    else if(strcmp(command, "POP") == 0)
    {   
        write_code_other(test_asm, test_code, 2);
    }
    else if(strcmp(command, "ADD") == 0)
    {   
        write_code_other(test_asm, test_code, 3);
    }
    else if(strcmp(command, "SUB") == 0)
    {   
        write_code_other(test_asm, test_code, 4);  
    }
    else if(strcmp(command, "MUL") == 0)
    {   
        write_code_other(test_asm, test_code, 5);   
    }
    else if(strcmp(command, "DIV") == 0)
    {   
        write_code_other(test_asm, test_code, 6);  
    }
}

void translate_to_assembly(FILE * test_asm, FILE * test_code)
{
    char * command = (char *)calloc(5, sizeof(size_t));
    double push_value = 0;
        
    do
    {
        fscanf(test_asm, "%s", command);
        if(strcmp(command, "PUSH") == 0)
        {
            fscanf(test_asm, " %lf", &push_value);
        }
        translate_logic(test_asm, test_code, command, push_value);
    }

    while(strcmp(command, "HLT") != 0)    ;
    fprintf(test_code, "%d", 0);

    free(command);
    command = nullptr;

    fclose(test_asm);
    fclose(test_code);

    test_asm = nullptr;
    test_code = nullptr;
}

void write_code_push(FILE * test_asm, FILE * test_code, int command_id, double push_value)
{   
    fprintf(test_code, "%d %f\n", command_id, push_value);
}

void write_code_other(FILE * test_asm, FILE * test_code, int command_id)
{   
    fprintf(test_code, "%d\n", command_id);
}