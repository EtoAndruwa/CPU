#include "disassembler.h"

const char* enum_struct_err_to_string(size_t code) // for struct
{
    switch(code)
    {
        #define DEF_CMD_STRING(code)      \
            case code:                    \
                return #code;             \

        DEF_CMD_STRING(STRUCT_OK)
        DEF_CMD_STRING(ERR_OPEN_BIN_FILE)
        DEF_CMD_STRING(ERR_CLOSE_BIN_FILE)
        DEF_CMD_STRING(ERR_OPEN_DUMP_FILE)
        DEF_CMD_STRING(ERR_CLOSE_DUMP_FILE)
        DEF_CMD_STRING(ERR_CALLOC_BIN_BUF)
        DEF_CMD_STRING(ERR_INV_READ_NUM_CMD)
        DEF_CMD_STRING(ERR_CANNOT_READ_CMD)
        DEF_CMD_STRING(ERR_CALLOC_COMMANDS)
        DEF_CMD_STRING(ERR_OPEN_ASM_FILE)
        DEF_CMD_STRING(ERR_CLOSE_ASM_FILE)

        #undef DEF_CMD_STRING
        default:
            return "NEW_ERROR_CODE";
    }
}

const char* get_cmd_string(size_t cmd_code)
{
    switch(cmd_code)
    {
        case PUSH_ST:
            return "PUSH";
        case PUSH_REG:
            return "PUSH";
        case PUSH_RAM_VAL:
            return "PUSH";
        case PUSH_RAM_REG:
            return "PUSH";
        case POP_REG:
            return "POP";
        case POP_RAM_VAL:
            return "POP";
        case POP_RAM_REG:
            return "POP";
        
        #define DEF_CMD_STRING(cmd_code)      \
            case cmd_code:                    \
                return #cmd_code;             \

        DEF_CMD_STRING(HLT)
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
