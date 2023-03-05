#include "stack.h"

const char* Enum_to_string(size_t code) // (OK) Сonverts an enum's int value to the enum's string value
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

        #undef DEF_CMD_STRING
        default:
            return "NEW_ERROR_CODE";
    }
}
