#include "assembler.h"

size_t check_is_int(char* num_text) // CHECKED
{
    size_t length_text = strlen(num_text);

    if(num_text[0] == '-' && length_text == 1) // case for '-' minus sign only
    {
        return NOT_ALL_DIGITS;
    }
    if(num_text[0] != '-' && isdigit(num_text[0]) == 0) // case for negative int
    {    
        return NOT_ALL_DIGITS;
    }    
    for(size_t i = 1; i < length_text; i++)
    {
        if(isdigit(num_text[i]) == 0) // Check does the text contain digits only
        {
            return TOKEN_IS_NOT_INT;
        }
    }
    return TOKEN_IS_INT; 
}

size_t check_next_token(asm_struct* assembly_struct, size_t token_index) // CHECKED
{
    if((assembly_struct->num_toks - 1) > token_index)
    {
        if(check_is_int(assembly_struct->toks[token_index + 1].text) == TOKEN_IS_INT)
        {
            return NEXT_TOKEN_VAL;
        }
        else if(check_is_float(assembly_struct->toks[token_index + 1].text) == TOKEN_IS_FLT)
        {
            return NEXT_TOKEN_VAL;
        }   
        return NEXT_TOKEN_CMD;
    }
}

size_t check_all_valid(asm_struct* assembly_struct) // CHECKED
{
    if(assembly_struct->err_code != STRUCT_OK)
    {   
        ERROR_MESSAGE(stderr, assembly_struct->err_code)
        return assembly_struct->err_code;
    }

    for(size_t index = 0; index < assembly_struct->num_toks; index++)
    {
        if(assembly_struct->toks[index].error_code != TOKEN_OK)
        {   
            printf("\n While check_all_valid found error token\n");
            ERROR_MESSAGE(stderr, assembly_struct->toks[index].error_code)
            return SOME_TOKEN_INVALID; 
        }
    }

    return ALL_TOKENS_VALID; 
}

size_t check_brackets(char* token_text) // CHECKED
{
    return (((token_text[0] == '[') && (token_text[strlen(token_text) - 1] == ']'))? BRACKETS_OKEY: BRACKETS_NOT_OKEY);
}

