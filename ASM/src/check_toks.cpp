#include "assembler.h"

size_t check_num(char* num_text) 
{
    size_t flag = 1; // Returns 1 if all characters are digit or contain '.'

    size_t length_text = strlen(num_text);
    for(size_t i  = 0; i < length_text; i++)
    {
        char check_char = num_text[i];

        if(isdigit(check_char) == 0) // Check does the text contain digits
        {
            flag = 0;
        }
    }

    return flag; // Returns 1 if all characters are digit or contain '.'
}

size_t check_next_token(asm_struct* assembly_struct, size_t i) 
{
    if(((assembly_struct->num_toks - 1) > i) && (check_num(assembly_struct->toks[i+1].text)))
    {
        return 1; // Returns 1 if the next token is number
    }
    else
    {
        return 0;
    }
}

size_t check_all_valid(asm_struct* assembly_struct) 
{
    size_t flag = 1; // Returns 1 if all valid and code can be converted into assembly code

    //printf("assembly_struct->num_toks: %ld\n", assembly_struct->num_toks);
    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {
        if((assembly_struct->err_code != STRUCT_OK) || (assembly_struct->toks[i].error_code != TOKEN_OK))
        {   
            flag = 0; // Returns 0 if some token is invalid or asm struct has an error 
            break;  
        }
    }

    return flag; // Returns 1 if all valid and code can be converted into assembly code
}

size_t check_brackets(char* token_text) 
{
    size_t closed = 0;  

    if((token_text[0] == '[') && (token_text[strlen(token_text) - 1] == ']'))
    {
        closed = 1;
    }

    return closed;  // Returns 1 if brackets are closed
}

