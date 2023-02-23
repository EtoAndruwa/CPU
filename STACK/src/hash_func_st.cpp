#include "stack.h"

void Calculate_hash(Stack* stack_struct) // (OK) Recalculates the value of hash everytime when called
{
    stack_struct->hash = 0; // Calculating new hash
    for(size_t i = 0; i < stack_struct->next_empty_cell; i++)
    {   
        if(stack_struct->data[i] != POISON_VALUE)
        {
            stack_struct->hash = stack_struct->hash + stack_struct->data[i];
        }
    }
}

stack_type Get_cur_value_of_hash(Stack* stack_struct) // (OK) Calculates the current value of the hash
{   
    stack_type cur_value_of_hash = 0;
    for(size_t i = 0; i < stack_struct->next_empty_cell; i++) 
    {
        cur_value_of_hash += stack_struct->data[i]; 
    }    

    return cur_value_of_hash;
}