int check_ram(asm_struct* assembly_struct, char* token_text, size_t index) // CHECKED
{
    if(check_brackets(token_text) == BRACKETS_OKEY)
    {
        size_t strlen_token_check = strlen(token_text);
        if(strlen_token_check >= 3 && strlen_token_check <= 4)
        {
            size_t length_of_inner = strlen_token_check - 1;
            char* str_check = (char*)calloc(length_of_inner, sizeof(char));

            if(str_check == nullptr)
            {
                assembly_struct->err_code = ERR_TO_CALLOC_INNER_RAM;
                dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
                ERROR_MESSAGE(stderr, assembly_struct->err_code)
                return assembly_struct->err_code;
            }

            strncpy(str_check, (token_text + 1), strlen_token_check - 2); // copies inner test [ax] -> ax
            str_check[strlen_token_check - 1] = '\0'; // makes null terminated string

            if(check_inner_reg(assembly_struct, str_check) == INNER_IS_REG)
            {
                if(strcmp(str_check, "ax") == 0)
                {
                    assembly_struct->toks[index].value= AX; 
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
                else if(strcmp(str_check, "ex") == 0)
                {
                    assembly_struct->toks[index].value = EX;
                }
                else if(strcmp(str_check, "fx") == 0)
                {   
                    assembly_struct->toks[index].value = FX;
                }                
                else if(strcmp(str_check, "hx") == 0)
                {
                    assembly_struct->toks[index].value = HX;
                }
                else if(strcmp(str_check, "ix") == 0)
                {   
                    assembly_struct->toks[index].value = IX;
                }

                assembly_struct->toks[index].type = REG;
                strcpy((char*)assembly_struct->toks[index].status, "OK");

                free(str_check); // frees inner reg text
                return INNER_IS_REG; 
            }
            else if(check_is_int(str_check) == TOKEN_IS_INT)
            {   
                assembly_struct->toks[index].value = atof(str_check);
                assembly_struct->toks[index].type  = VAL;
                strcpy((char*)assembly_struct->toks[index].status, "OK");

                free(str_check);
                return INNER_VAL; 
            }

            assembly_struct->err_code = ERR_INNER_RAM_IF_FLT;
            dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
            ERROR_MESSAGE(stderr, assembly_struct->err_code)
            return assembly_struct->err_code;
        }
        else if(strlen_token_check > 5)
        {
            size_t length_of_inner = strlen_token_check - 1; 
            char* str_check = (char*)calloc(length_of_inner, sizeof(char)); // inner text inside []

            if(str_check == nullptr)
            {
                assembly_struct->err_code = ERR_TO_CALLOC_INNER_RAM;
                dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
                ERROR_MESSAGE(stderr, assembly_struct->err_code)
                return assembly_struct->err_code;
            }

            strncpy(str_check, (token_text + 1), strlen_token_check - 2); // copy [ax+10] -> ax+10
            str_check[strlen_token_check - 1] = '\0'; // makes null terminated string

            char* position_plus_sing = strchr(str_check,' +'); // pointer to the +

            if(position_plus_sing == nullptr)
            {
                if(check_is_int(str_check) == TOKEN_IS_INT)
                {
                    assembly_struct->toks[index].value = atof(str_check);
                    assembly_struct->toks[index].type  = VAL;
                    strcpy((char*)assembly_struct->toks[index].status, "OK");

                    free(str_check);
                    return INNER_VAL; 
                }

                free(str_check);
                assembly_struct->err_code = ERR_INVAL_RAM_ADDRESSING;
                dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
                ERROR_MESSAGE(stderr, assembly_struct->err_code)
                return assembly_struct->err_code;
            }
            else
            {
                size_t text_bef_plus_len = position_plus_sing - str_check; // number of chars before + sign

                if(text_bef_plus_len > 0)
                {
                    char* text_bef_plus_ptr = (char*)calloc(text_bef_plus_len + 1, sizeof(char));

                    if(text_bef_plus_ptr == nullptr)
                    {
                        free(str_check);
                        assembly_struct->err_code = ERR_TO_CALLOC_INNER_RAM;
                        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
                        ERROR_MESSAGE(stderr, assembly_struct->err_code)
                        return assembly_struct->err_code;
                    }

                    strncpy(text_bef_plus_ptr, str_check, text_bef_plus_len); // copies the text before + sign
                    text_bef_plus_ptr[text_bef_plus_len] = '\0'; // makes null terminated string

                    printf("text_bef_plus_ptr: %s\n", text_bef_plus_ptr);
                    if(check_inner_reg(assembly_struct, position_plus_sing + 1) == INNER_IS_REG && (check_is_int(text_bef_plus_ptr) == TOKEN_IS_INT)) // 5+ax
                    {
                        put_inner_values(assembly_struct, index, text_bef_plus_ptr, position_plus_sing + 1);

                        free(str_check);
                        free(text_bef_plus_ptr);
                        return INNER_VAL_REG;
                    }
                    else if(check_inner_reg(assembly_struct, text_bef_plus_ptr) == INNER_IS_REG && (check_is_int(position_plus_sing + 1) == TOKEN_IS_INT)) // ax+5
                    {
                        put_inner_values(assembly_struct, index, position_plus_sing + 1, text_bef_plus_ptr);

                        free(str_check);
                        free(text_bef_plus_ptr);
                        return INNER_VAL_REG;
                    }
                } 
                free(str_check);
                assembly_struct->err_code = ERR_INVAL_RAM_ADDRESSING;
                dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
                ERROR_MESSAGE(stderr, assembly_struct->err_code)
                return assembly_struct->err_code;
            }   
        }
        return INNER_RAM_INVALID;
    }
    return INNER_RAM_INVALID;
}

size_t check_is_number(char* num_text) // CHECKED
{
    for(size_t i = 0; i < strlen(num_text); i++)
    {
        if(isdigit(num_text[i]) == 0) // If the character is not a digit
        {
            return NOT_ALL_DIGITS;
        }
    }
    return ALL_DIGITS; // Returns ALL_DIGITS if all characters are digits (word is an integer)
}

size_t check_flags(asm_struct* assembly_struct) // CHECKED
{
    size_t flags_ok = ALL_JMPS_OKEY;    

    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {   
        if(strcmp(assembly_struct->toks[i].text, "JMP") == 0 || strcmp(assembly_struct->toks[i].text, "JZ") == 0
            || strcmp(assembly_struct->toks[i].text, "JE") == 0 || strcmp(assembly_struct->toks[i].text, "JG") == 0
                || strcmp(assembly_struct->toks[i].text, "JNE") == 0 || strcmp(assembly_struct->toks[i].text, "JGE") == 0) // If the function is JMP
        {
            char* flag_name = assembly_struct->toks[i + 1].text;
            for(size_t j = 0; j < assembly_struct->num_toks ; j++) // Checks all tokens
            {   
                if(assembly_struct->toks[j].type == FLG) // If the command is flag
                {   
                    if(((strcmp(assembly_struct->toks[j].text, flag_name) == 0) && (j != 0) && ((strcmp(assembly_struct->toks[j - 1].text, "JMP") != 0) && 
                        (strcmp(assembly_struct->toks[j - 1].text, "JZ") != 0) && (strcmp(assembly_struct->toks[j - 1].text, "JE") != 0)&& 
                            (strcmp(assembly_struct->toks[j - 1].text, "JG") != 0) && (strcmp(assembly_struct->toks[j - 1].text, "JNE") != 0) && 
                                (strcmp(assembly_struct->toks[j - 1].text, "JGE") != 0))) || ((strcmp(assembly_struct->toks[j].text, flag_name) == 0) && (j == 0))) // Except flags after JMP or if the flag is the first command in the asm code                 
                    {   
                        for(size_t q = j + 1; q < assembly_struct->num_toks; q++)
                        {
                            if(assembly_struct->toks[q].new_index != -1)
                            {
                                assembly_struct->toks[i + 1].value= assembly_struct->toks[q].new_index;
                                break;
                            }
                        }
                        flags_ok = ALL_JMPS_OKEY; 
                        break;
                    }
                    flags_ok = SOME_JMP_NOT_OK; 
                }
            }

            if(flags_ok == SOME_JMP_NOT_OK) 
            {   
                assembly_struct->toks[i].error_code = ERR_NO_FLAG_TO_JMP;
                ERROR_MESSAGE(stderr, ERR_NO_FLAG_TO_JMP)
                strcpy((char*)assembly_struct->toks[i].status, "---");
            }
        }
    }
    return flags_ok; 
}

size_t check_func(asm_struct* assembly_struct) // CHECKED
{
    size_t funcs_ok = ALL_CALLS_OK;

    if(assembly_struct->num_toks > 1)
    {
        for(size_t i = 0; i < assembly_struct->num_toks; i++)
        {   
            if(strcmp(assembly_struct->toks[i].text, "CALL") == 0) // Checks all tokens after CALL
            {
                char* func_name = assembly_struct->toks[i + 1].text; // Gets the name of the function which is called
                for(size_t j = 0; j < assembly_struct->num_toks ; j++) // Searches through the ALL tokens!
                {   
                    if(assembly_struct->toks[j].type == FNC) // If the token is a function
                    {   
                        if(((strcmp(assembly_struct->toks[j].text, func_name) == 0) && (j != 0) && (strcmp(assembly_struct->toks[j - 1].text, "CALL") != 0)) ||
                             ((strcmp(assembly_struct->toks[j].text, func_name) == 0) && (j == 0))) // The token is not a call of the function or is the firts command in the assembly code
                        {   
                            funcs_ok = ALL_CALLS_OK; // Calls declared function
                            for(size_t q = j + 1; q < assembly_struct->num_toks; q++)
                            {
                                if(assembly_struct->toks[q].new_index != -1)
                                {
                                    assembly_struct->toks[i + 1].value= assembly_struct->toks[q].new_index;
                                    break;
                                }
                            }
                        }
                        funcs_ok = SOME_CALL_NOT_OKEY; // Calls undeclared function
                    }
                }
                if(funcs_ok == SOME_CALL_NOT_OKEY)
                {   
                    assembly_struct->toks[i].error_code = ERR_CALLS_NON_EXISTEN_FNC;
                    ERROR_MESSAGE(stderr, ERR_CALLS_NON_EXISTEN_FNC)
                    strcpy((char*)assembly_struct->toks[i].status, "---");
                    break;
                }
            }  
        }
        return funcs_ok; 
    }
    return funcs_ok; 
}

size_t check_fnc_declaration(asm_struct* assembly_struct) // CHECKED
{
    size_t func_decl_ok = ALL_FUNCS_OK; // Returns 1 if all declarations of function are uniqe

    if(assembly_struct->num_toks > 1)
    {
        for(size_t i = 0; i < assembly_struct->num_toks; i++)
        {   
            size_t positon_of_first_decl = i; // This value stores the first position of the function declaration
            if((strlen(assembly_struct->toks[i].text) > 1) && ((assembly_struct->toks[i].text[(strlen(assembly_struct->toks[i].text) - 1)] == ':') &&  (i > 0) 
                && (strcmp(assembly_struct->toks[i - 1].text, "CALL") != 0)) || (assembly_struct->toks[i].text[(strlen(assembly_struct->toks[i].text) - 1)] == ':') &&  
                    (i == 0)) // If the token is the fist declaration of the function and is not a call of the function 
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
                            strcpy((char*)assembly_struct->toks[i].status, "---");
                            break;
                        }
                        func_decl_ok = ALL_FUNCS_OK; // The declaration is an uniqe one
                    }
                }
                if(func_decl_ok == SOME_FUNC_NOT_OK)
                {   
                    assembly_struct->toks[positon_of_first_decl].error_code = ERR_FIRST_DECL_OF_FNC; 
                    ERROR_MESSAGE(stderr, ERR_FIRST_DECL_OF_FNC)
                    strcpy((char*)assembly_struct->toks[positon_of_first_decl].status, "---");
                    break;
                }
            }
        }    
        return func_decl_ok; 
    }
    return func_decl_ok; 
}

