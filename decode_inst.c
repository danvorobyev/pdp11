#include <stdint.h>
#include <stdio.h>
#include "decode_inst.h"

#define slice(val, lsb, len) (((val) >> (lsb)) & ((1 << (len)) - 1))

int exec_command(int16_t* R, char* mem, int16_t* pc){
    int16_t inst = *(int16_t*)(mem + *pc); // for 16bit instructions
    int ret_status;

    while(1){

        ret_status = decode_A_type(inst, R, mem, pc);
        if(ret_status == EXEC_OK)
            break;
        ret_status = decode_B_type(inst, R, mem, pc);
        if(ret_status == EXEC_OK)
            break;
        ret_status = decode_C_type(inst, R, mem, pc);
        if(ret_status == EXEC_OK)
            break;
        ret_status = decode_D_type(inst, R, mem, pc);
        if(ret_status == EXEC_OK)
            break;
        ret_status = decode_E_type(inst, R, mem, pc);
        if(ret_status == EXEC_OK)
            break;
        ret_status = decode_F_type(inst, R, mem, pc);
        if(ret_status == EXEC_OK)
            break;
        break;

    }

    return ret_status;
}

int decode_A_type(int16_t inst, int16_t *R, char *mem, int16_t *pc) // opcode = 16
{
    int opcode = slice(inst, 0, 16);
    switch(opcode)
    {
        case HALT:
            //TODO: halt;
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_B_type(int16_t inst, int16_t *R, char *mem, int16_t *pc) // opcode = 4, command = 12
{
    int opcode = slice(inst, 12, 4);

    switch (opcode)
    {
        case ADD:
            //TODO: add;
            return EXEC_OK;
        case MOV:
            //TODO: mov;
            return EXEC_OK;
        case MOVB:
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_C_type(int16_t inst, int16_t *R, char *mem, int16_t *pc) // opcode = 7, command = 9
{
    int opcode = slice(inst, 9, 7);
    switch(opcode)
    {
        case SOB:
            //TODO: sob;
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_D_type(int16_t inst, int16_t *R, char *mem, int16_t *pc) // opcode = 8, command = 8
{
    int opcode = slice(inst, 8, 8);
    switch(opcode)
    {
        case BEQ:
            return EXEC_OK;
        case BR:
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_E_type(int16_t inst, int16_t *R, char *mem, int16_t *pc) // opcode = 10, command = 6
{
    int opcode = slice(inst, 6, 10);
    switch(opcode)
    {
        case TSTB:
            //TODO: sob;
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_F_type(int16_t inst, int16_t *R, char *mem, int16_t *pc) // opcode = 13, command = 3
{

}

int16_t * before_exec(int16_t operand, int16_t * R, int16_t* mem, int16_t *pc){
    int16_t* x;

    int16_t mode = (operand >> 3) & (int16_t)(0x7);
    int16_t reg = operand & (int16_t)(0x7);

    switch(mode)
    {
        case 0:
            return &R[reg];
        case 1:

            return x;
        case 2:

            return x;
        case 3:

            return x;
        case 4:

            return x;
        case 5:

            return x;
        case 6:

            return x;
        case 7:

            return x;
        default:
            return NULL;

    }
}