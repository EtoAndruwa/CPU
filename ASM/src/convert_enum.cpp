#include "assembler.h"

const char* enum_token_err_to_string(size_t code)  // for token
{
    switch(code)
    {
        case TOKEN_OK:
            return "TOKEN_OK";
        case ERR_TOKEN_WITH_VALUE:
            return "ERR_TOKEN_WITH_VALUE";
        case ERR_TOKEN_WITHOUT_VALUE:
            return "ERR_TOKEN_WITHOUT_VALUE";
        case ERR_INVALID_TOKEN:
            return "ERR_INVALID_TOKEN";
        case ERR_NO_FLAG:
            return "ERR_NO_FLAG";
        case ERR_INVALID_FLAG:
            return "ERR_INVALID_FLAG";
        case ERR_NO_FLAG_TO_JMP:
            return "ERR_NO_FLAG_TO_JMP";
        case ERR_INVALID_REG:
            return "ERR_INVALID_REG";
        case ERR_CALLS_NON_EXISTEN_FNC:
            return "ERR_CALLS_NON_EXISTEN_FNC";
        case ERR_NO_FNC_NAME:
            return "ERR_NO_FNC_NAME";
        case ERR_DOUBLE_DECL_OF_FNC:
            return "ERR_DOUBLE_DECL_OF_FNC";
        case ERR_FIRST_DECL_OF_FNC:
            return "ERR_FIRST_DECL_OF_FNC";
        case ERR_TO_CHECK_INNER_RAM:
            return "ERR_TO_CHECK_INNER_RAM";
        case ERR_DOUBLE_DECL_OF_FLAG:
            return "ERR_DOUBLE_DECL_OF_FLAG";
        case ERR_FIRST_DECL_OF_FLAG:
            return "ERR_FIRST_DECL_OF_FLAG";
        default:
            return "NEW_ERROR_CODE";       
    }
}

const char* enum_struct_err_to_string(size_t code) // for struct
{
    switch(code)
    {
        case ERR_ASM_CODE_BUF_NULL:
            return "ERR_ASM_CODE_BUF_NULL";
        case ERR_CLOSE_ASM_FILE:
            return "ERR_CLOSE_ASM_FILE";
        case ERR_CLOSE_LOG_FILE:
            return "ERR_CLOSE_LOG_FILE";
        case ERR_CLOSE_BIN_FILE:
            return "ERR_CLOSE_BIN_FILE";
        case ERR_EMPTY_ASM_FILE:
            return "ERR_EMPTY_ASM_FILE";
        case ERR_OPEN_ASM_FILE:
            return "ERR_OPEN_ASM_FILE";
        case ERR_OPEN_LOG_FILE:
            return "ERR_OPEN_LOG_FILE";
        case ERR_OPEN_BIN_FILE:
            return "ERR_OPEN_BIN_FILE";
        case ERR_TO_WRITE_CODE:
            return "ERR_TO_WRITE_CODE";
        case ERR_TO_CALLOC_TOKS:
            return "ERR_TO_CALLOC_TOKS";
        case ERR_TO_CALLOC_ASM_BUF:
            return "ERR_TO_CALLOC_ASM_BUF";
        case ERR_READ_TO_ASM_BUF:
            return "ERR_READ_TO_ASM_BUF";
        case ERR_TO_CALLOC_BIN_CODES:
            return "ERR_TO_CALLOC_BIN_CODES";
        case ERR_TO_REALLOC_TOKS:
            return "ERR_TO_REALLOC_TOKS";
        case ERR_CLOSE_LISTING:
            return "ERR_CLOSE_LISTING";
        case ERR_OPEN_LISTING:
            return "ERR_OPEN_LISTING";
        default:
            return "STRUCT_OK"; 
    }
}

const char* enum_type_to_string(size_t code) // for token type
{
    switch(code)
    {
        case cmd:
            return "cmd";
        case reg:
            return "reg";
        case val:
            return "val";
        case flg:
            return "flg";
        case fnc:
            return "fnc";
        default:
            return "---";
    }
}
