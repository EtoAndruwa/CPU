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

void push_ram_val(CPU* CPU, size_t ram_index)
{
    if((ram_index < RAM_SIZE) && (ram_index >= 0))
    {
        StackPush(CPU->stack, CPU->ram[ram_index]);
    }
    else
    {
        CPU->error_code = ERR_RAM_ADDRESSING;
    }
}

void pop_ram_val(CPU* CPU, size_t ram_index)
{
    if((ram_index < RAM_SIZE) && (ram_index >= 0))
    {
        CPU->ram[ram_index] = StackPop(CPU->stack);
    }
    else
    {
        CPU->error_code = ERR_RAM_ADDRESSING;
    }
}

void push_ram_reg(CPU* CPU, size_t reg_id)
{
    switch (reg_id)
    {
    case ax:
        StackPush(CPU->stack, CPU->ram[CPU->reg[0] / 100]);
        break;
    case bx:
        StackPush(CPU->stack, CPU->ram[CPU->reg[1] / 100]);
        break;
    case cx:
        StackPush(CPU->stack, CPU->ram[CPU->reg[2] / 100]);
        break;
    case dx:
        StackPush(CPU->stack, CPU->ram[CPU->reg[3] / 100]);
        break; 
    case rax:
        StackPush(CPU->stack, CPU->ram[CPU->r_reg[0] / 100]);
        break;
    case rbx:
        StackPush(CPU->stack, CPU->ram[CPU->r_reg[1] / 100]);
        break;
    case rcx:
        StackPush(CPU->stack, CPU->ram[CPU->r_reg[2] / 100]);
        break;
    default:
        break;
    }
}

void pop_ram_reg(CPU* CPU, size_t reg_id)
{
    switch (reg_id)
    {
    case ax:
        if((CPU->reg[0] / 100) >= RAM_SIZE)
        {
            CPU->error_code = ERR_RAM_ADDRESSING;
        }
        else
        {
            CPU->ram[CPU->reg[0] / 100] = StackPop(CPU->stack);;
        }
        break;
    case bx:
        if((CPU->reg[1] / 100) >= RAM_SIZE)
        {
            CPU->error_code = ERR_RAM_ADDRESSING;
        }
        else
        {
            CPU->ram[CPU->reg[1] / 100] = StackPop(CPU->stack);;
        }
        break;
    case cx:
        if((CPU->reg[2] / 100) >= RAM_SIZE)
        {
            CPU->error_code = ERR_RAM_ADDRESSING;
        }
        else
        {
            CPU->ram[CPU->reg[2] / 100] = StackPop(CPU->stack);;
        }
        break;
    case dx:
        if((CPU->reg[3] / 100) >= RAM_SIZE)
        {
            CPU->error_code = ERR_RAM_ADDRESSING;
        }
        else
        {
            CPU->ram[CPU->reg[3] / 100] = StackPop(CPU->stack);;
        }
        break;
    case rax:
        if((CPU->r_reg[0] / 100) >= RAM_SIZE)
        {
            CPU->error_code = ERR_RAM_ADDRESSING;
        }
        else
        {
            CPU->ram[CPU->r_reg[0] / 100] = StackPop(CPU->stack);;
        }
        break;
    case rbx:
        if((CPU->r_reg[1] / 100) >= RAM_SIZE)
        {
            CPU->error_code = ERR_RAM_ADDRESSING;
        }
        else
        {
            CPU->ram[CPU->r_reg[1] / 100] = StackPop(CPU->stack);;
        }
        break;
    case rcx:
        if((CPU->r_reg[2] / 100) >= RAM_SIZE)
        {
            CPU->error_code = ERR_RAM_ADDRESSING;
        }
        else
        {
            CPU->ram[CPU->r_reg[2] / 100] = StackPop(CPU->stack);;
        }
        break;
    default:
        break;
    }
}

