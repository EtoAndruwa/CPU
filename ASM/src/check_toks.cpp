#include "assembler.h"

size_t check_num_int(char* num_text) 
{
    size_t is_int = TOKEN_IS_INT; // Returns 1 if all characters are digit or contain '.'

    size_t length_text = strlen(num_text);
    for(size_t i  = 0; i < length_text; i++)
    {
        char check_char = num_text[i];

        if(isdigit(check_char) != 0 || ((check_char == '-') && (i == 0))) // Check does the text contain digits
        {
            is_int = TOKEN_IS_INT;
        }
        else
        {
            is_int = TOKEN_IS_NOT_INT;
            break;
        }
    }

    return is_int; 
}

size_t check_next_token(asm_struct* assembly_struct, size_t i) 
{
    return ((((assembly_struct->num_toks - 1) > i) && (check_num_int(assembly_struct->toks[i+1].text) == TOKEN_IS_INT))? NEXT_TOKEN_VAL: NEXT_TOKEN_CMD);
}

size_t check_all_valid(asm_struct* assembly_struct) 
{
    if(assembly_struct->err_code != STRUCT_OK)
    {   
        return assembly_struct->err_code;
    }

    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {
        if(assembly_struct->toks[i].error_code != TOKEN_OK)
        {   
            printf("%d\n\n", i);
            return SOME_TOKEN_INVALID; 
        }
    }

    return ALL_TOKENS_VALID; 
}

size_t check_brackets(char* token_text) 
{
    return (((token_text[0] == '[') && (token_text[strlen(token_text) - 1] == ']'))? BRACKETS_OKEY: BRACKETS_NOT_OKEY);
}

size_t check_ram(asm_struct* assembly_struct, char* token_text, size_t index)
{
    if(check_brackets(token_text) == BRACKETS_OKEY)
    {
        size_t strlen_token_check = strlen(token_text);
        if(strlen_token_check >= 3 && strlen_token_check <= 5)
        {
            size_t length_of_inner = strlen_token_check- 1;
            char* str_check =(char*)calloc(length_of_inner, sizeof(char));

            if(str_check == nullptr)
            {
                assembly_struct->err_code = ERR_TO_CHECK_INNER_RAM;
                dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
                dtor_asm(assembly_struct);
                exit(ERR_TO_CHECK_INNER_RAM);
            }

            strncpy(str_check, (token_text + 1), strlen_token_check - 2);
            str_check[strlen_token_check - 1] = '\0';

            if(check_reg_inner(assembly_struct, str_check) == INNER_REG)
            {
                if(strcmp(str_check, "ax") == 0)
                {
                    assembly_struct->toks[index].value = AX; 
                }
                else if(strcmp(str_check, "bx") == 0)
                {
                    assembly_struct->toks[index].value = BX;
                }
                else if(strcmp(str_check, "cx") == 0)
                {
                    assembly_struct->toks[index].value = CX;
                }
                else if(strcmp(str_check, "dx") == 0)
                {   
                    assembly_struct->toks[index].value = DX;
                }
                assembly_struct->toks[index].type = REG;
                strcpy((char*)assembly_struct->toks[index].status, "OK");

                free(str_check);
                str_check = nullptr;
                return INNER_REG; 
            }
            else if(check_num_int(str_check) == TOKEN_IS_INT)
            {   
                assembly_struct->toks[index].value = atoi(str_check);
                assembly_struct->toks[index].type  = VAL;
                strcpy((char*)assembly_struct->toks[index].status, "OK");

                free(str_check);
                str_check = nullptr;
                return INNER_VAL; 
            }
        }
        else if(strlen_token_check > 5)
        {
            size_t length_of_inner = strlen_token_check - 1;
            char* str_check =(char*)calloc(length_of_inner, sizeof(char));

            if(str_check == nullptr)
            {
                assembly_struct->err_code = ERR_TO_CHECK_INNER_RAM;
                dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
                dtor_asm(assembly_struct);
                exit(ERR_TO_CHECK_INNER_RAM);
            }

            strncpy(str_check, (token_text + 1), strlen_token_check - 2);
            str_check[strlen_token_check - 1] = '\0';

            char* position_plus_sing = strchr(str_check,'+');

            if(position_plus_sing == nullptr)
            {
                if(check_num_int(str_check) == TOKEN_IS_INT)
                {
                    assembly_struct->toks[index].value = atoi(str_check);
                    assembly_struct->toks[index].type  = VAL;
                    strcpy((char*)assembly_struct->toks[index].status, "OK");

                    free(str_check);
                    str_check = nullptr;
                    return INNER_VAL; 
                }
                else
                {
                    free(str_check);
                    str_check = nullptr;
                    assembly_struct->err_code = ERR_INVAL_RAM_ADDRESSING;
                    dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
                    dtor_asm(assembly_struct);
                    exit(ERR_INVAL_RAM_ADDRESSING);
                }
            }
            else
            {
                size_t text_bef_plus_len = position_plus_sing - str_check;

                if(text_bef_plus_len > 0)
                {
                    char* text_bef_plus_ptr =(char*)calloc(text_bef_plus_len + 1, sizeof(char));

                    if(text_bef_plus_ptr == nullptr)
                    {
                        free(str_check);
                        str_check = nullptr;
                        assembly_struct->err_code = ERR_TO_CHECK_INNER_RAM;
                        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
                        dtor_asm(assembly_struct);
                        exit(ERR_TO_CHECK_INNER_RAM);
                    }

                    strncpy(text_bef_plus_ptr, str_check, text_bef_plus_len);
                    text_bef_plus_ptr[text_bef_plus_len] = '\0';

                    if(check_reg_inner(assembly_struct, position_plus_sing + 1) == INNER_REG && (check_num_int(text_bef_plus_ptr) == TOKEN_IS_INT))
                    {
                        put_inner_values(assembly_struct, index, text_bef_plus_ptr, position_plus_sing + 1);

                        free(str_check);
                        free(text_bef_plus_ptr);
                        text_bef_plus_ptr = nullptr;
                        str_check = nullptr;
                        return INNER_VAL_REG;
                    }

                    else if(check_reg_inner(assembly_struct, text_bef_plus_ptr) == INNER_REG && (check_num_int(position_plus_sing + 1) == TOKEN_IS_INT))
                    {
                        put_inner_values(assembly_struct, index, position_plus_sing + 1, text_bef_plus_ptr);

                        free(str_check);
                        free(text_bef_plus_ptr);
                        text_bef_plus_ptr = nullptr;
                        str_check = nullptr;
                        return INNER_VAL_REG;
                    }
                }
                else
                {   
                    free(str_check);
                    str_check = nullptr;
                    assembly_struct->err_code = ERR_INVAL_RAM_ADDRESSING;
                    dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
                    dtor_asm(assembly_struct);
                    exit(ERR_INVAL_RAM_ADDRESSING);
                }
            }   
        }
        else
        {
            return INNER_RAM_INVALID;
        }
    }
    else
    {
        return INNER_RAM_INVALID;
    }
}

