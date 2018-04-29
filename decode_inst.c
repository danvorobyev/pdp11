#include <stdint.h>
#include "decode_inst.h"

#define slice(val, lsb, len) (((val) >> (lsb)) & ((1 << (len)) - 1))

int exec_command(int16_t* R, char* mem, int16_t* pc){
    int16_t inst = *(int16_t*)(mem + *pc); // for 16bit instructions
    int ret_status;

    while(1){
        ret_status = decode_A_type(inst, R, mem, pc);
        if(ret_status == EXEC_OK)
            break;
    }


    return ret_status;
}


int decode_A_type(int16_t inst, int16_t *R, char *mem, int16_t *pc)
{
    int opcode = slice(inst, 12, 4);
    int ss = slice(inst, , );
    int dd = slice(inst, , );
    switch (opcode)
    {
        case ADD:
            //TODO: add;
            return EXEC_OK;
        case MOV:
            //TODO: mov;
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

