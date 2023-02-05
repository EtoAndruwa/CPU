#include "assembler.h"

size_t check_num(char* num_text) // (OK) Checks does the number contain only digits and .
{
    size_t flag = 1;    
    size_t length_text = strlen(num_text);

    for(size_t i  = 0; i < length_text; i++)
    {
        char check_char = num_text[i];

        if((isdigit(check_char) == 0) && (check_char != '.'))
        {
            flag = 0;
        }
    }

    return flag; // Returns 1 if all characters are digit or contain '.'
}

size_t check_next_token(asm_struct* assembly_struct, size_t i) // (OK) Checks is the next token is a number
{
    if(check_num(assembly_struct->toks[i+1].text))
    {
        return 1; // Returns 1 if the next token is number
    }
}

size_t check_all_valid(asm_struct* assembly_struct) // (OK) Cheks all token for being valid
{
    size_t flag = 1; // Returns 1 if all valid and code can be converted into assembly code

    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {
        if((assembly_struct->err_code != STRUCT_OK) || (assembly_struct->toks[i].error_code != TOKEN_OK))
        {   
            flag = 0;
            break;  
        }
    }

    return flag;
}

size_t check_brackets(char* token_text) // (OK) Checks the valid memmory addressing in command
{
    size_t closed = 0;  

    if(strchr(token_text, '[') && strchr(token_text, ']'))
    {
        closed = 1;
    }

    return closed;  // Returns 1 if brackets are closed
}

size_t check_num_int(char* num_text) // (OK) Checks does the number contain only digits (in integer)
{
    size_t flag = 1;    
    size_t length_text = strlen(num_text);

    for(size_t i  = 0; i < length_text; i++)
    {
        char check_char = num_text[i];

        if(isdigit(check_char) == 0)
        {
            flag = 0;
        }
    }

    return flag; // Returns 1 if all characters are digits (word is integer)
}

size_t check_flags(asm_struct* assembly_struct) // (OK) Checks all flags
{
    size_t flags_ok = 1;    

    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {   
        if(strcmp(assembly_struct->toks[i].text, "JMP") == 0)
        {
            char* flag_name = assembly_struct->toks[i+1].text;
            //printf("\nflag_name: %s\n", flag_name);
            //printf("JMP_flag_num: %d\n\n", i);
            for(size_t j = 0; j < assembly_struct->num_toks ; j++)
            {   
                if(assembly_struct->toks[j].type == flg)
                {   
                    //printf("tok_j_num: %d\n", j);
                    if(((strcmp(assembly_struct->toks[j].text, flag_name) == 0) && (j != 0) && (strcmp(assembly_struct->toks[j-1].text, "JMP") != 0)) || ((strcmp(assembly_struct->toks[j].text, flag_name) == 0) && (j == 0)))
                    {   
                        flags_ok = 1;
                        //printf("Result of search: %d\n\n", flags_ok);
                        break;
                    }
                    else 
                    {
                        flags_ok = 0;
                        //printf("Result of search: %d\n", flags_ok);    
                    }
                }
            }
            if(flags_ok == 0)
            {   
                assembly_struct->toks[i].error_code = ERR_NO_FLAG_TO_JMP;
                strcpy((char*)assembly_struct->toks[i].status, "--");
                //printf("assembly_struct->toks[i].error_code: %d\n", assembly_struct->toks[i].error_code);
            }
        }
    }

    //printf("flag_ok: %d\n", flags_ok);
    return flags_ok; // Returns 1 if all flags are ok
}