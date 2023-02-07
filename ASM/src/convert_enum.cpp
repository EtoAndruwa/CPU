#include "assembler.h"

/**
 * @brief               | (OK) Сonverts an enum's int value to the enum's string value
 * 
 * @param code          | The enum code of the command
 * @return const char*  | Returns the string value of the tokens's error code 
 */
const char* enum_token_err_to_string(size_t code) 
{
    switch(code)
    {
        case TOKEN_OK:
            return "OK";
            break;
        case ERR_TOKEN_WITH_VALUE:
            return "ERR_TOKEN_WITH_VALUE";
            break;
        case ERR_TOKEN_WITHOUT_VALUE:
            return "ERR_TOKEN_WITHOUT_VALUE";
            break;
        case ERR_INVALID_TOKEN:
            return "ERR_INVALID_TOKEN";
            break;
        case ERR_NO_FLAG:
            return "ERR_NO_FLAG";
            break;
        case ERR_INVALID_FLAG:
            return "ERR_INVALID_FLAG";
            break;
        case ERR_NO_FLAG_TO_JMP:
            return "ERR_NO_FLAG_TO_JMP";
            break;
        case ERR_INVALID_REG:
            return "ERR_INVALID_REG";
            break;
        case ERR_CALLS_NON_EXISTEN_FNC:
            return "ERR_CALLS_NON_EXISTEN_FNC";
            break;
        case ERR_NO_FNC_NAME:
            return "ERR_NO_FNC_NAME";
            break;
        case ERR_DOUBLE_DECL_OF_FNC:
            return "ERR_DOUBLE_DECL_OF_FNC";
            break;
        case ERR_FIRST_DECL_OF_FNC:
            return "ERR_FIRST_DECL_OF_FNC";
            break;
        default:
            return "NEW_ERROR_CODE";
            break;        
    }
}

/**
 * @brief               | (OK) Сonverts an enum's int value to the enum's string value
 * 
 * @param code          | The enum code of the command
 * @return const char*  | Returns the string value of the asm struct's error code  
 */
const char* enum_struct_err_to_string(size_t code) 
{
    switch(code)
    {
        case ERR_ASM_CODE_BUF_NULL:
            return "ERR_ASM_CODE_BUF_NULL";
            break;
        case ERR_CLOSE_ASM_FILE:
            return "ERR_CLOSE_ASM_FILE";
            break;
        case ERR_CLOSE_LOG_FILE:
            return "ERR_CLOSE_LOG_FILE";
            break;
        case ERR_CLOSE_TRANSLATED_FILE:
            return "ERR_CLOSE_TRANSLATED_FILE";
            break;
        case ERR_EMPTY_ASM_FILE:
            return "ERR_EMPTY_ASM_FILE";
            break;
        case ERR_NO_HLT:
            return "ERR_NO_HLT";
            break;
        case ERR_OPEN_ASM_FILE:
            return "ERR_OPEN_ASM_FILE";
            break;
        case ERR_OPEN_LOG_FILE:
            return "ERR_OPEN_LOG_FILE";
            break;
        case ERR_OPEN_TRANSLATED_FILE:
            return "ERR_OPEN_TRANSLATED_FILE";
            break;
        default:
            return "STRUCT_OK"; 
            break;
    }
}

/**
 * @brief              | (OK) Сonverts an enum's int value to the enum's string value
 * 
 * @param code         | The enum code of the command
 * @return const char* | Returns the string value of the token's type code 
 */
const char* enum_type_to_string(size_t code) 
{
    switch(code)
    {
        case cmd:
            return "cmd";
            break;
        case reg:
            return "reg";
            break;
        case val:
            return "val";
            break;  
        case flg:
            return "flg";
            break;
        case fnc:
            return "fnc";
            break;
        default:
            return "---";
            break;
    }
}