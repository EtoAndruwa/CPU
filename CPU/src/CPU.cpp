#include "CPU.h"

int cpu_ctor(CPU* CPU, Stack* Stack) // CHECKED
{
    int error_code = StackCtor(Stack, STACK_SIZE);
    if(error_code != RETURN_OK)
    {
        ERROR_MESSAGE(stderr, error_code)
        return error_code;
    }

    CPU->stack = Stack;
    CPU->error_code = CPU_OK;
    CPU->bin_code = nullptr;
    CPU->bin_file = nullptr;
    CPU->num_bin_cmd[0] = 0;
    CPU->curr_cmd = 0;

    fill_with_poison(CPU->reg, REG_NUM);

    for(size_t i = 0; i < RAM_SIZE; i++)
    {
        CPU->ram[i] = 'O';
    }
}

void cpu_dtor(CPU* CPU) // CHECKED
{
    dump_cpu(CPU,FUNC_NAME, FUNC_LINE, FUNC_FILE);

    StackDtor(CPU->stack);
    CPU->stack = nullptr;

    fill_with_poison(CPU->reg, REG_NUM);    
    fill_with_poison(CPU->ram, RAM_SIZE);

    free(CPU->bin_code);
    CPU->bin_code = nullptr;

    CPU->bin_file = nullptr;
    CPU->curr_cmd = POISON_VALUE;
    CPU->num_bin_cmd[0] = POISON_VALUE;
    CPU->error_code = POISON_VALUE;
}

void call_stack_ctor_dtor(Call_stack* Call_stack) // CHECKED
{
    fill_with_poison(Call_stack->call_stack, CALL_STACK_SIZE);
    Call_stack->cur_index = POISON_VALUE;
}

void fill_with_poison(stack_type* arr_ptr, size_t size_arr) // CHECKED
{
    for(size_t i = 0; i < size_arr; i++)
    {
        arr_ptr[i] = POISON_VALUE;
    }
}

int check_code_file(CPU* CPU) // CHECKED
{
    FILE* bin_file_ptr = fopen("../ASM/bin_code.bin", "rb"); // Opens an empty file
    if(bin_file_ptr == nullptr)
    {
        ERROR_MESSAGE(stderr, ERR_OPEN_BIN_FILE)
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_OPEN_BIN_FILE);
    }
    CPU->bin_file = bin_file_ptr;
    return RETURN_OK;
}

int cpu_logic(float cmd_code, CPU* CPU, Call_stack* Call_stack) // CHECKED
{
    #define DEF_CMD(name, body) case name: body; break;

    switch((int)cmd_code)
    {
        #include "gen_cmd.h"
        #undef DEF_CMD

        default:
            printf("\nERROR CMD code %f\n", cmd_code);
            printf("ERROR CUR CMD %ld\n", CPU->curr_cmd);
            ERROR_MESSAGE(stderr, ERR_UNKNOWN_CMD)
            return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_UNKNOWN_CMD);
    }

    return RETURN_OK;
}

int get_cmd_in_buf(CPU* CPU) // CHECKED
{
    if(check_code_file(CPU) != RETURN_OK)
    {
        ERROR_MESSAGE(stderr, CPU->error_code)
        return CPU->error_code;
    }
    if(fread(CPU->num_bin_cmd, sizeof(float), 1, CPU->bin_file) != 1)
    {
        ERROR_MESSAGE(stderr, ERR_INV_READ_NUM_CMD)
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_INV_READ_NUM_CMD);
    }
    printf("\nCMD GET: %d\n", (int)CPU->num_bin_cmd[0]);

    CPU->bin_code = (float*)calloc(((int)CPU->num_bin_cmd[0]), sizeof(float));
    if(CPU->bin_code == nullptr)    
    {
        ERROR_MESSAGE(stderr, ERR_CALLOC_BIN_CODE)
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CALLOC_BIN_CODE);
    }

    if(fread(CPU->bin_code, sizeof(float), (int)CPU->num_bin_cmd[0], CPU->bin_file) != (int)(*CPU->num_bin_cmd))
    {
        ERROR_MESSAGE(stderr, ERR_CANNOT_READ_CMD)
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CANNOT_READ_CMD);
    }

    if(fclose(CPU->bin_file) == EOF)
    {
        ERROR_MESSAGE(stderr, ERR_CLOSE_BIN_FILE)
        return safe_exit(CPU, FUNC_NAME, FUNC_LINE, FUNC_FILE, ERR_CLOSE_BIN_FILE);
    }
    CPU->bin_file = nullptr;

    return RETURN_OK;
}

int cpu_work(CPU* CPU, Call_stack* Call_stack) // CHECKED
{
    while((int)CPU->bin_code[CPU->curr_cmd] != HLT)
    {
        printf("CPU->num_bin_cmd %f\n", *CPU->num_bin_cmd);
        printf("BEFORE CPU->cur_cmd %ld\n", CPU->curr_cmd);
        int error_code = cpu_logic(CPU->bin_code[CPU->curr_cmd], CPU, Call_stack);
        printf("AFTER CPU->cur_cmd %ld\n\n", CPU->curr_cmd);
        if(error_code != RETURN_OK)
        {   
            ERROR_MESSAGE(stderr, error_code)
            return error_code;
        }
    }
    return RETURN_OK;
}

int safe_exit(CPU* CPU, const char* func_name, int func_line, const char* func_file, int error_code) // CHECKED
{
    CPU->error_code = error_code;
    if(dump_cpu(CPU, func_name, func_line, func_file) != 0)
    {
        ERROR_MESSAGE(stderr, CPU->error_code)
        return CPU->error_code;
    }
    cpu_dtor(CPU);
    return CPU->error_code;
}

