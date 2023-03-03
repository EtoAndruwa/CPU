#include "assembler.h"
#include "def_cmd.h"


size_t file_openning_check(asm_struct* assembly_struct) 
{   
    FILE* asm_code = fopen(FILE_ASM_NAME, "rb"); // Opens the file with text
    FILE* bin_code = fopen(FILE_CODE_NAME, "wb"); // Opens an empty file

    if(asm_code == nullptr)
    {
        assembly_struct->err_code = ERR_OPEN_ASM_FILE;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        return assembly_struct->err_code;
    }
    if(bin_code == nullptr)
    {   
        assembly_struct->err_code = ERR_OPEN_BIN_FILE;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        return assembly_struct->err_code;
    }
    else
    {  
        assembly_struct->asm_file = asm_code;
        assembly_struct->translated_file = bin_code;
    }
}

void get_token_value(asm_struct* assembly_struct, size_t cur_tok_chk) 
{
    if((strcmp(assembly_struct->toks[cur_tok_chk].text, "ax") == 0) || (strcmp(assembly_struct->toks[cur_tok_chk].text, "bx") == 0) ||  
        (strcmp(assembly_struct->toks[cur_tok_chk].text, "cx") == 0) || (strcmp(assembly_struct->toks[cur_tok_chk].text, "dx") == 0) ||
            (strcmp(assembly_struct->toks[cur_tok_chk].text, "rax") == 0) || (strcmp(assembly_struct->toks[cur_tok_chk].text, "rbx") == 0) || 
                (strcmp(assembly_struct->toks[cur_tok_chk].text, "rcx") == 0)) 
        DEF_CMD_REGS(assembly_struct, cur_tok_chk)
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "PUSH") == 0)
    {
        if(((assembly_struct->num_toks - 1) > cur_tok_chk) && (check_next_token(assembly_struct, cur_tok_chk) == NEXT_TOKEN_VAL))                                                                                                                           
        {                                                                                                                                                                        
            assembly_struct->toks[cur_tok_chk].value = PUSH | (1 << 5);                                                                                                                         
            assembly_struct->toks[cur_tok_chk].type  = cmd;                                                                                                                       
            strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "OK");                                                                                                                         
            assembly_struct->cur_tok_chk++;                                                                                                                                      
        }                                                                                                                                                                        
        else                                                                                                                                                                        
            DEF_CMD_PUSH_POP(PUSH)
    }
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "POP") == 0)    
        DEF_CMD_PUSH_POP(POP)
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "ADD") == 0)  
        DEF_CMD_OTHERS(ADD)
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "SUB") == 0)  
        DEF_CMD_OTHERS(SUB)
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "MUL") == 0)  
        DEF_CMD_OTHERS(MUL)
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "DIV") == 0)   
        DEF_CMD_OTHERS(DIV)
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "SQRT") == 0)       
        DEF_CMD_OTHERS(SQRT)
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "HLT") == 0)  
        DEF_CMD_OTHERS(HLT)
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "OUT") == 0)  
        DEF_CMD_OTHERS(OUT)
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "RET") == 0)
        DEF_CMD_OTHERS(RET)
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "JMP") == 0)
        DEF_CMD_JMP(JMP)       
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "JZ") == 0)
        DEF_CMD_JMP(JZ)
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "DEC") == 0)
        DEF_CMD_DEC
    else if(strcmp(assembly_struct->toks[cur_tok_chk].text, "CALL") == 0)
        DEF_CMD_CALL
    else if(check_num_int(assembly_struct->toks[cur_tok_chk].text) == TOKEN_IS_INT)
        DEF_CMD_VAL
    else if((assembly_struct->toks[cur_tok_chk].text[0] == ':') && (strlen(assembly_struct->toks[cur_tok_chk].text) > 1))
        DEF_CMD_FLAG
    else if((assembly_struct->toks[cur_tok_chk].text[(strlen(assembly_struct->toks[cur_tok_chk].text) - 1)] == ':') && (strlen(assembly_struct->toks[cur_tok_chk].text) > 1))
        DEF_CMD_FUNC
    else
    {
        strcpy((char*)assembly_struct->toks[cur_tok_chk].status, "--");
        assembly_struct->toks[cur_tok_chk].error_code = ERR_INVALID_TOKEN;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        assembly_struct->cur_tok_chk++;
    }
}

