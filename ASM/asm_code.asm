PUSH 88
POP ax

CALL PRINT_TOP:
CALL PRINT_BOT:

HLT

PRINT_4:    
    PUSH ax
    POP [bx]

    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:
    RET

PRINT_8:
    PUSH ax
    POP [bx]

    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:
    RET

PRINT_12:
    PUSH ax
    POP [bx]

    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:    
    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X: 
    CALL PRINT_X:
    CALL PRINT_X:
    RET

PRINT_16:
    PUSH ax
    POP [bx]

    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:    
    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X: 
    CALL PRINT_X:
    CALL PRINT_X: 
    CALL PRINT_X:
    CALL PRINT_X: 
    CALL PRINT_X:
    CALL PRINT_X:
    RET

PRINT_18:
    PUSH ax
    POP [bx]

    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:    
    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X: 
    CALL PRINT_X:
    CALL PRINT_X: 
    CALL PRINT_X:
    CALL PRINT_X: 
    CALL PRINT_X:
    CALL PRINT_X: 
    CALL PRINT_X:
    CALL PRINT_X: 
    CALL PRINT_X:
    RET

PRINT_X:
    PUSH 1
    PUSH bx
    ADD
    POP bx
    PUSH ax
    POP [bx]
    RET

PRINT_TOP:

    PUSH 28
    POP bx
    CALL PRINT_4:

    PUSH 46
    POP bx
    CALL PRINT_8:

    PUSH 66
    POP bx
    CALL PRINT_8:

    PUSH 84
    POP bx
    CALL PRINT_12:

    PUSH 104
    POP bx
    CALL PRINT_12:

    PUSH 122
    POP bx
    CALL PRINT_16:

    PUSH 142
    POP bx
    CALL PRINT_16:

    PUSH 161
    POP bx
    CALL PRINT_18:

    PUSH 181
    POP bx
    CALL PRINT_18:

    RET

PRINT_BOT:
    PUSH 201
    POP bx
    CALL PRINT_18:

    PUSH 221
    POP bx
    CALL PRINT_18:

    PUSH 242
    POP bx
    CALL PRINT_16:

    PUSH 262
    POP bx
    CALL PRINT_16:

    PUSH 284
    POP bx
    CALL PRINT_12:

    PUSH 304
    POP bx
    CALL PRINT_12:

    PUSH 326
    POP bx
    CALL PRINT_8:

    PUSH 346
    POP bx
    CALL PRINT_8:

    PUSH 368
    POP bx
    CALL PRINT_4:

    RET