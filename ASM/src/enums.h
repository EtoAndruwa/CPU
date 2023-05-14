#ifndef ENUMS_H
#define ENUMS_H

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#ifdef DEF_ASM_STRUCT_ERR_CODE
/**
 * @brief The enum used in order to determine the type of error connected with files
 */
enum asm_error_codes
{
    STRUCT_OK                 = 0,
    ERR_ASM_CODE_BUF_NULL     = -1,
    ERR_OPEN_ASM_FILE         = -2,
    ERR_OPEN_BIN_FILE         = -3,
    ERR_CLOSE_ASM_FILE        = -4,
    ERR_CLOSE_BIN_FILE        = -5,
    ERR_EMPTY_ASM_FILE        = -6, 
    ERR_OPEN_LOG_FILE         = -7,
    ERR_CLOSE_LOG_FILE        = -8,
    ERR_TO_WRITE_CODE         = -9,
    ERR_TO_CALLOC_TOKS        = -10,
    ERR_TO_CALLOC_ASM_BUF     = -11,
    ERR_READ_TO_ASM_BUF       = -12,
    ERR_TO_CALLOC_BIN_CODES   = -13,
    ERR_TO_REALLOC_TOKS       = -14,
    ERR_OPEN_LISTING          = -15,
    ERR_CLOSE_LISTING         = -16
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
enum token_error_codes
{
    TOKEN_OK                     = 0,  /// \brief Example: 'PUSH 10'
    ERR_INVALID_TOKEN            = -17,  /// \brief Example: 'asdfadfas'
    ERR_TOKEN_WITHOUT_VALUE      = -18,  /// \brief Example: 'POP 10'
    ERR_TOKEN_WITH_VALUE         = -19,  /// \brief Example: 'PUSH ______'
    ERR_NO_FLAG                  = -20,  /// \brief Example: 'JMP _____'
    ERR_INVALID_FLAG             = -21,  /// \brief Example: ':abc'
    ERR_NO_FLAG_TO_JMP           = -22,  
    ERR_INVALID_REG              = -23,   
    ERR_CALLS_NON_EXISTEN_FNC    = -24,  
    ERR_NO_FNC_NAME              = -25,  
    ERR_DOUBLE_DECL_OF_FNC       = -26, 
    ERR_FIRST_DECL_OF_FNC        = -27,

    ERR_INNER_RAM_IF_FLT         = -29,
    ERR_DOUBLE_DECL_OF_FLAG      = -30,
    ERR_FIRST_DECL_OF_FLAG       = -31,
    ERR_INVAL_RAM_ADDRESSING     = -32,
    ERR_TO_CALLOC_INNER_RAM      = -33,
};  
#endif

#ifdef DEF_RET_CODES_ASM
/**
 * @brief The enum codes for function's returns 
 * 
 */
enum return_codes
{
    RETURN_OK,
    INNER_RAM_INVALID,
    INNER_VAL        ,
    INNER_VAL_REG    ,
    INNER_IS_REG     ,
    INNER_IS_NOT_REG ,

    NEXT_TOKEN_CMD   ,
    NEXT_TOKEN_VAL   ,
    NEXT_TOKEN_IS_REG,
    NEXT_TOKEN_NOT_REG,

    ALL_TOKENS_VALID  ,
    SOME_TOKEN_INVALID,

    BRACKETS_OKEY     ,
    BRACKETS_NOT_OKEY ,

    ALL_FUNCS_OK       ,
    SOME_FUNC_NOT_OK   , 

    TOKEN_IS_INT      ,
    TOKEN_IS_FLT      ,
    TOKEN_IS_NOT_INT  ,

    ALL_CALLS_OK      ,
    SOME_CALL_NOT_OKEY,

    ALL_FLAGS_OKEY    ,
    SOME_FLAG_NOT_OK  ,

    ALL_JMPS_OKEY     ,
    SOME_JMP_NOT_OK   ,

    ALL_DIGITS        ,
    NOT_ALL_DIGITS    ,
};
#endif

#ifdef DEF_CMD_ID_CODE
/**
 * @brief The codes of the asm commands
 * 
 */
enum cmd_codes
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
    RET  = 9,

    INP  = 10, // input value into reg
    PRT  = 11, 
    DEC  = 12,
    INC  = 13,

    JMP  = 14, 
    JZ   = 15, // jump if zero X == 0
    JE   = 16, // jump if X == Y
    JG   = 17, // jump if X > Y
    JNE  = 18, // jump if X != Y
    JGE  = 19, // jump if X >= Y


    AX   = 21,
    BX   = 22,
    CX   = 23,
    DX   = 24,
    EX   = 25,
    FX   = 26,
    HX   = 27, 
    IX   = 28,
    CALL = 29,

    PUSH_ST       = PUSH | (1 << 5), 
    PUSH_REG      = PUSH | (1 << 6),
    PUSH_RAM_REG  = PUSH | (3 << 6),
    PUSH_RAM_VAL  = PUSH | (5 << 5),

    POP_RAM_REG   = POP | (3 << 6),
    POP_RAM_VAL   = POP | (5 << 5),
    POP_REG       = POP | (1 << 6),

    PUSH_RAM_V_R_A  = 225, // RAM REG + VAR AX
    POP_RAM_V_R_A   = 226,

    PUSH_RAM_V_R_B  = 229, // RAM REG + VAR BX
    POP_RAM_V_R_B   = 230,

    PUSH_RAM_V_R_C  = 233, // RAM REG + VAR CX
    POP_RAM_V_R_C   = 234,

    PUSH_RAM_V_R_D  = 241, // RAM REG + VAR DX
    POP_RAM_V_R_D   = 242,

    PUSH_RAM_V_R_E  = 237, // RAM REG + VAR EX
    POP_RAM_V_R_E   = 238,

    PUSH_RAM_V_R_F  = 245, // RAM REG + VAR FX
    POP_RAM_V_R_F   = 246,

    PUSH_RAM_V_R_H  = 249, // RAM REG + VAR HX
    POP_RAM_V_R_H   = 250,
    
    PUSH_RAM_V_R_I  = 253, // RAM REG + VAR IX
    POP_RAM_V_R_I   = 254,
};
#endif

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif
