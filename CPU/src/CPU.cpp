#include "CPU.h"

FILE* check_code_file(CPU* CPU)
{
    FILE* code_file = fopen("../ASM/test_code.bin", "rb"); // Opens an empty file

    if(code_file == nullptr)
    {
        CPU->error_code = ERR_OPEN_CODE_FILE;
        printf("ERROR: unable to open file %s.\n", FILE_NAME);
    }
    if(CPU->error_code != CPU_OK)
    {
        cpu_dtor(CPU);
        exit(-1);
    }
    else
    {   
        printf("Code file was openned\n");
        return code_file;
    }
}

void push_reg(CPU* CPU, size_t reg_code) // From reg to stack
{
    switch (reg_code)
    {
    case ax:
        StackPush(CPU->stack, CPU->reg[0]);
        break;
    case bx:
        StackPush(CPU->stack, CPU->reg[1]);
        break;
    case cx:
        StackPush(CPU->stack, CPU->reg[2]);
        break;
    case dx:
        StackPush(CPU->stack, CPU->reg[3]);
        break;
    case rax:
        StackPush(CPU->stack, CPU->r_reg[0]);
        break;
    case rbx:
        StackPush(CPU->stack, CPU->r_reg[1]);
        break;
    case rcx:
        StackPush(CPU->stack, CPU->r_reg[2]);
        break;
    default:
        break;
    }
}

void pop_reg(CPU* CPU, size_t reg_code) // From Stack to reg
{
    switch (reg_code)
    {
    case ax:
        CPU->reg[0] = StackPop(CPU->stack);
        break;
    case bx:
        CPU->reg[1] = StackPop(CPU->stack);
        break;
    case cx:
        CPU->reg[2] = StackPop(CPU->stack);
        break;
    case dx:
        CPU->reg[3] = StackPop(CPU->stack);
        break;
    case rax:
        CPU->r_reg[0] = StackPop(CPU->stack);
        break;
    case rbx:
        CPU->r_reg[1] = StackPop(CPU->stack);
        break;
    case rcx:
        CPU->r_reg[2] = StackPop(CPU->stack);
        break;
    default:
        break;
    }
}

void push_ram(CPU* CPU, size_t ram_index, size_t ram_value)
{
    if((ram_index < RAM_SIZE) && (ram_index >= 0))
    {
        CPU->ram[ram_index] = ram_value;
    }
    else
    {
        CPU->error_code = ERR_RAM_ADDRESSING;
    }
}

stack_type pop_ram(CPU* CPU, size_t ram_index)
{
    stack_type ram_popped_val = CPU->ram[ram_index];
}

void cpu_logic(size_t cmd_code, CPU* CPU, Call_stack* Call_stack)
{
    switch (cmd_code)
    {
    case PUSH_ST: // ok
        StackPush(CPU->stack, (int)CPU->bin_code[CPU->curr_cmd + 1] * MUL_CONST);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        break;
    case PUSH_REG: // ok
        push_reg(CPU, CPU->bin_code[CPU->curr_cmd + 1] * MUL_CONST);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        break;
    case POP_REG: // ok
        pop_reg(CPU, CPU->bin_code[CPU->curr_cmd + 1]);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        break;
    case ADD: // ok
        StackAdd(CPU->stack);
        CPU->curr_cmd++;
        break;
    case MUL: // ok
        StackMul(CPU->stack);
        CPU->curr_cmd++;
        break;
    case OUT: //ok
        StackOut(CPU->stack);
        CPU->curr_cmd++;
        break;
    case DIV: //ok
        StackDiv(CPU->stack);
        CPU->curr_cmd++;
        break;
    case SQRT: //ok
        StackSqrt(CPU->stack);
        CPU->curr_cmd++;
        break;
    case SUB: //ok
        StackSub(CPU->stack);
        CPU->curr_cmd++;
        break;
    case CALL:
        push_ret(CPU, Call_stack, CPU->bin_code[CPU->curr_cmd + 1]);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        break;
    default:
        break;
    }
}

void jmp_ret(CPU* CPU, Call_stack* Call_stack)
{
    if((Call_stack->cur_index >= 0) && (Call_stack->call_stack[Call_stack->cur_index] != POISON_VALUE))
    {   
        CPU->curr_cmd = Call_stack->call_stack[Call_stack->cur_index];
        Call_stack->call_stack[Call_stack->cur_index] = POISON_VALUE;
        Call_stack->cur_index--;
    }
}

void get_cmd_in_buf(CPU* CPU)
{
    FILE* bin_code = check_code_file(CPU);
    fread(CPU->num_bin_cmd, sizeof(char), 1, bin_code);
    CPU->bin_code = (char*)calloc(*CPU->num_bin_cmd, sizeof(char));
    fread(CPU->bin_code, sizeof(char), *CPU->num_bin_cmd, bin_code);

    printf("\nBIN_ARR");
    for(size_t i = 0; i < *CPU->num_bin_cmd; i++)
    {   
        printf(" %d ", CPU->bin_code[i]);
    }
    printf("\n\n");
}

void cpu_work(CPU* CPU, Call_stack* Call_stack)
{
    while(CPU->bin_code[CPU->curr_cmd] != HLT)
    {
        cpu_logic(CPU->bin_code[CPU->curr_cmd], CPU, Call_stack);
        // print_cpu_data(CPU);
    }
}

void push_ret(CPU* CPU, Call_stack* Call_stack, size_t index_to_jmp)
{
    if((Call_stack->cur_index >= 0) && (Call_stack->cur_index < CALL_STACK_SIZE))
    {
        Call_stack->call_stack[Call_stack->cur_index] = CPU->bin_code[index_to_jmp];
        Call_stack->cur_index++;
    }
    else
    {
        CPU->error_code = ERR_CALL_STACK_FULL;
    }
}