size_t check_flag_declaration(asm_struct* assembly_struct) // CHECKED
{
    size_t  flag_decl_ok = ALL_FLAGS_OKEY; // Returns 1 if all declarations of flag are uniqe

    if(assembly_struct->num_toks > 1)
    {
        for(size_t i = 0; i < assembly_struct->num_toks; i++)
        {   
            size_t positon_of_first_decl = i; // This value stores the first position of the flag declaration
            if(((strlen(assembly_struct->toks[i].text) > 1) && (assembly_struct->toks[i].text[0] == ':') &&  (i > 0) && 
                (strcmp(assembly_struct->toks[i - 1].text, "JMP") != 0) && (strcmp(assembly_struct->toks[i - 1].text, "JZ") != 0)
                    && (strcmp(assembly_struct->toks[i - 1].text, "JE") != 0) && (strcmp(assembly_struct->toks[i - 1].text, "JG") != 0)
                        && (strcmp(assembly_struct->toks[i - 1].text, "JNE") != 0) && (strcmp(assembly_struct->toks[i - 1].text, "JGE") != 0)) || 
                            (assembly_struct->toks[i].text[0] == ':') &&  (i == 0)) // If the token is the fist declaration of the function and is not a call of the function 
            {
                char* flag_name = assembly_struct->toks[i].text; // The flag name that is used in order to search another declarations of the flag with the same name
                for(size_t j = i + 1; j < assembly_struct->num_toks; j++) // Check the tokens after the firts flag declaration
                {   
                    if(assembly_struct->toks[j].type == FLG) // If the token is a flag
                    {   
                        if((strcmp(assembly_struct->toks[j].text, flag_name) == 0) && (strcmp(assembly_struct->toks[j - 1].text, "JMP") != 0) && (strcmp(assembly_struct->toks[j - 1].text, "JZ") != 0)
                            && (strcmp(assembly_struct->toks[j - 1].text, "JE") != 0) && (strcmp(assembly_struct->toks[j - 1].text, "JNE") != 0)
                             && (strcmp(assembly_struct->toks[j - 1].text, "JG") != 0) && (strcmp(assembly_struct->toks[j - 1].text, "JGE") != 0)) // If the token is a function declaration and is not a call of the function
                        {   
                            i = j; // Check all tokens after found one (prevents upper search)
                            flag_decl_ok = SOME_FLAG_NOT_OK;
                            assembly_struct->toks[j].error_code = ERR_DOUBLE_DECL_OF_FLAG;
                            strcpy((char*)assembly_struct->toks[i].status, "---");
                            break;
                        }
                        flag_decl_ok = ALL_FLAGS_OKEY; // The declaration is an uniqe one
                    }
                }
                if(flag_decl_ok == SOME_FLAG_NOT_OK)
                {   
                    assembly_struct->toks[positon_of_first_decl].error_code = ERR_FIRST_DECL_OF_FLAG; 
                    ERROR_MESSAGE(stderr, ERR_FIRST_DECL_OF_FLAG)
                    strcpy((char*)assembly_struct->toks[positon_of_first_decl].status, "---");
                    break;
                }
            }
        }    
        return flag_decl_ok; 
    }
    return flag_decl_ok; 
}

