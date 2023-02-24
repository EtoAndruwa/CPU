#include "disassembler.h"

const char* enum_struct_err_to_string(size_t code) // for struct
{
    switch(code)
    {
        case STRUCT_OK:
            return "STRUCT_OK";
        case ERR_OPEN_BIN_FILE:
            return "ERR_OPEN_BIN_FILE";
        case ERR_CLOSE_BIN_FILE:
            return "ERR_CLOSE_BIN_FILE";
        case ERR_OPEN_DUMP_FILE:
            return "ERR_OPEN_DUMP_FILE";
        case ERR_CLOSE_DUMP_FILE:
            return "ERR_CLOSE_DUMP_FILE";
        case ERR_CALLOC_BIN_BUF:
            return "ERR_CALLOC_BIN_BUF";
        case ERR_INV_READ_NUM_CMD:
            return "ERR_INV_READ_NUM_CMD";
        case ERR_CANNOT_READ_CMD:
            return "ERR_CANNOT_READ_CMD";
        case ERR_CALLOC_COMMANDS:
            return "ERR_CALLOC_COMMANDS";
        default:
            return "NEW_ERROR_CODE"; 
    }
}