#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "decode_inst.h"
#include "inst_set.h"

#define slice(val, lsb, len) (((val) >> (lsb)) & ((1 << (len)) - 1))



int decode_A_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw) // opcode = 16
{
    int opcode = slice(inst, 0, 16);
    switch(opcode)
    {
        case HALT:
            printf("%o: HALT\n", *pc);
            *pc += 2;
            printf("\n---------------- halted ---------------\n");
            return EXEC_EXIT;
        default:
            return EXEC_EXIT;
    }
}

int decode_B_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw) // opcode = 4, command = 12
{
    int opcode = slice(inst, 12, 4);
    int16_t* op1;
    int16_t* op2;


    int16_t ss =(int16_t)(slice(inst, 6, 6));
    int16_t dd =(int16_t)(slice(inst, 0, 6));

    switch (opcode)
    {
        case ADD:
            printf("%o: ADD     ", *pc);
            op1 = exec(ss, R, mem, pc, WORD);
            printf(",");
            op2 = exec(dd, R, mem, pc, WORD);
            printf("\n");
            add_op(op1, op2, pc, psw);
            return EXEC_OK;
        case MOV:
            printf("%o: MOV     ", *pc);
            op1 = exec(ss, R, mem, pc, WORD);
            printf(",");
            op2 = exec(dd, R, mem, pc, WORD);
            printf("\n");
            mov_op(op1, op2, pc, psw);
            return EXEC_OK;
        case MOVb:
            printf("%o: MOVb", *pc);
            op1= exec(ss, R, mem, pc, BYTE);
            printf(",");
            op2 = exec(dd, R, mem, pc, BYTE);
            operandTObyte(op1);
            movb_op(op1, op2, pc, psw);
            printf("\n");
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_C_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw) // opcode = 7, command = 9
{
    int opcode = slice(inst, 9, 7);
    int16_t op1;
    int16_t op2;
    switch(opcode)
    {
        case SOB:
            printf("%o: SOB     ", *pc);
            op1 = (int16_t)(slice(inst, 6, 3));
            op2 = (int16_t)(slice(inst, 0, 6));
            printf ("r%o,%06o", op1, *pc + 2 - (op2 << 1));
            printf("\n");
            sob_op(&R[op1], &op2, pc, psw);
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_D_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw) // opcode = 8, command = 8
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

int decode_E_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw) // opcode = 10, command = 6
{
    int opcode = slice(inst, 6, 10);
    switch(opcode)
    {
        case TSTb:
            //TODO: sob;
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_F_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw)// opcode = 13, command = 3
{
    int opcode = slice(inst, 6, 10);
    int16_t* op1;
    int16_t dd =(int16_t)(slice(inst, 0, 6));
    switch(opcode)
    {
        case CLR:
            printf("%o: CLR     ", *pc);
            op1 = exec(dd, R, mem, pc, WORD);
            printf("\n");
            clr_op(op1, pc, psw);
            return EXEC_OK;
    }
}


void operandTObyte(int16_t* op)
{
    int16_t buf = *op & (int16_t)0xFF;
    if(buf >> 7 == 1)
        buf = (int16_t)0xFF00 | buf;
    *op = buf;
}


int16_t* exec(int16_t operand, int16_t * R, char* mem, int16_t *pc, int byteORword)
{

    int16_t mode = (operand >> 3) & (int16_t)(0x7);
    int16_t reg = operand & (int16_t)(0x7);
    int16_t buf;
    switch(mode)
    {
        case 0:
            printf("r%o", reg);
            return &R[reg];

        case 1:
            printf("(r)%o", reg);
            return (int16_t *)(mem + R[reg]);

        case 2:
            if (reg == 7)
            {
                *pc += 2;
                printf("#%06o", *(int16_t *)(mem + *pc));
                return (int16_t *)(mem + *pc);
            }
            printf("(r%o)+", reg);
            buf = R[reg];
            R[reg] += 1 + byteORword;
            return (int16_t *)(mem + buf);
        case 3:
            if (reg == 7)
            {
                *pc += 2;
                printf("#%06o ",*(int16_t *)(mem + *(int16_t *)(mem + *pc)));
                return (int16_t *)(mem + *(int16_t *)(mem + *pc));
            }
            printf("@(r%o)+", reg);
            buf = R[reg];
            R[reg] += 2;
            return (int16_t *)(mem + *(int16_t *)(mem + buf));

        case 4:
            printf("-(r%o)", reg);
            R[reg] -= 1 + byteORword;
            return (int16_t *)(mem + R[reg]);

        case 5:
            printf("@-(r%o)", reg);
            R[reg] -= 2;
            return (int16_t *)(mem + *(int16_t *)(mem + R[reg]));

        case 6:
            return NULL;
        case 7:

            return NULL;
        default:
            return NULL;

    }
}

int exec_command(int16_t* R, char* mem, int16_t* pc, int16_t* psw)
{
    int16_t inst = *(int16_t*)(mem + *pc); // for 16bit instructions
    int ret_status;

    while(1){

        ret_status = decode_A_type(inst, R, mem, pc, psw);
        if(ret_status == EXEC_OK)
            break;
        ret_status = decode_B_type(inst, R, mem, pc, psw);
        if(ret_status == EXEC_OK)
            break;
        ret_status = decode_C_type(inst, R, mem, pc, psw);
        if(ret_status == EXEC_OK)
            break;
        ret_status = decode_D_type(inst, R, mem, pc, psw);
        if(ret_status == EXEC_OK)
            break;
        ret_status = decode_E_type(inst, R, mem, pc, psw);
        if(ret_status == EXEC_OK)
            break;
        ret_status = decode_F_type(inst, R, mem, pc, psw);
        if(ret_status == EXEC_OK)
            break;
        break;

    }

    return ret_status;
}


