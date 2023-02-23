#include "CPU.h"

char* convert_enum_cpu(size_t error_code)
{
    switch(error_code)
    {
        case CPU_OK:
            return "CPU_OK";
        case ERR_NULLPTR_RAM:
            return "ERR_NULLPTR_RAM";
        case ERR_RAM_ADDRESSING:  
            return "ERR_RAM_ADDRESSING";
        case ERR_OPEN_BIN_FILE:  
            return "ERR_OPEN_BIN_FILE"; 
        case ERR_CALL_STACK_FULL:
            return "ERR_CALL_STACK_FULL";
        case ERR_CALL_STACK_EMPT:
            return "ERR_CALL_STACK_EMPT";
        case ERR_OPEN_DUMP_FILE:
            return "ERR_OPEN_DUMP_FILE";
        case ERR_CLOSE_DUMP_FILE:
            return "ERR_CLOSE_DUMP_FILE";
        case ERR_INVALID_REG:
            return "ERR_INVALID_REG";
        case ERR_UNKNOWN_CMD:
            return "ERR_UNKNOWN_CMD";
        case ERR_INV_READ_NUM_CMD:
            return "ERR_INV_READ_NUM_CMD";
        case ERR_CANNOT_READ_CMD:
            return "ERR_CANNOT_READ_CMD";
        case ERR_CALLOC_BIN_CODE:
            return "ERR_CALLOC_BIN_CODE";
        case ERR_CLOSE_BIN_FILE:
            return "ERR_CLOSE_BIN_FILE";
        case ERR_BIN_NULL_BEF_DTOR:
            return "ERR_BIN_NULL_BEF_DTOR";
        default:
            return "NEW_ERROR_CODE";
    }
}