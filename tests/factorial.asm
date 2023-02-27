PUSH 20
POP cx

CALL factorial:
OUT
HLT


factorial:
JZ :1

PUSH cx
DEC cx 
JZ :2
PUSH cx
MUL
DEC cx
CALL factorial:
MUL
RET

:1
PUSH 1
RET

:2
PUSH 1
MUL
RET