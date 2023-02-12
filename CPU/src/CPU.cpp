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
        CPU->memmory[ram_index] = ram_value;
    }
    else
    {
        CPU->error_code = ERR_RAM_ADDRESSING;
    }
}

stack_type pop_ram(CPU* CPU, size_t ram_index)
{
    stack_type ram_popped_val = CPU->memmory[ram_index];
}

void cpu_logic(size_t cmd_code, CPU* CPU)
{
    switch (cmd_code)
    {
    case PUSH_ST:
        StackPush(CPU->stack, );
        break;
    case PUSH_REG:
        push_reg(CPU, );
        break;
    case PUSH_RAM:
        push_ram(CPU, );
        break;
    default:
        break;
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
    printf("\n");
}

void get_ram_mem(CPU* CPU)
{
    CPU->memmory = (stack_type*)calloc(RAM_SIZE, sizeof(stack_type));
    if(CPU->memmory == nullptr)
    {
        CPU->error_code = ERR_NULLPTR_RAM;
    }
}

void cpu_ctor(CPU* CPU, Stack* Stack)
{
    StackCtor(Stack, STACK_SIZE);
    CPU->stack = Stack;

    StackOut(CPU->stack);

    memset(CPU->reg, POISON, REG_NUM);
    memset(CPU->r_reg, POISON, R_REG_NUM);
    memset(CPU->call_queue, POISON, CALL_QUEUE_SIZE);
    memset(CPU->jmp_map, POISON, JMP_MAP_SIZE);
    CPU->error_code = CPU_OK;
    get_ram_mem(CPU);
}

void cpu_dtor(CPU* CPU)
{
    StackDtor(CPU->stack);

    memset(CPU->reg, POISON, REG_NUM);
    memset(CPU->r_reg, POISON, R_REG_NUM);
    memset(CPU->call_queue, POISON, CALL_QUEUE_SIZE);
    memset(CPU->jmp_map, POISON, JMP_MAP_SIZE);
    CPU->error_code = POISON;

    for(size_t i = 0; i < RAM_SIZE; i++)
    {
        CPU->memmory[i] = POISON;
    }

    free(CPU->memmory);
    CPU->memmory = nullptr;
}

void jmp_map_realloc(CPU* CPU)
{


}

void call_queue_realloc(CPU* CPU)
{


}

void cpu_work()
{
    while()
    {


    }
}