void cpu_logic(size_t cmd_code, CPU* CPU, Call_stack* Call_stack)
{
    switch (cmd_code)
    {
    case PUSH_ST: // ok
        StackPush(CPU->stack, (int)CPU->bin_code[CPU->curr_cmd + 1] * MUL_CONST);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        printf("curr_cmd: %ld\n", CPU->curr_cmd);
        break;
    case PUSH_REG: // ok
        push_reg(CPU, CPU->bin_code[CPU->curr_cmd + 1] * MUL_CONST);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        printf("curr_cmd: %ld\n", CPU->curr_cmd);
        break;
    case POP_REG: // ok
        pop_reg(CPU, CPU->bin_code[CPU->curr_cmd + 1]);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        printf("curr_cmd: %ld\n", CPU->curr_cmd);
        break;
    case ADD: // ok
        StackAdd(CPU->stack);
        CPU->curr_cmd++;
        printf("curr_cmd: %ld\n", CPU->curr_cmd);
        break;
    case MUL: // ok
        StackMul(CPU->stack);
        CPU->curr_cmd++;
        printf("curr_cmd: %ld\n", CPU->curr_cmd);
        break;
    case OUT: //ok
        StackOut(CPU->stack);
        CPU->curr_cmd++;
        printf("curr_cmd: %ld\n", CPU->curr_cmd);
        break;
    case DIV: //ok
        StackDiv(CPU->stack);
        CPU->curr_cmd++;
        printf("curr_cmd: %ld\n", CPU->curr_cmd);
        break;
    case SQRT: //ok
        StackSqrt(CPU->stack);
        CPU->curr_cmd++;
        printf("curr_cmd: %ld\n", CPU->curr_cmd);
        break;
    case SUB: //ok
        StackSub(CPU->stack);
        CPU->curr_cmd++;
        printf("curr_cmd: %ld\n", CPU->curr_cmd);
        break;
    case CALL: //ok
        push_ret(CPU, Call_stack, CPU->curr_cmd + 2);
        CPU->curr_cmd = CPU->bin_code[CPU->curr_cmd + 1];
        printf("curr_cmd: %ld\n", CPU->curr_cmd);
        break;
    case RET:
        jmp_ret(CPU, Call_stack);
        printf("curr_cmd: %ld\n", CPU->curr_cmd);
        break;
    case JMP:
        jmp_flag(CPU, CPU->curr_cmd + 1);
        printf("curr_cmd: %ld\n", CPU->curr_cmd);
        break;
    case PUSH_RAM_REG:
        push_ram_reg(CPU, CPU->bin_code[CPU->curr_cmd + 1]);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        printf("curr_cmd: %ld\n", CPU->curr_cmd);
        break;
    case PUSH_RAM_VAL:
        push_ram_val(CPU, CPU->bin_code[CPU->curr_cmd + 1]);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        printf("curr_cmd: %ld\n", CPU->curr_cmd);
        break;
    case POP_RAM_REG:
        pop_ram_reg(CPU, CPU->bin_code[CPU->curr_cmd + 1]);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        printf("curr_cmd: %ld\n", CPU->curr_cmd);
        break;
    case POP_RAM_VAL:
        pop_ram_val(CPU, CPU->bin_code[CPU->curr_cmd + 1]);
        CPU->curr_cmd = CPU->curr_cmd + 2;
        printf("curr_cmd: %ld\n", CPU->curr_cmd);
        break;
    default:
        break;
    }
}

void jmp_ret(CPU* CPU, Call_stack* Call_stack)
{
    if((Call_stack->cur_index == 0) && (Call_stack->call_stack[Call_stack->cur_index] != POISON_VALUE))
    {   
        CPU->curr_cmd = Call_stack->call_stack[Call_stack->cur_index];
        Call_stack->call_stack[Call_stack->cur_index] = POISON_VALUE;
    }
    else if(Call_stack->cur_index > 0)
    {   
        Call_stack->cur_index--;
        CPU->curr_cmd = Call_stack->call_stack[Call_stack->cur_index];
        Call_stack->call_stack[Call_stack->cur_index] = POISON_VALUE;    
    }
    else
    {
        CPU->error_code = ERR_CALL_STACK_EMPT;
    }
}

void get_cmd_in_buf(CPU* CPU)
{
    FILE* bin_code = check_code_file(CPU);
    fread(CPU->num_bin_cmd, sizeof(int), 1, bin_code);
    CPU->bin_code = (int*)calloc(*CPU->num_bin_cmd, sizeof(int));
    fread(CPU->bin_code, sizeof(int), *CPU->num_bin_cmd, bin_code);
    fclose(bin_code);

    // printf("\nBIN_ARR");
    // for(size_t i = 0; i < *CPU->num_bin_cmd; i++)
    // {   
    //     printf(" %d ", CPU->bin_code[i]);
    // }
    // printf("\n\n");
}

void cpu_work(CPU* CPU, Call_stack* Call_stack)
{
    while(CPU->bin_code[CPU->curr_cmd] != HLT)
    {
        cpu_logic(CPU->bin_code[CPU->curr_cmd], CPU, Call_stack);
    }
}

void push_ret(CPU* CPU, Call_stack* Call_stack, size_t index_to_jmp) //ok
{
    if((Call_stack->cur_index >= 0) && (Call_stack->cur_index < CALL_STACK_SIZE))
    {
        Call_stack->call_stack[Call_stack->cur_index] = index_to_jmp;
        //print_call_stack(Call_stack);
    }
    else
    {
        CPU->error_code = ERR_CALL_STACK_FULL;
    }
}

void jmp_flag(CPU* CPU, size_t index_to_jmp)
{
    CPU->curr_cmd = CPU->bin_code[index_to_jmp];
}   
