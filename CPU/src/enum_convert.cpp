#include "CPU.h"

char* convert_enum_cpu(size_t error_code)
{
    switch(error_code)
    {
        case CPU_OK:
            return "CPU_OK";
            break;
        case ERR_NULLPTR_RAM:
            return "ERR_NULLPTR_RAM";
            break;
        case ERR_RAM_ADDRESSING:  
            return "ERR_RAM_ADDRESSING";
            break;
        case ERR_OPEN_CODE_FILE:  
            return "ERR_OPEN_CODE_FILE";
            break;  
        case ERR_CALL_STACK_FULL:
            return "ERR_CALL_STACK_FULL";
            break;
        case ERR_CALL_STACK_EMPT:
            return "ERR_CALL_STACK_EMPT";
            break;
        default:
            return "NEW_ERROR_CODE";
            break;
    }
}