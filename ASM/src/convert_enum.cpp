#include "assembler.h"

const char* enum_token_err_to_string(size_t code)  // for token
{
    switch(code)
    {
        #define DEF_CMD_STRING(code)      \
            case code:                    \
                return #code;             \

        DEF_CMD_STRING(TOKEN_OK)
        DEF_CMD_STRING(ERR_INVALID_TOKEN)
        DEF_CMD_STRING(ERR_TOKEN_WITHOUT_VALUE)
        DEF_CMD_STRING(ERR_TOKEN_WITH_VALUE)
        DEF_CMD_STRING(ERR_NO_FLAG)
        DEF_CMD_STRING(ERR_INVALID_FLAG)
        DEF_CMD_STRING(ERR_INVALID_REG)
        DEF_CMD_STRING(ERR_CALLS_NON_EXISTEN_FNC)
        DEF_CMD_STRING(ERR_NO_FNC_NAME)
        DEF_CMD_STRING(ERR_DOUBLE_DECL_OF_FNC)
        DEF_CMD_STRING(ERR_FIRST_DECL_OF_FNC)
        DEF_CMD_STRING(ERR_TO_CHECK_INNER_RAM)
        DEF_CMD_STRING(ERR_DOUBLE_DECL_OF_FLAG)
        DEF_CMD_STRING(ERR_FIRST_DECL_OF_FLAG)
        DEF_CMD_STRING(ERR_INVAL_RAM_ADDRESSING)

        #undef DEF_CMD_STRING
        default:
            return "NEW_ERROR_CODE";
    }
}

const char* enum_struct_err_to_string(size_t code) // for struct
{
    switch(code)
    {
        #define DEF_CMD_STRING(code)      \
            case code:                    \
                return #code;             \

        DEF_CMD_STRING(STRUCT_OK)
        DEF_CMD_STRING(ERR_ASM_CODE_BUF_NULL)
        DEF_CMD_STRING(ERR_OPEN_ASM_FILE)
        DEF_CMD_STRING(ERR_OPEN_BIN_FILE)
        DEF_CMD_STRING(ERR_CLOSE_ASM_FILE)
        DEF_CMD_STRING(ERR_CLOSE_BIN_FILE)
        DEF_CMD_STRING(ERR_EMPTY_ASM_FILE)
        DEF_CMD_STRING(ERR_OPEN_LOG_FILE)
        DEF_CMD_STRING(ERR_CLOSE_LOG_FILE)
        DEF_CMD_STRING(ERR_TO_WRITE_CODE)
        DEF_CMD_STRING(ERR_TO_CALLOC_TOKS)
        DEF_CMD_STRING(ERR_TO_CALLOC_ASM_BUF)
        DEF_CMD_STRING(ERR_READ_TO_ASM_BUF)
        DEF_CMD_STRING(ERR_TO_CALLOC_BIN_CODES)
        DEF_CMD_STRING(ERR_TO_REALLOC_TOKS)
        DEF_CMD_STRING(ERR_OPEN_LISTING)
        DEF_CMD_STRING(ERR_CLOSE_LISTING)

        #undef DEF_CMD_STRING
        default:
            return "NEW_ERROR_CODE";
    }
}

const char* enum_type_to_string(size_t code) // for token type
{
    switch(code)
    {
        #define DEF_CMD_STRING(code)      \
            case code:                    \
                return #code;             \

        DEF_CMD_STRING(EMPTY)
        DEF_CMD_STRING(CMD)
        DEF_CMD_STRING(REG)
        DEF_CMD_STRING(VAL)
        DEF_CMD_STRING(FLG)
        DEF_CMD_STRING(FNC)

        #undef DEF_CMD_STRING
        default:
            return "NEW_ERROR_CODE";
    }
}

const char* get_cmd_string(size_t cmd_code)
{
    switch(cmd_code)
    {
        #define DEF_CMD_STRING(cmd_code)      \
            case cmd_code:                    \
                return #cmd_code;             \

        DEF_CMD_STRING(HLT)
        DEF_CMD_STRING(PUSH)
        DEF_CMD_STRING(POP)
        DEF_CMD_STRING(DEC)
        DEF_CMD_STRING(JZ)
        DEF_CMD_STRING(ADD)
        DEF_CMD_STRING(SUB)
        DEF_CMD_STRING(MUL)
        DEF_CMD_STRING(DIV)
        DEF_CMD_STRING(SQRT)
        DEF_CMD_STRING(OUT)
        DEF_CMD_STRING(RET)
        DEF_CMD_STRING(JMP)
        DEF_CMD_STRING(AX)
        DEF_CMD_STRING(BX)
        DEF_CMD_STRING(CX)
        DEF_CMD_STRING(DX)
        DEF_CMD_STRING(CALL)

        #undef DEF_CMD_STRING
        default:
            return "NEW_CMD";
    }
}
