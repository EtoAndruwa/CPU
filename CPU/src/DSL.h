#ifndef DSL_H
#define DSL_H

#define ADD()             StackAdd(CPU->stack); CPU->curr_cmd++                               
#define MUL()             StackMul(CPU->stack); CPU->curr_cmd++
#define OUT()             StackOut(CPU->stack); CPU->curr_cmd++
#define DIV()             StackDiv(CPU->stack); CPU->curr_cmd++
#define SQRT()            StackSqrt(CPU->stack); CPU->curr_cmd++
#define SUB()             StackSub(CPU->stack); CPU->curr_cmd++
#define PUSH_ST()         StackPush(CPU->stack, CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define PUSH_REG()        push_reg(CPU, CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define POP_REG()         pop_reg(CPU, CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define CALL()            push_ret(CPU, Call_stack, CPU->curr_cmd + 2); CPU->curr_cmd = CPU->bin_code[CPU->curr_cmd + 1]
#define RET()             jmp_ret(CPU, Call_stack)


#define JMP()             jmp_flag(CPU, CPU->curr_cmd + 1)
#define JZ()              jmp_flag_jz(CPU, CPU->curr_cmd + 1)
#define JE()              jmp_flag_je(CPU, CPU->curr_cmd + 1)
#define JG()              jmp_flag_jg(CPU, CPU->curr_cmd + 1)
#define JNE()             jmp_flag_jne(CPU, CPU->curr_cmd + 1)
#define JGE()             jmp_flag_jge(CPU, CPU->curr_cmd + 1)
#define INP()             inp(CPU, CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2

#define DEC()             dec(CPU, CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define INC()             inc(CPU, CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2

#define PUSH_RAM_REG()    push_ram_reg(CPU, CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define PUSH_RAM_VAL()    push_ram_val(CPU, CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define POP_RAM_REG()     pop_ram_reg(CPU, CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define POP_RAM_VAL()     pop_ram_val(CPU, CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2

#define PUSH_RAM_V_R_A()  push_ram_reg_val(CPU, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define PUSH_RAM_V_R_B()  push_ram_reg_val(CPU, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define PUSH_RAM_V_R_C()  push_ram_reg_val(CPU, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define PUSH_RAM_V_R_D()  push_ram_reg_val(CPU, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define PUSH_RAM_V_R_E()  push_ram_reg_val(CPU, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define PUSH_RAM_V_R_F()  push_ram_reg_val(CPU, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define PUSH_RAM_V_R_H()  push_ram_reg_val(CPU, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define PUSH_RAM_V_R_I()  push_ram_reg_val(CPU, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2

#define POP_RAM_V_R_A()   pop_ram_reg_val(CPU, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define POP_RAM_V_R_B()   pop_ram_reg_val(CPU, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define POP_RAM_V_R_C()   pop_ram_reg_val(CPU, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define POP_RAM_V_R_D()   pop_ram_reg_val(CPU, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define POP_RAM_V_R_E()   pop_ram_reg_val(CPU, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define POP_RAM_V_R_F()   pop_ram_reg_val(CPU, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define POP_RAM_V_R_H()   pop_ram_reg_val(CPU, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2
#define POP_RAM_V_R_I()   pop_ram_reg_val(CPU, CPU->bin_code[CPU->curr_cmd], CPU->bin_code[CPU->curr_cmd + 1]); CPU->curr_cmd += 2

#endif
