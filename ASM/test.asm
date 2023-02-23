PUSH 88
POP ax

CALL PRINT_TOP:

CALL PRINT_BOT:

HLT

PRINT_2:
    PUSH ax
    POP [bx]

    CALL PRINT_X:
    RET

PRINT_4:    
    PUSH ax
    POP [bx]

    CALL PRINT_X:
    CALL PRINT_X:
    CALL PRINT_X:
    RET

PRINT_6:
    PUSH ax
    POP [bx]

    CALL PRINT_X:
    CALL PRINT_X:
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

PRINT_10:
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

PRINT_14:
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

PRINT_20:
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
    PUSH 9
    POP bx
    CALL PRINT_2:

    PUSH 28
    POP bx
    CALL PRINT_4:

    PUSH 47
    POP bx
    CALL PRINT_6:

    PUSH 66
    POP bx
    CALL PRINT_8:

    PUSH 85
    POP bx
    CALL PRINT_10:

    PUSH 104
    POP bx
    CALL PRINT_12:

    PUSH 123
    POP bx
    CALL PRINT_14:

    PUSH 142
    POP bx
    CALL PRINT_16:

    PUSH 161
    POP bx
    CALL PRINT_18:

    PUSH 180
    POP bx
    CALL PRINT_20:

    RET

PRINT_BOT:
    PUSH 200
    POP bx
    CALL PRINT_20:

    PUSH 221
    POP bx
    CALL PRINT_18:

    PUSH 242
    POP bx
    CALL PRINT_16:

    PUSH 263
    POP bx
    CALL PRINT_14:

    PUSH 284
    POP bx
    CALL PRINT_12:

    PUSH 305
    POP bx
    CALL PRINT_10:

    PUSH 326
    POP bx
    CALL PRINT_8:

    PUSH 347
    POP bx
    CALL PRINT_6:

    PUSH 368
    POP bx
    CALL PRINT_4:

    PUSH 389
    POP bx
    CALL PRINT_2:

    RET