size_t check_ram(asm_struct* assembly_struct, char* token_text, size_t index)
{
    if(check_brackets(token_text))
    {
        size_t strlen_token_check = strlen(token_text);
        if(strlen_token_check >= 3)
        {
            size_t length_of_inner = strlen_token_check -1 ;
            char* str_check =(char*)calloc(length_of_inner, sizeof(char));
            strncpy(str_check, (token_text + 1), strlen_token_check - 2);
            str_check[strlen_token_check - 1] = '\0';

            if(check_reg_inner(assembly_struct, str_check))
            {
                if(strcmp(str_check, "ax") == 0)
                {
                    assembly_struct->toks[index].value = 21; 
                }
                else if(strcmp(str_check, "bx") == 0)
                {
                    assembly_struct->toks[index].value = 22;
                }
                else if(strcmp(str_check, "cx") == 0)
                {
                    assembly_struct->toks[index].value = 23;
                }
                else if(strcmp(str_check, "dx") == 0)
                {   
                    assembly_struct->toks[index].value = 24;
                }
                if(strcmp(str_check, "rax") == 0)
                {
                    assembly_struct->toks[index].value = 25; 
                }
                else if(strcmp(str_check, "rbx") == 0)
                {
                    assembly_struct->toks[index].value = 26;
                }
                else if(strcmp(str_check, "rcx") == 0)
                {
                    assembly_struct->toks[index].value = 27;
                }
                assembly_struct->toks[index].type = reg;
                strcpy((char*)assembly_struct->toks[index].status, "OK");

                free(str_check);
                str_check = nullptr;
                return 2; // If ram addressing [reg]
            }
            else if(check_num(str_check))
            {   
                assembly_struct->toks[index].value = atoi(str_check);
                assembly_struct->toks[index].type = val;
                strcpy((char*)assembly_struct->toks[index].status, "OK");

                free(str_check);
                str_check = nullptr;
                return 1; // if memmory addressing [val] 
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

size_t check_num_int(char* num_text) 
{
    size_t flag = 1; 

    size_t length_text = strlen(num_text);
    for(size_t i  = 0; i < length_text; i++)
    {
        if(isdigit(num_text[i]) == 0) // If the character is not a digit
        {
            flag = 0;
        }
    }

    return flag; // Returns 1 if all characters are digits (word is an integer)
}

size_t check_flags(asm_struct* assembly_struct) 
{
    size_t flags_ok = 1;    

    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {   
        if(strcmp(assembly_struct->toks[i].text, "JMP") == 0) // If the function is JMP
        {
            char* flag_name = assembly_struct->toks[i+1].text;
            for(size_t j = 0; j < assembly_struct->num_toks ; j++) // Checks all tokens
            {   
                if(assembly_struct->toks[j].type == flg) // If the command is flag
                {   
                    if(((strcmp(assembly_struct->toks[j].text, flag_name) == 0) && (j != 0) && (strcmp(assembly_struct->toks[j-1].text, "JMP") != 0)) || ((strcmp(assembly_struct->toks[j].text, flag_name) == 0) && (j == 0))) // Except flags after JMP or if the flag is the first command in the asm code                 
                    {   
                        assembly_struct->toks[i + 1].value = assembly_struct->toks[j + 1].new_index; 
                        flags_ok = 1; // Flag exists
                        break;
                    }
                    else 
                    {
                        flags_ok = 0; // Flag does not exist
                    }
                }
            }

            if(flags_ok == 0) 
            {   
                assembly_struct->toks[i].error_code = ERR_NO_FLAG_TO_JMP;
                strcpy((char*)assembly_struct->toks[i].status, "--");
            }
        }
    }

    return flags_ok; // Returns '1' if all flags are ok and '0' if there is some flag missing
}

size_t check_func(asm_struct* assembly_struct) 
{
    size_t funcs_ok = 1;

    if(assembly_struct->num_toks > 1)
    {
        for(size_t i = 0; i < assembly_struct->num_toks; i++)
        {   
            if(strcmp(assembly_struct->toks[i].text, "CALL") == 0) // Checks all tokens after CALL
            {
                char* func_name = assembly_struct->toks[i+1].text; // Gets the name of the function which is called
                for(size_t j = 0; j < assembly_struct->num_toks ; j++) // Searches through the ALL tokens!
                {   
                    if(assembly_struct->toks[j].type == fnc) // If the token is a function
                    {   
                        if(((strcmp(assembly_struct->toks[j].text, func_name) == 0) && (j != 0) && (strcmp(assembly_struct->toks[j-1].text, "CALL") != 0)) || ((strcmp(assembly_struct->toks[j].text, func_name) == 0) && (j == 0))) // The token is not a call of the function or is the firts command in the assembly code
                        {   
                            funcs_ok = 1; // Calls declared function
                            assembly_struct->toks[i + 1].value = assembly_struct->toks[j + 1].new_index;
                            break;
                        }
                        else 
                        {
                            funcs_ok = 0; // Calls undeclared function
                        }
                    }
                }
                if(funcs_ok == 0)
                {   
                    assembly_struct->toks[i].error_code = ERR_CALLS_NON_EXISTEN_FNC;
                    strcpy((char*)assembly_struct->toks[i].status, "--");
                }
            }  
        }
        return funcs_ok; // Returns '1' if all CALL commands call declared functions 
    }
    else
    {
        return funcs_ok; // Returns '1' if all CALL commands call declared functions 
    }
}

size_t check_fnc_declaration(asm_struct* assembly_struct) 
{
    size_t declaration_ok = 1; // Returns 1 if all declarations of function are uniqe
    if(assembly_struct->num_toks > 1)
    {
        for(size_t i = 0; i < assembly_struct->num_toks; i++)
            {   
                size_t positon_of_first_decl = i; // This value stores the first position of the function declaration
                if(((assembly_struct->toks[i].text[(strlen(assembly_struct->toks[i].text) - 1)] == ':') &&  (i > 0) && (strcmp(assembly_struct->toks[i-1].text, "CALL") != 0)) || (assembly_struct->toks[i].text[(strlen(assembly_struct->toks[i].text) - 1)] == ':') &&  (i == 0)) // If the token is the fist declaration of the function and is not a call of the function 
                {
                    char* func_name = assembly_struct->toks[i].text; // The function name that is used in order to search another declarations of the function with the same name
                    for(size_t j = i + 1; j < assembly_struct->num_toks ; j++) // Check the tokens after the firts function declaration
                    {   
                        if(assembly_struct->toks[j].type == fnc) // If the token is a function
                        {   
                            if((strcmp(assembly_struct->toks[j].text, func_name) == 0) && (strcmp(assembly_struct->toks[j-1].text, "CALL") != 0)) // If the token is a function declaration and is not a call of the function
                            {   
                                i = j; // Check all tokens after found one (prevents upper search)
                                declaration_ok = 0;
                                assembly_struct->toks[j].error_code = ERR_DOUBLE_DECL_OF_FNC;
                                strcpy((char*)assembly_struct->toks[i].status, "--");
                                break;
                            }
                            else 
                            {
                                declaration_ok = 1; // The declaration is an uniqe one
                            }
                        }
                    }
                    if(declaration_ok == 0)
                    {   
                        assembly_struct->toks[positon_of_first_decl].error_code = ERR_FIRST_DECL_OF_FNC; 
                        strcpy((char*)assembly_struct->toks[positon_of_first_decl].status, "--");
                        break;
                    }
                }
            }    

        return declaration_ok; // Returns 1 if all declarations of function are uniqe
    }
    else
    {
        return declaration_ok; // Returns 1 if all declarations of function are uniqe
    }
}

size_t check_next_reg(asm_struct* assembly_struct, size_t i)
{
    //printf("%s", assembly_struct->toks[i+1].text);
    if((strcmp(assembly_struct->toks[i+1].text, "ax") == 0) || (strcmp(assembly_struct->toks[i+1].text, "bx") == 0) || (strcmp(assembly_struct->toks[i+1].text, "cx") == 0) || (strcmp(assembly_struct->toks[i+1].text, "dx") == 0) || (strcmp(assembly_struct->toks[i+1].text, "rcx") == 0) || (strcmp(assembly_struct->toks[i+1].text, "rax") == 0) || (strcmp(assembly_struct->toks[i+1].text, "rbx") == 0))
    {
        return 1; // Returns 1 if the next token is reg 
    }
    else
    {
        return 0;
    }
}

size_t check_reg_inner(asm_struct* assembly_struct, char* inner_text)
{
    if((strcmp(inner_text, "ax") == 0) || (strcmp(inner_text, "bx") == 0) || (strcmp(inner_text, "cx") == 0) || (strcmp(inner_text, "dx") == 0) || (strcmp(inner_text, "rcx") == 0) || (strcmp(inner_text, "rax") == 0) || (strcmp(inner_text, "rbx") == 0))
    {
        return 1; // Returns 1 if the next token is reg 
    }
    else
    {
        return 0;
    }
}

void new_index_tok(asm_struct* assembly_struct, size_t index_cmd)
{
    size_t new_index = 0;
    
    if((assembly_struct->toks[index_cmd].type != flg) && (assembly_struct->toks[index_cmd].type != fnc))
    {
        for(size_t i = 0; i < index_cmd; i++)
        {
            if(assembly_struct->toks[i].type == cmd || assembly_struct->toks[i].type == val || assembly_struct->toks[i].type == reg || assembly_struct->toks[i].type == ret)
            {
                new_index++;
            }
        }
        assembly_struct->toks[index_cmd].new_index = new_index;
    }
    else
    {
        assembly_struct->toks[index_cmd].new_index = - 1;
    }
}

void put_new_index(asm_struct* assembly_struct)
{
    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {
        new_index_tok(assembly_struct, i);
    }
}