size_t get_commands_into_buf(asm_struct* assembly_struct) 
{
    rewind(assembly_struct->asm_file); // Puts the pointer inside the file to the start of the file 
    assembly_struct->asm_buf = (char*)calloc(1, sizeof(char) * (assembly_struct->size + 1)); // Allocates enough memmory for the buffer of chars  

    if(assembly_struct->asm_buf == nullptr)
    {
        assembly_struct->err_code = ERR_TO_CALLOC_ASM_BUF;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        dtor_asm(assembly_struct);
        return assembly_struct->err_code;
    }

    int num_read = fread(assembly_struct->asm_buf, sizeof(char), assembly_struct->size, assembly_struct->asm_file); // Reads the file into the buffer

    if((num_read <= 0) && (num_read > assembly_struct->size))
    {
        assembly_struct->err_code = ERR_READ_TO_ASM_BUF;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        dtor_asm(assembly_struct);
        return assembly_struct->err_code;       
    }
    assembly_struct->asm_buf[assembly_struct->size] = '\0'; // Makes form the file null-terminated string
    rewind(assembly_struct->asm_file); // Puts the pointer inside the file to the start of the file
}

size_t get_size_asm(asm_struct* assembly_struct) 
{
    rewind(assembly_struct->asm_file); // Puts the pointer inside the file to the start of the file 

    fseek(assembly_struct->asm_file, 0, SEEK_END); // Puts the pointer inside the file to the end of it
    assembly_struct->size = ftell(assembly_struct->asm_file); // Get the size of the file with '\r'!

    if(assembly_struct->size == 0) 
    {
        assembly_struct->err_code = ERR_EMPTY_ASM_FILE; 
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        dtor_asm(assembly_struct);  
        return assembly_struct->err_code;
    } 

    rewind(assembly_struct->asm_file);
}

size_t dtor_asm(asm_struct* assembly_struct) 
{

    for(size_t i = 0 ; i < assembly_struct->num_toks; i++)
    {
        assembly_struct->toks[i].error_code = TOKEN_OK;
        assembly_struct->toks[i].new_index  = -1;
        strcpy((char*)assembly_struct->toks[i].status, "---");
        assembly_struct->toks[i].text  = nullptr;
        assembly_struct->toks[i].type  = cmd;
        assembly_struct->toks[i].value = 0;
    }

    free(assembly_struct->bin_codes);
    assembly_struct->bin_codes = nullptr;

    free(assembly_struct->asm_buf);
    assembly_struct->asm_buf = nullptr;

    free(assembly_struct->toks);
    assembly_struct->toks = nullptr;

    assembly_struct->err_code    = 0;
    assembly_struct->size        = 0;
    assembly_struct->cur_tok_chk = 0;

    if(fclose(assembly_struct->asm_file) == EOF)
    {
        assembly_struct->err_code = ERR_CLOSE_ASM_FILE;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        return assembly_struct->err_code;
    }
    if(fclose(assembly_struct->translated_file) == EOF)
    {   
        assembly_struct->err_code = ERR_CLOSE_BIN_FILE;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        return assembly_struct->err_code;
    }
}

size_t get_tokens(asm_struct* assembly_struct) 
{
    char* token = strtok(assembly_struct->asm_buf," \n\r");
    assembly_struct->toks = (tokens*)calloc(1, sizeof(tokens));
    
    if(assembly_struct->toks == nullptr)
    {
        assembly_struct->err_code = ERR_TO_CALLOC_TOKS;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        dtor_asm(assembly_struct);
        return assembly_struct->err_code;
    }

    size_t toks_num = 0;
    while (token != NULL)                        
    {   
        realloc_toks(assembly_struct, toks_num); // Reallocs the struct with tokens

        if(assembly_struct->err_code != STRUCT_OK)
        {
            return assembly_struct->err_code;
        }

        assembly_struct->toks[toks_num].text = token; // Adds the new token to the array
        token = strtok(NULL, " \n\r");
        toks_num++;
    }
}

size_t realloc_toks(asm_struct* assembly_struct, size_t i) 
{
    if(assembly_struct->num_toks == i)
    {
        assembly_struct->num_toks++;
        assembly_struct->toks = (tokens*)realloc(assembly_struct->toks, assembly_struct->num_toks * sizeof(tokens)); // The pointer to the array of structs

        if(assembly_struct->toks == nullptr)
        {
            assembly_struct->err_code = ERR_TO_REALLOC_TOKS;
            dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
            dtor_asm(assembly_struct);
            return assembly_struct->err_code;
        }
    }
}

void translate_to_asm(asm_struct* assembly_struct)  
{
    assembly_struct->cur_tok_chk = 0;

    while(assembly_struct->cur_tok_chk < assembly_struct->num_toks)
    {
        get_token_value(assembly_struct, assembly_struct->cur_tok_chk);
    }
}

