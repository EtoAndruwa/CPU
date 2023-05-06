#include "CPU.h"

char* convert_enum_cpu(int error_code) // CHECKED
{
    switch(error_code)
    {
        #define DEF_CMD_STRING(error_code)      \
            case error_code:                    \
                return #error_code;             \

        DEF_CMD_STRING(CPU_OK)
        DEF_CMD_STRING(ERR_NULLPTR_RAM)
        DEF_CMD_STRING(ERR_RAM_ADDRESSING)
        DEF_CMD_STRING(ERR_OPEN_BIN_FILE)
        DEF_CMD_STRING(ERR_CALL_STACK_FULL)
        DEF_CMD_STRING(ERR_CALL_STACK_EMPT)
        DEF_CMD_STRING(ERR_OPEN_DMP_FILE)
        DEF_CMD_STRING(ERR_CLOSE_DMP_FILE)
        DEF_CMD_STRING(ERR_NEW_REG)
        DEF_CMD_STRING(ERR_UNKNOWN_CMD)
        DEF_CMD_STRING(ERR_INV_READ_NUM_CMD)
        DEF_CMD_STRING(ERR_CANNOT_READ_CMD)
        DEF_CMD_STRING(ERR_CALLOC_BIN_CODE)
        DEF_CMD_STRING(ERR_CLOSE_BIN_FILE)
        DEF_CMD_STRING(ERR_BIN_NULL_BEF_DTOR)        

        #undef DEF_CMD_STRING
        default:
            return "NEW_ERROR_CODE_CPU";
    }
}
