#include "stack.h"

void Calculate_hash(Stack * st) // (OK) Recalculates the value of hash everytime when called
{
    st->hash = 0; // Calculating new hash
    for(size_t i = 0; i < st->next_empty_cell; i++)
    {   
        if(st->data[i] != POISON_VALUE)
        {
            st->hash = st->hash + st->data[i];
            //printf("Hash value: %d\n", st->hash);
        }
    }
}

stack_type Get_cur_value_of_hash(Stack * st) // (OK) Calculates the current value of the hash
{   
    stack_type cur_value_of_hash = 0;
    for(size_t i = 0; i < st->next_empty_cell; i++) 
    {
        cur_value_of_hash += st->data[i]; 
    }    

    return cur_value_of_hash;
}
