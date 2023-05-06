#include "stack.h"

const char* Enum_to_string(int code) // (CHECKED) Сonverts an enum's int value to the enum's string value
{
    switch(code)
    {
        #define DEF_CMD_STRING(code)      \
            case code:                    \
                return #code;             \

        DEF_CMD_STRING(STACK_IS_OK)
        DEF_CMD_STRING(ERR_NULL_DATA)
        DEF_CMD_STRING(ERR_OUT_OF_STACK_RIGHT)
        DEF_CMD_STRING(ERR_OUT_OF_STACK_LEFT)
        DEF_CMD_STRING(ERR_LEFT_CANARY_DEAD)
        DEF_CMD_STRING(ERR_HASH_CHANGED)
        DEF_CMD_STRING(ERR_TO_CALLOC_STACK)
        DEF_CMD_STRING(ERR_TO_REALLOC_DOWN)
        DEF_CMD_STRING(ERR_TO_REALLOC_UP)
        DEF_CMD_STRING(ERR_TO_CALLOC_CMD_STR)
        DEF_CMD_STRING(ERR_CLOSE_DUMP_FILE)
        DEF_CMD_STRING(ERR_OPEN_ACTION_LOG)
        DEF_CMD_STRING(ERR_DIV_TO_ZERO)
        DEF_CMD_STRING(ERR_UNKNOWN_STACK_CMD)
        DEF_CMD_STRING(ERR_SQRT_FROM_NEGATIVE)

        #undef DEF_CMD_STRING
        default:
            return "NEW_ERROR_CODE";
    }
}