size_t check_is_number(char* num_text) 
{
    size_t is_digits = ALL_DIGITS; 

    size_t length_text = strlen(num_text);
    for(size_t i  = 0; i < length_text; i++)
    {
        if(isdigit(num_text[i]) == 0) // If the character is not a digit
        {
            is_digits = NOT_ALL_DIGITS;
        }
    }

    return is_digits; // Returns 1 if all characters are digits (word is an integer)
}

size_t check_flags(asm_struct* assembly_struct) 
{
    size_t flags_ok = ALL_JMPS_OKEY;    

    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {   
        if(strcmp(assembly_struct->toks[i].text, "JMP") == 0 || strcmp(assembly_struct->toks[i].text, "JZ") == 0) // If the function is JMP
        {
            char* flag_name = assembly_struct->toks[i+1].text;
            for(size_t j = 0; j < assembly_struct->num_toks ; j++) // Checks all tokens
            {   
                if(assembly_struct->toks[j].type == FLG) // If the command is flag
                {   
                    if(((strcmp(assembly_struct->toks[j].text, flag_name) == 0) && (j != 0) && ((strcmp(assembly_struct->toks[j-1].text, "JMP") != 0) && (strcmp(assembly_struct->toks[j-1].text, "JZ") != 0))) || ((strcmp(assembly_struct->toks[j].text, flag_name) == 0) && (j == 0))) // Except flags after JMP or if the flag is the first command in the asm code                 
                    {   
                        for(size_t q = j + 1; q < assembly_struct->num_toks; q++)
                        {
                            if(assembly_struct->toks[q].new_index != -1)
                            {
                                assembly_struct->toks[i + 1].value = assembly_struct->toks[q].new_index;
                                break;
                            }
                        }
                        flags_ok = ALL_JMPS_OKEY; 
                        break;
                    }
                    else 
                    {
                        flags_ok = SOME_JMP_NOT_OK; 
                    }
                }
            }

            if(flags_ok == SOME_JMP_NOT_OK) 
            {   
                assembly_struct->toks[i].error_code = ERR_NO_FLAG_TO_JMP;
                strcpy((char*)assembly_struct->toks[i].status, "--");
            }
        }
    }

    return flags_ok; 
}

