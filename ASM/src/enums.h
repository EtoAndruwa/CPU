#ifndef ENUMS_H
#define ENUMS_H

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#ifdef DEF_ASM_STRUCT_ERR_CODE
/**
 * @brief The enum used in order to determine the type of error connected with files
 */
enum asm_errors 
{
    STRUCT_OK                 = 0,
    ERR_ASM_CODE_BUF_NULL     = 1,
    ERR_OPEN_ASM_FILE         = 2,
    ERR_OPEN_BIN_FILE         = 3,
    ERR_CLOSE_ASM_FILE        = 4,
    ERR_CLOSE_BIN_FILE        = 5,
    ERR_EMPTY_ASM_FILE        = 6, 
    ERR_OPEN_LOG_FILE         = 7,
    ERR_CLOSE_LOG_FILE        = 8,
    ERR_TO_WRITE_CODE         = 9,
    ERR_TO_CALLOC_TOKS        = 10,
    ERR_TO_CALLOC_ASM_BUF     = 11,
    ERR_READ_TO_ASM_BUF       = 12,
    ERR_TO_CALLOC_BIN_CODES   = 13,
    ERR_TO_REALLOC_TOKS       = 14,
    ERR_OPEN_LISTING          = 15,
    ERR_CLOSE_LISTING         = 16
};
#endif

#ifdef DEF_TOKEN_TYPE
/**
 * @brief The enum used in order to determine the type of token (command, register or value)
 */
enum type
{
    EMPTY = 0, /// \brief for initializing
    CMD   = 1, /// \brief 'command'
    REG   = 2, /// \brief 'register'
    VAL   = 3, /// \brief 'value' 
    FLG   = 4, /// \brief 'flag'
    FNC   = 5, /// \brief 'function'
};
#endif

#ifdef DEF_TOKEN_ERR_CODE
/**
 * @brief The enum is used in order to determine the error connected with token
 */
enum token_error_code 
{
    TOKEN_OK                     = 0,  /// \brief Example: 'PUSH 10'
    ERR_INVALID_TOKEN            = 1,  /// \brief Example: 'asdfadfas'
    ERR_TOKEN_WITHOUT_VALUE      = 2,  /// \brief Example: 'POP 10'
    ERR_TOKEN_WITH_VALUE         = 3,  /// \brief Example: 'PUSH ______'
    ERR_NO_FLAG                  = 4,  /// \brief Example: 'JMP _____'
    ERR_INVALID_FLAG             = 5,  /// \brief Example: ':abc'
    ERR_NO_FLAG_TO_JMP           = 6,  
    ERR_INVALID_REG              = 7,   
    ERR_CALLS_NON_EXISTEN_FNC    = 8,  
    ERR_NO_FNC_NAME              = 9,  
    ERR_DOUBLE_DECL_OF_FNC       = 10, 
    ERR_FIRST_DECL_OF_FNC        = 11,
    ERR_TO_CHECK_INNER_RAM       = 12,
    ERR_DOUBLE_DECL_OF_FLAG      = 13,
    ERR_FIRST_DECL_OF_FLAG       = 14,
    ERR_INVAL_RAM_ADDRESSING     = 15,
};  
#endif

#ifdef DEF_RET_CODES_ASM
/**
 * @brief The enum codes for function's returns 
 * 
 */
enum ret_codes
{
    INNER_RAM_INVALID  = 0,
    INNER_REG          = 1,
    INNER_VAL          = 2,
    INNER_VAL_REG      = 3,
    NEXT_TOKEN_CMD     = 4,
    NEXT_TOKEN_VAL     = 5,
    ALL_TOKENS_VALID   = 6,
    SOME_TOKEN_INVALID = 7,
    BRACKETS_OKEY      = 8,
    BRACKETS_NOT_OKEY  = 9,
    ALL_FUNCS_OK       = 10,
    SOME_FUNC_NOT_OK   = 11, 
    TOKEN_IS_INT       = 12,
    TOKEN_IS_NOT_INT   = 13,
    ALL_CALLS_OK       = 14,
    SOME_CALL_NOT_OKEY = 15,
    ALL_FLAGS_OKEY     = 16,
    SOME_FLAG_NOT_OK   = 17,
    NEXT_TOKEN_IS_REG  = 18,
    NEXT_TOKEN_NOT_REG = 19,
    ALL_JMPS_OKEY      = 20,
    SOME_JMP_NOT_OK    = 21,
    INNER_NOT_REG      = 22,
    ALL_DIGITS         = 23,
    NOT_ALL_DIGITS     = 24
};
#endif

#ifdef DEF_CMD_ID_CODE
/**
 * @brief The codes of the asm commands
 * 
 */
enum cmd
{  
    HLT  = 0,
    PUSH = 1,
    POP  = 2,
    ADD  = 3, 
    SUB  = 4, 
    MUL  = 5, 
    DIV  = 6, 
    SQRT = 7, 
    OUT  = 8, 
    RET  = 10,
    JMP  = 11, 
    DEC  = 12,
    JZ   = 13,
    AX   = 21,
    BX   = 22,
    CX   = 23,
    DX   = 24,
    CALL = 30,
    PUSH_ST       = PUSH | (1 << 5), 
    PUSH_REG      = PUSH | (1 << 6),
    PUSH_RAM_REG  = PUSH | (3 << 6),
    PUSH_RAM_VAL  = PUSH | (5 << 5),
    PUSH_RAM_V_R_A  = 225,
    POP_RAM_V_R_A   = 226,
    PUSH_RAM_V_R_B  = 229,
    POP_RAM_V_R_B   = 230,
    PUSH_RAM_V_R_C  = 233,
    POP_RAM_V_R_C   = 234,
    PUSH_RAM_V_R_D  = 241,
    POP_RAM_V_R_D   = 242,
    POP_RAM_REG   = POP | (3 << 6),
    POP_RAM_VAL   = POP | (5 << 5),
    POP_REG       = POP | (1 << 6),
};
#endif

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif
