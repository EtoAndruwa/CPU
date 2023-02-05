#include "assembler.h"

const char* enum_token_err_to_string(size_t code) // (OK) Сonverts an enum's int value to the enum's string value
{
    size_t check_code = code;
    switch(check_code)
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
        default:
            return "NEW_ERROR_CODE";
            break;        
    }
}

const char* enum_to_string(size_t code) // (OK) Сonverts an enum's int value to the enum's string value
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

const char* enum_type_to_string(size_t code) // (OK) Сonverts an enum's int value to the enum's string value
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
        default:
            return "---";
            break;
    }
}