PUSH 4
PUSH -1
PUSH -5
OUT
POP cx
POP bx
POP ax
OUT
CALL GET_DISCR:
CALL GET_X1:
CALL GET_X2:
HLT


GET_DISCR:
PUSH bx
PUSH bx 
OUT
MUL
OUT
PUSH 4
PUSH ax
PUSH cx
OUT
MUL
MUL
SUB
OUT
POP dx
RET


GET_X1:
PUSH bx
PUSH -1
MUL
PUSH dx
SQRT
SUB
PUSH 2
PUSH ax
MUL
DIV
POP rax
RET

GET_X2:
PUSH bx
PUSH -1
MUL
PUSH dx
SQRT
ADD
PUSH 2
PUSH ax
MUL
DIV
POP rbx
RET




