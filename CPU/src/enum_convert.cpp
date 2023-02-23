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
        case ERR_CLODE_DUMP_FILE:
            return "ERR_CLODE_DUMP_FILE";
        case ERR_INVALID_REG:
            return "ERR_INVALID_REG";
        case ERR_UNKNOWN_CMD:
            return "ERR_UNKNOWN_CMD";
        default:
            return "NEW_ERROR_CODE";
    }
}