size_t check_next_reg(asm_struct* assembly_struct, size_t cmd_index) // CHECKED
{
    if((strcmp(assembly_struct->toks[cmd_index + 1].text, "ax") == 0) || (strcmp(assembly_struct->toks[cmd_index + 1].text, "bx") == 0)
        || (strcmp(assembly_struct->toks[cmd_index + 1].text, "cx") == 0) || (strcmp(assembly_struct->toks[cmd_index + 1].text, "dx") == 0)
            || (strcmp(assembly_struct->toks[cmd_index + 1].text, "ex") == 0) || (strcmp(assembly_struct->toks[cmd_index + 1].text, "fx") == 0) 
                || (strcmp(assembly_struct->toks[cmd_index + 1].text, "hx") == 0) || (strcmp(assembly_struct->toks[cmd_index + 1].text, "ix") == 0))
    {
        return NEXT_TOKEN_IS_REG; 
    }

    return NEXT_TOKEN_NOT_REG;
}

size_t check_inner_reg(asm_struct* assembly_struct, char* inner_text) // CHECKED 
{
    if((strcmp(inner_text, "ax") == 0) || (strcmp(inner_text, "bx") == 0) || (strcmp(inner_text, "cx") == 0) || (strcmp(inner_text, "dx") == 0)
        || (strcmp(inner_text, "ex") == 0) || (strcmp(inner_text, "fx") == 0) || (strcmp(inner_text, "hx") == 0) || (strcmp(inner_text, "ix") == 0))
    {
        return INNER_IS_REG; 
    }

    return INNER_IS_NOT_REG; 
}

