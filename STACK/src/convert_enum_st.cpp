#include "stack.h"

const char* Enum_to_string(size_t code) // (OK) Сonverts an enum's int value to the enum's string value
{
    switch(code)
    {
        case STACK_IS_OK:
            return "STACK_IS_OK";
        case ERR_NULL_DATA:
            return "ERR_NULL_DATA";
        case ERR_OUT_OF_STACK_RIGHT:
            return "ERR_OUT_OF_STACK_RIGHT";
        case ERR_OUT_OF_STACK_LEFT:
            return "ERR_OUT_OF_STACK_LEFT";
        case ERR_LEFT_CANARY_DEAD:
            return "ERR_LEFT_CANARY_DEAD";
        case ERR_RIGHT_CANARY_DEAD:
            return "ERR_RIGHT_CANARY_DEAD";
        case ERR_HASH_CHANGED:
            return "ERR_HASH_CHANGED";
        case ERR_TO_CALLOC_STACK:
            return "ERR_TO_CALLOC_STACK";
        case ERR_TO_REALLOC_DOWN:
            return "ERR_TO_REALLOC_DOWN";
        case ERR_TO_REALLOC_UP:
            return "ERR_TO_REALLOC_UP";
        case ERR_TO_CALLOC_CMD_STR:
            return "ERR_TO_CALLOC_CMD_STR";
        case ERR_CLOSE_ACTION_LOG:
            return "ERR_CLOSE_ACTION_LOG";
        case ERR_OPEN_ACTION_LOG:
            return "ERR_OPEN_ACTION_LOG";
        case ERR_CLOSE_DUMP_FILE:
            return "ERR_OPEN_ACTION_LOG";
        case ERR_OPEN_DUMP_FILE:
            return "ERR_OPEN_DUMP_FILE";
        case ERR_DIV_TO_ZERO:
            return "ERR_DIV_TO_ZERO";
        default:
            return "NEW_ERROR_CODE"; 
    }
}
