#include "CPU.h"

FILE* check_code_file(CPU* CPU)
{
    FILE* code_file = fopen("code_file.bin", "rb"); // Opens an empty file

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
        printf("COde file was openned\n");
        return code_file;
    }
}

void get_commands_in_buf(CPU* CPU)
{
    CPU->
}



void push_reg(CPU* CPU, size_t reg_code, stack_type push_value)
{
    switch (reg_code)
    {
    case ax:
        CPU->reg[0] = push_value;
        break;
    case bx:
        CPU->reg[1] = push_value;
        break;
    case cx:
        CPU->reg[2] = push_value;
        break;
    case dx:
        CPU->reg[3] = push_value;
        break;
    case rax:
        CPU->r_reg[0] = push_value;
        break;
    case rbx:
        CPU->r_reg[1] = push_value;
        break;
    case rcx:
        CPU->r_reg[2] = push_value;
        break;
    default:
        break;
    }
}

stack_type pop_reg(CPU* CPU, size_t reg_code)
{
    stack_type popped_value_reg = 0;

    switch (reg_code)
    {
    case ax:
        popped_value_reg = CPU->reg[0];
        break;
    case bx:
        popped_value_reg = CPU->reg[1];
        break;
    case cx:
        popped_value_reg = CPU->reg[2];
        break;
    case dx:
        popped_value_reg = CPU->reg[3];
        break;
    case rax:
        popped_value_reg = CPU->r_reg[0];
        break;
    case rbx:
        popped_value_reg = CPU->r_reg[1];
        break;
    case rcx:
        popped_value_reg = CPU->r_reg[2];
        break;
    default:
        break;
    }

    return popped_value_reg;
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
    case PUSH_VAL:
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