size_t write_asm(asm_struct* assembly_struct) 
{   
    put_new_index(assembly_struct); // Gets new indexes of all tokens

    if(check_all_valid(assembly_struct) == ALL_TOKENS_VALID && check_flags(assembly_struct) == ALL_JMPS_OKEY && check_func(assembly_struct) == ALL_CALLS_OK && check_fnc_declaration(assembly_struct) == ALL_FUNCS_OK && 
        check_flag_declaration(assembly_struct) == ALL_FLAGS_OKEY) // Rules
    {        
        if(get_arr_bin_codes(assembly_struct) != STRUCT_OK)
        {
            return assembly_struct->err_code;
        }   

        size_t new_num_cmd = get_new_num_toks(assembly_struct);

        int tokens_wrote = fwrite(assembly_struct->bin_codes, sizeof(int), new_num_cmd + 1, assembly_struct->translated_file);

        if(tokens_wrote != (new_num_cmd + 1))
        {
            assembly_struct->err_code = ERR_TO_WRITE_CODE;
            dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
            dtor_asm(assembly_struct);
            return assembly_struct->err_code;
        }
    }
    else
    {
        assembly_struct->err_code = ERR_TO_WRITE_CODE;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        dtor_asm(assembly_struct);
        return assembly_struct->err_code;
    }
}

size_t get_arr_bin_codes(asm_struct* assembly_struct)
{
    size_t new_num_cmd = get_new_num_toks(assembly_struct);
    assembly_struct->bin_codes = (int*)calloc(new_num_cmd + 1, sizeof(int)); // Creates buffer for number of commands without jmp and func

    if(assembly_struct->bin_codes == nullptr)
    {   
        assembly_struct->err_code = ERR_TO_CALLOC_BIN_CODES;
        dump_asm(assembly_struct, FUNC_NAME, FUNC_LINE, FUNC_FILE);
        dtor_asm(assembly_struct);
        return assembly_struct->err_code;
    }

    assembly_struct->bin_codes[0] = (int)(new_num_cmd); // New number of toks
    size_t j = 1;

    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {   
        if(assembly_struct->toks[i].new_index != -1)
        {   
            assembly_struct->bin_codes[j] = assembly_struct->toks[i].value;
            j++;
        }
    }
}

void new_index_tok(asm_struct* assembly_struct, size_t index_cmd)
{
    size_t new_index = 0;

    if(index_cmd == 0)
    {
        if((assembly_struct->toks[index_cmd].type == flg) || (assembly_struct->toks[index_cmd].type == fnc))
        {
            assembly_struct->toks[index_cmd].new_index = -1;
            return;
        }
        else
        {
            assembly_struct->toks[index_cmd].new_index = 0;
            return;
        }
    }   
    else if(assembly_struct->toks[index_cmd].type == cmd || assembly_struct->toks[index_cmd].type == val || assembly_struct->toks[index_cmd].type == reg || 
                ((assembly_struct->toks[index_cmd].type == fnc) && (strcmp(assembly_struct->toks[index_cmd-1].text, "CALL") == 0)) || 
                    ((assembly_struct->toks[index_cmd].type == flg) && (strcmp(assembly_struct->toks[index_cmd-1].text, "JMP") == 0)) || 
                        ((assembly_struct->toks[index_cmd].type == flg) && (strcmp(assembly_struct->toks[index_cmd-1].text, "JZ") == 0)))
    {
        for(size_t i = 0; i < index_cmd; i++)
        {
            if(i == 0)
            {
                if(assembly_struct->toks[i].type == cmd || assembly_struct->toks[i].type == val || assembly_struct->toks[i].type == reg)
                {
                    new_index++;
                }
            }  
            else if(assembly_struct->toks[i].type == cmd || assembly_struct->toks[i].type == val || assembly_struct->toks[i].type == reg || 
                        ((assembly_struct->toks[i].type == fnc) && (strcmp(assembly_struct->toks[i-1].text, "CALL") == 0)) || ((assembly_struct->toks[i].type == flg) && 
                            (strcmp(assembly_struct->toks[i-1].text, "JMP") == 0)) || ((assembly_struct->toks[i].type == flg) && (strcmp(assembly_struct->toks[i-1].text, "JZ") == 0)))
            {
                new_index++;
            }
            else
            {
                assembly_struct->toks[index_cmd].new_index = -1;;
            }
        }
    }
    else
    {
        assembly_struct->toks[index_cmd].new_index = - 1;
        return;
    }

    assembly_struct->toks[index_cmd].new_index = new_index;
}

void put_new_index(asm_struct* assembly_struct)
{
    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {
        new_index_tok(assembly_struct, i);
    }
}

size_t get_new_num_toks(asm_struct* assembly_struct)
{
    size_t max = 0;

    for(size_t i = 0; i < assembly_struct->num_toks; i++)   
    {
        max = max <= assembly_struct->toks[i].new_index ? assembly_struct->toks[i].new_index : max;
    }

    return (max + 1); // The number of tokens with right indexes
}

void max_len_tok(asm_struct* assembly_struct)
{
    for(size_t i = 0; i < assembly_struct->num_toks; i++)
    {
        size_t length_tok_i = strlen(assembly_struct->toks[i].text);
        assembly_struct->length_listing = (assembly_struct->length_listing <= length_tok_i)? length_tok_i: assembly_struct->length_listing;
    }
}