size_t check_func(asm_struct* assembly_struct) 
{
    size_t funcs_ok = ALL_CALLS_OK;

    if(assembly_struct->num_toks > 1)
    {
        for(size_t i = 0; i < assembly_struct->num_toks; i++)
        {   
            if(strcmp(assembly_struct->toks[i].text, "CALL") == 0) // Checks all tokens after CALL
            {
                char* func_name = assembly_struct->toks[i+1].text; // Gets the name of the function which is called
                for(size_t j = 0; j < assembly_struct->num_toks ; j++) // Searches through the ALL tokens!
                {   
                    if(assembly_struct->toks[j].type == FNC) // If the token is a function
                    {   
                        if(((strcmp(assembly_struct->toks[j].text, func_name) == 0) && (j != 0) && (strcmp(assembly_struct->toks[j-1].text, "CALL") != 0)) || ((strcmp(assembly_struct->toks[j].text, func_name) == 0) && (j == 0))) // The token is not a call of the function or is the firts command in the assembly code
                        {   
                            funcs_ok = ALL_CALLS_OK; // Calls declared function
                            for(size_t q = j + 1; q < assembly_struct->num_toks; q++)
                            {
                                if(assembly_struct->toks[q].new_index != -1)
                                {
                                    assembly_struct->toks[i + 1].value = assembly_struct->toks[q].new_index;
                                    break;
                                }
                            }
                            break;
                        }
                        else 
                        {
                            funcs_ok = SOME_CALL_NOT_OKEY; // Calls undeclared function
                        }
                    }
                }
                if(funcs_ok == SOME_CALL_NOT_OKEY)
                {   
                    assembly_struct->toks[i].error_code = ERR_CALLS_NON_EXISTEN_FNC;
                    strcpy((char*)assembly_struct->toks[i].status, "--");
                    break;
                }
            }  
        }
        return funcs_ok; 
    }
    else
    {
        return funcs_ok; 
    }
}

size_t check_fnc_declaration(asm_struct* assembly_struct) 
{
    size_t func_decl_ok = ALL_FUNCS_OK; // Returns 1 if all declarations of function are uniqe

    if(assembly_struct->num_toks > 1)
    {
        for(size_t i = 0; i < assembly_struct->num_toks; i++)
            {   
                size_t positon_of_first_decl = i; // This value stores the first position of the function declaration
                if((strlen(assembly_struct->toks[i].text) > 1) && ((assembly_struct->toks[i].text[(strlen(assembly_struct->toks[i].text) - 1)] == ':') &&  (i > 0) && (strcmp(assembly_struct->toks[i-1].text, "CALL") != 0)) || (assembly_struct->toks[i].text[(strlen(assembly_struct->toks[i].text) - 1)] == ':') &&  (i == 0)) // If the token is the fist declaration of the function and is not a call of the function 
                {
                    char* func_name = assembly_struct->toks[i].text; // The function name that is used in order to search another declarations of the function with the same name
                    for(size_t j = i + 1; j < assembly_struct->num_toks ; j++) // Check the tokens after the firts function declaration
                    {   
                        if(assembly_struct->toks[j].type == FNC) // If the token is a function
                        {   
                            if((strcmp(assembly_struct->toks[j].text, func_name) == 0) && (strcmp(assembly_struct->toks[j-1].text, "CALL") != 0)) // If the token is a function declaration and is not a call of the function
                            {   
                                i = j; // Check all tokens after found one (prevents upper search)
                                func_decl_ok = SOME_FUNC_NOT_OK;
                                assembly_struct->toks[j].error_code = ERR_DOUBLE_DECL_OF_FNC;
                                strcpy((char*)assembly_struct->toks[i].status, "--");
                                break;
                            }
                            else 
                            {
                                func_decl_ok = ALL_FUNCS_OK; // The declaration is an uniqe one
                            }
                        }
                    }
                    if(func_decl_ok == SOME_FUNC_NOT_OK)
                    {   
                        assembly_struct->toks[positon_of_first_decl].error_code = ERR_FIRST_DECL_OF_FNC; 
                        strcpy((char*)assembly_struct->toks[positon_of_first_decl].status, "--");
                        break;
                    }
                }
            }    
        return func_decl_ok; 
    }
    else
    {
        return func_decl_ok; 
    }
}

