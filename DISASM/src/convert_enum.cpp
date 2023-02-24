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
        case ERR_OPEN_ASM_FILE:
            return "ERR_OPEN_ASM_FILE";
        case ERR_CLOSE_ASM_FILE:
            return "ERR_CLOSE_ASM_FILE";
        default:
            return "NEW_ERROR_CODE"; 
    }
}

const char* get_cmd_string(size_t cmd_code)
{
    switch(cmd_code)
    {
        case HLT:
            return "HLT";
        case PUSH_ST:
            return "PUSH";
        case PUSH_REG:
            return "PUSH";
        case PUSH_RAM_VAL:
            return "PUSHL";
        case PUSH_RAM_REG:
            return "PUSH";
        case POP_REG:
            return "POP";
        case POP_RAM_VAL:
            return "POP";
        case POP_RAM_REG:
            return "POP";
        case DEC:
            return "DEC";
        case JZ:
            return "JZ";
        case ADD:
            return "ADD";
        case SUB:
            return "SUB";
        case MUL:
            return "MUL";
        case DIV:
            return "DIV";
        case SQRT:
            return "SQRT";
        case OUT:
            return "OUT";
        case RET:
            return "RET";
        case JMP:
            return "JMP";
        case ax:
            return "ax";
        case bx:
            return "bx";
        case cx:
            return "cx";
        case dx:
            return "dx";
        case rax:
            return "rax";
        case rbx:
            return "rbx";
        case rcx:
            return "rcx";
        case CALL:
            return "CALL";
        default:
            return "NEW_CMD"; 
    }
}