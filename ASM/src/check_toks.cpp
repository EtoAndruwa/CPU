#include "assembler.h"

/**
 * @brief           | (OK) Checks does the number contain only digits and .
 * 
 * @param num_text  | The string that must be checked
 * @return size_t   | Returns '1' if all characters are digit or contain '.'
 */
size_t check_num(char* num_text) 
{
    size_t flag = 1; // Returns 1 if all characters are digit or contain '.'

    size_t length_text = strlen(num_text);
    for(size_t i  = 0; i < length_text; i++)
    {
        char check_char = num_text[i];

        if((isdigit(check_char) == 0) && (check_char != '.')) // Check does the text contain digits and/or '.'
        {
            flag = 0;
        }
    }

    return flag; // Returns 1 if all characters are digit or contain '.'
}

/**
 * @brief                  | (OK) Checks is the next token is a number
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct 
 * @param i                | The total number of tokens
 * @return size_t          | Returns '1' if the next token is number
 */
size_t check_next_token(asm_struct* assembly_struct, size_t i) 
{
    if(check_num(assembly_struct->toks[i+1].text))
    {
        return 1; // Returns 1 if the next token is number
    }
}

/**
 * @brief                  | (OK) Checks all token for being valid
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 * @return size_t          | Returns '1' if all tokens are valid and code can be converted into assembly 
                           | code OR returns '0' if some token is invalid or asm struct has an error
 */
size_t check_all_valid(asm_struct* assembly_struct) 
{
    size_t flag = 1; // Returns 1 if all valid and code can be converted into assembly code

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

/**
 * @brief             | (FOR_FUTURE) Checks the valid memmory addressing in the command
 * 
 * @param token_text  | The token's text that must be checked for closing brackets 
 * @return size_t     | Returns '1' if brackets are closed
 */
size_t check_brackets(char* token_text) 
{
    size_t closed = 0;  

    if((token_text[0] == '[') && (token_text[strlen(token_text - 1)] == ']'))
    {
        closed = 1;
    }

    return closed;  // Returns 1 if brackets are closed
}

/**
 * @brief           | (OK) Checks does the number contain only digits (is an integer)
 * 
 * @param num_text  | The token's text that must be checked for being an integer
 * @return size_t   | Returns '1' if all characters are digits (word is an integer)
 */
size_t check_num_int(char* num_text) 
{
    size_t flag = 1; 

    size_t length_text = strlen(num_text);
    for(size_t i  = 0; i < length_text; i++)
    {
        char check_char = num_text[i];

        if(isdigit(check_char) == 0) // If the character is not a digit
        {
            flag = 0;
        }
    }

    return flag; // Returns 1 if all characters are digits (word is an integer)
}

/**
 * @brief                  | (OK) Checks all flags for existence 
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 * @return size_t          | Returns '1' if all flags are ok and '0' if there is some flag missing
 */
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

/**
 * @brief                  | (OK) Checks all function calls 
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 * @return size_t          | Returns '1' if all CALL commands call declared functions and '0' if call undeclared functions
 */
size_t check_func(asm_struct* assembly_struct) 
{
    size_t funcs_ok = 1;

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

/**
 * @brief                  | (OK) Checks all function declarations for double declaration
 * 
 * @param assembly_struct  | The struct containing all information about the asm struct
 * @return size_t          | Returns '1' if all declarations of functions are uniqe and '0' if double declarations are exist in the code
 */
size_t check_fnc_declaration(asm_struct* assembly_struct) 
{
    size_t declaration_ok = 1; // Returns 1 if all declarations of function are uniqe

    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {   
        size_t positon_of_first_decl = i; // This value stores the first position of the function declaration
        if((assembly_struct->toks[i].text[(strlen(assembly_struct->toks[i].text) - 1)] == ':') && (strcmp(assembly_struct->toks[i-1].text, "CALL") != 0)) // If the token is the fist declaration of the function and is not a call of the function 
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