size_t check_flag_declaration(asm_struct* assembly_struct) 
{
    size_t  flag_decl_ok = ALL_FLAGS_OKEY; // Returns 1 if all declarations of flag are uniqe

    if(assembly_struct->num_toks > 1)
    {
        for(size_t i = 0; i < assembly_struct->num_toks; i++)
            {   
                size_t positon_of_first_decl = i; // This value stores the first position of the flag declaration
                if(((strlen(assembly_struct->toks[i].text) > 1) && (assembly_struct->toks[i].text[0] == ':') &&  (i > 0) && (strcmp(assembly_struct->toks[i-1].text, "JMP") != 0) && (strcmp(assembly_struct->toks[i-1].text, "JZ") != 0)) || (assembly_struct->toks[i].text[0] == ':') &&  (i == 0)) // If the token is the fist declaration of the function and is not a call of the function 
                {
                    char* flag_name = assembly_struct->toks[i].text; // The flag name that is used in order to search another declarations of the flag with the same name
                    for(size_t j = i + 1; j < assembly_struct->num_toks ; j++) // Check the tokens after the firts flag declaration
                    {   
                        if(assembly_struct->toks[j].type == FLG) // If the token is a flag
                        {   
                            if((strcmp(assembly_struct->toks[j].text, flag_name) == 0) && (strcmp(assembly_struct->toks[j-1].text, "JMP") != 0) && (strcmp(assembly_struct->toks[j-1].text, "JZ") != 0)) // If the token is a function declaration and is not a call of the function
                            {   
                                i = j; // Check all tokens after found one (prevents upper search)
                                flag_decl_ok = SOME_FLAG_NOT_OK;
                                assembly_struct->toks[j].error_code = ERR_DOUBLE_DECL_OF_FLAG;
                                strcpy((char*)assembly_struct->toks[i].status, "--");
                                break;
                            }
                            else 
                            {
                                flag_decl_ok = ALL_FLAGS_OKEY; // The declaration is an uniqe one
                            }
                        }
                    }
                    if(flag_decl_ok == SOME_FLAG_NOT_OK)
                    {   
                        assembly_struct->toks[positon_of_first_decl].error_code = ERR_FIRST_DECL_OF_FLAG; 
                        strcpy((char*)assembly_struct->toks[positon_of_first_decl].status, "--");
                        break;
                    }
                }
            }    

        return flag_decl_ok; 
    }
    else
    {
        return flag_decl_ok; 
    }
}

size_t check_next_reg(asm_struct* assembly_struct, size_t i)
{
    //printf("%s", assembly_struct->toks[i+1].text);
    if((strcmp(assembly_struct->toks[i+1].text, "ax") == 0) || (strcmp(assembly_struct->toks[i+1].text, "bx") == 0) || (strcmp(assembly_struct->toks[i+1].text, "cx") == 0) || 
            (strcmp(assembly_struct->toks[i+1].text, "dx") == 0))
    {
        return NEXT_TOKEN_IS_REG; 
    }
    else
    {
        return NEXT_TOKEN_NOT_REG;
    }
}

size_t check_reg_inner(asm_struct* assembly_struct, char* inner_text)
{
    if((strcmp(inner_text, "ax") == 0) || (strcmp(inner_text, "bx") == 0) || (strcmp(inner_text, "cx") == 0) || (strcmp(inner_text, "dx") == 0))
    {
        return INNER_REG; 
    }
    else
    {
        return INNER_NOT_REG; 
    }
}

void put_inner_values(asm_struct* assembly_struct, size_t index, char* value_text_ptr, char* register_text_ptr)
{
    if(strcmp(register_text_ptr, "ax") == 0)
    {
        assembly_struct->toks[index - 1].value = 0; 
    }
    else if(strcmp(register_text_ptr, "bx") == 0)
    {
        assembly_struct->toks[index - 1].value = 1 << 2; 
    }
    else if(strcmp(register_text_ptr, "cx") == 0)
    {
        assembly_struct->toks[index - 1].value = 1 << 3; 
    }
    else if(strcmp(register_text_ptr, "dx") == 0)
    {   
        assembly_struct->toks[index - 1].value = 1 << 4; 
    }

    assembly_struct->toks[index].value = atoi(value_text_ptr);
    assembly_struct->toks[index].type  = REG;
    strcpy((char*)assembly_struct->toks[index].status, "OK");
}