void put_inner_values(asm_struct* assembly_struct, size_t index, char* value_text_ptr, char* register_text_ptr) // CHECKED
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
    else if(strcmp(register_text_ptr, "ex") == 0)
    {
        assembly_struct->toks[index - 1].value = 3 << 2; 
    }
    else if(strcmp(register_text_ptr, "fx") == 0)
    {   
        assembly_struct->toks[index - 1].value = 5 << 2; 
    }
    else if(strcmp(register_text_ptr, "hx") == 0)
    {
        assembly_struct->toks[index - 1].value = 6 << 2; 
    }
    else if(strcmp(register_text_ptr, "ix") == 0)
    {   
        assembly_struct->toks[index - 1].value = 7 << 2; 
    }
    else
    {   
        assembly_struct->toks[index - 1].error_code = ERR_INVALID_REG;
        ERROR_MESSAGE(stderr, ERR_INVALID_REG)
        return;
    }

    if(check_is_int(value_text_ptr) != TOKEN_IS_INT)
    {
        assembly_struct->toks[index - 1].error_code = ERR_INVAL_RAM_ADDRESSING;
        ERROR_MESSAGE(stderr, ERR_INVAL_RAM_ADDRESSING)
        return;
    }

    assembly_struct->toks[index].value = atof(value_text_ptr);
    assembly_struct->toks[index].type  = VAL;
    strcpy((char*)assembly_struct->toks[index].status, "OK");
}

size_t length_double(char* str_double) 
{
    size_t old_length = strlen(str_double) - 1;
    size_t num_of_zeros = 0;
    size_t right_end_id = old_length;
    for(;  right_end_id >= 0; right_end_id--) // from the right to the left in order ot search first non zero digit and calculate the lenght of float
    {
        if(str_double[right_end_id] != '0')
        {
            break;
        }
        num_of_zeros++;
    }

    if(str_double[right_end_id] == '.' && str_double[right_end_id + 1] == '0')  //shorts the atof value to normal 1.00 -> 1'\0'
    {
        str_double[strchr(str_double, '.') - str_double] = '\0'; //shorts the atof value to normal 1.00 -> 1'\0'
        return strlen(str_double);
    }

    str_double[old_length + 1 - num_of_zeros] = '\0'; //shorts the atof value to normal 1.230000 -> 1.23'\0'
    return strlen(str_double);
}

size_t check_is_float(char* num_text) // CHECKED
{
    size_t length_text = strlen(num_text);
    size_t num_of_points = 0;

    if(num_text[0] == '-' && length_text == 1) // case for '-' minus sign only
    {
        return NOT_ALL_DIGITS;
    }
    if(num_text[0] != '-' && isdigit(num_text[0]) == 0) // case for negative float
    {    
        return NOT_ALL_DIGITS;
    }
    for(size_t i = 1; i < length_text; i++)
    {
        if(num_text[i] == '.')
        {   
            num_of_points++;
            continue;
        }
        if(num_of_points > 1)
        {
            return NOT_ALL_DIGITS;
        }
        if(isdigit(num_text[i]) == 0) // If the character is not a digit
        {
            return NOT_ALL_DIGITS;
        }
    }
    return TOKEN_IS_FLT; // Returns INNER_IS_FLT if the word if float
}

