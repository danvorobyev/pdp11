#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "decode_inst.h"
#include "inst_set.h"

#define slice(val, lsb, len) (((val) >> (lsb)) & ((1 << (len)) - 1))



int decode_A_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw) // opcode = 16
{
    int opcode = inst;
    switch(opcode)
    {
        case CCC:
            printf("%o: CCC", *pc);
            return EXEC_OK;
        case CLC:
            printf("%o: CLC", *pc);
            return EXEC_OK;
        case CLN:
            printf("%o: CLN", *pc);
            return EXEC_OK;
        case CLV:
            printf("%o: CLV", *pc);
            return EXEC_OK;
        case CLZ:
            printf("%o: CLZ", *pc);
            return EXEC_OK;
        case HALT:
            printf("%o: HALT\n", *pc);
            *pc += 2;
            printf("\n---------------- halted ---------------\n");
            return EXEC_EXIT;
        case NOP:
            printf("%o: NOP", *pc);
            return EXEC_OK;
        case RESET:
            printf("%o: RESET", *pc);
            return EXEC_OK;
        case SCC:
            printf("%o: SCC", *pc);
            return EXEC_OK;
        case SEC:
            printf("%o: SEC", *pc);
            return EXEC_OK;
        case SEN:
            printf("%o: SEN", *pc);
            return EXEC_OK;
        case SEV:
            printf("%o: SEV", *pc);
            return EXEC_OK;
        case SEZ:
            printf("%o: SEZ", *pc);
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_B_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw) // opcode = 4, command = 12
{
    int opcode = B_type & inst;
    int16_t* op1;
    int16_t* op2;
    int8_t* op3;
    char* op4;
    int mode;

    int16_t ss =(int16_t)(slice(inst, 6, 6));
    int16_t dd =(int16_t)(slice(inst, 0, 6));

    switch (opcode)
    {
        case ADD:
            printf("%o: ADD     ", *pc);
            op1 = (int16_t*)exec(ss, R, mem, pc, WORD);
            printf(",");
            op2 = (int16_t*)exec(dd, R, mem, pc, WORD);
            *pc += 2;
            printf("\n");
            add_op(op1, op2, psw);
            return EXEC_OK;
        case BIC:
            printf("%o: BIC", *pc);
            return EXEC_OK;
        case BICb:
            printf("%o: BICb", *pc);
            return EXEC_OK;
        case BIS:
            printf("%o: BIS", *pc);
            return EXEC_OK;
        case BISb:
            printf("%o: BISb", *pc);
            return EXEC_OK;
        case BIT:
            printf("%o: BIC", *pc);
            return EXEC_OK;
        case BITb:
            printf("%o: BITb", *pc);
            return EXEC_OK;
        case CMP:
            printf("%o: CMP", *pc);
            return EXEC_OK;
        case CMPb:
            printf("%o: CMPb", *pc);
            return EXEC_OK;
        case MOV:
            printf("%o: MOV     ", *pc);
            op1 = (int16_t*)exec(ss, R, mem, pc, WORD);
            printf(",");
            op2 = (int16_t*)exec(dd, R, mem, pc, WORD);
            *pc += 2;
            printf("\n");
            mov_op(op1, op2, psw);
            return EXEC_OK;
        case MOVb:
            printf("%o: MOVb    ", *pc);
            op3= (int8_t*)exec(ss, R, mem, pc, BYTE);
            printf(",");
            op4 = exec(dd, R, mem, pc, BYTE);
            *pc += 2;
            mode = slice(inst, 3, 3);
            movb_op(op3, op4, psw, mode);
            printf("\n");
            return EXEC_OK;
        case SUB:
            printf("%o: SUB", *pc);
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_C_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw) // opcode = 7, command = 9
{
    int opcode = C_type & inst;
    int16_t op1;
    int16_t op2;
    switch(opcode)
    {
        case ASH:
            printf("%o: ASH", *pc);
            return EXEC_OK;
        case ASHC:
            printf("%o: ASHC", *pc);
            return EXEC_OK;
        case JSR:
            printf("%o: JSR", *pc);
            return EXEC_OK;
        case SOB:
            printf("%o: SOB     ", *pc);
            op1 = (int16_t)(slice(inst, 6, 3));
            op2 = (int16_t)(slice(inst, 0, 6));
            *pc += 2;
            printf ("r%o,%06o", op1, *pc + 2 - (op2 << 1));
            printf("\n");
            sob_op(&R[op1], &op2, pc, psw);
            return EXEC_OK;
        case XOR:
            printf("%o: XOR", *pc);
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_D_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw) // opcode = 8, command = 8
{
    int opcode = D_type & inst;
    int16_t offset = (int16_t)(int8_t)(inst & 0xFF);
    switch(opcode)
    {
        case BCC:
            printf("%o: BCC", *pc);
            *pc += 2;
            bcc_op(&offset, pc, psw);
            printf("\n");
            return EXEC_OK;
        case BCS:
            printf("%o: BCS", *pc);
            *pc += 2;
            bcs_op(&offset, pc, psw);
            printf("\n");
            return EXEC_OK;
        case BEQ:
            printf("%o: BEQ", *pc);
            *pc += 2;
            beq_op(&offset, pc, psw);
            printf("\n");
            return EXEC_OK;
        case BGE:
            printf("%o: BGE", *pc);
            *pc += 2;
            bge_op(&offset, pc, psw);
            printf("\n");
            return EXEC_OK;
        case BGT:
            printf("%o: BGT", *pc);
            *pc += 2;
            bgt_op(&offset, pc, psw);
            printf("\n");
            return EXEC_OK;
        case BHI:
            printf("%o: BHI", *pc);
            *pc += 2;
            bhi_op(&offset, pc, psw);
            printf("\n");
            return EXEC_OK;
        case BLE:
            printf("%o: BLE", *pc);
            *pc += 2;
            ble_op(&offset, pc, psw);
            printf("\n");
            return EXEC_OK;
        case BLT:
            printf("%o: BLT", *pc);
            *pc += 2;
            blt_op(&offset, pc, psw);
            printf("\n");
            return EXEC_OK;
        case BLOS:
            printf("%o: BLOS", *pc);
            *pc += 2;
            blos_op(&offset, pc, psw);
            printf("\n");
            return EXEC_OK;
        case BMI:
            printf("%o: BMI", *pc);
            *pc += 2;
            bmi_op(&offset, pc, psw);
            printf("\n");
            return EXEC_OK;
        case BNE:
            printf("%o: BNE", *pc);
            *pc += 2;
            bne_op(&offset, pc, psw);
            printf("\n");
            return EXEC_OK;
        case BPL:
            printf("%o: BPL", *pc);
            *pc += 2;
            bpl_op(&offset, pc, psw);
            printf("\n");
            return EXEC_OK;
        case BR:
            printf("%o: BR", *pc);
            *pc += 2;
            br_op(&offset, pc, psw);
            printf("\n");
            return EXEC_OK;
        case BVC:
            printf("%o: BVC", *pc);
            *pc += 2;
            bvc_op(&offset, pc, psw);
            printf("\n");
            return EXEC_OK;
        case BVS:
            printf("%o: BVS", *pc);
            *pc += 2;
            bvs_op(&offset, pc, psw);
            printf("\n");
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_E_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw) // opcode = 10, command = 6
{
    int opcode = E_type & inst;
    int16_t* op;
    int16_t dd =(int16_t)(slice(inst, 0, 6));
    switch(opcode)
    {
        case ADC:
            printf("%o: ADC", *pc);
            op = (int16_t*)exec(dd, R, mem, pc, WORD);
            *pc += 2;
            adc_op(op, psw);
            printf("\n");
            return EXEC_OK;
        case ADCb:
            printf("%o: ADCb", *pc);
            return EXEC_OK;
        case ASL:
            printf("%o: ASL", *pc);
            return EXEC_OK;
        case ASLb:
            printf("%o: ASLb", *pc);
            return EXEC_OK;
        case ASR:
            printf("%o: ASR", *pc);
            return EXEC_OK;
        case ASRb:
            printf("%o: ASRb", *pc);
            return EXEC_OK;
        case CLR:
            printf("%o: CLR     ", *pc);
            op = (int16_t*)exec(dd, R, mem, pc, WORD);
            *pc += 2;
            clr_op(op, psw);
            printf("\n");
            return EXEC_OK;
        case CLRb:
            printf("%o: CLRb", *pc);
            return EXEC_OK;
        case COM:
            printf("%o: COM", *pc);
            return EXEC_OK;
        case COMb:
            printf("%o: COMb", *pc);
            return EXEC_OK;
        case DEC:
            printf("%o: DEC     ", *pc);
            op = (int16_t*)exec(dd, R, mem, pc, WORD);
            *pc += 2;
            dec_op(op, psw);
            printf("\n");
            return EXEC_OK;
        case DECb:
            printf("%o: DECb", *pc);
            return EXEC_OK;
        case INC:
            printf("%o: INC", *pc);
            op = (int16_t*)exec(dd, R, mem, pc, WORD);
            *pc += 2;
            inc_op(op, psw);
            printf("\n");
            return EXEC_OK;
        case INCb:
            printf("%o: INCb", *pc);
            return EXEC_OK;
        case JMP:
            printf("%o: JMP", *pc);
            return EXEC_OK;
        case NEG:
            printf("%o: NEG", *pc);
            return EXEC_OK;
        case NEGb:
            printf("%o: NEGb", *pc);
            return EXEC_OK;
        case ROL:
            printf("%o: ROL", *pc);
            return EXEC_OK;
        case ROLb:
            printf("%o: ROLb", *pc);
            return EXEC_OK;
        case ROR:
            printf("%o: ROR", *pc);
            return EXEC_OK;
        case RORb:
            printf("%o: RORb", *pc);
            return EXEC_OK;
        case SBC:
            printf("%o: SBC", *pc);
            op = (int16_t*)exec(dd, R, mem, pc, WORD);
            *pc += 2;
            sbc_op(op, psw);
            printf("\n");
            return EXEC_OK;
        case SBCb:
            printf("%o: SBCb", *pc);
            return EXEC_OK;
        case SWAB:
            printf("%o: SWAB", *pc);
            return EXEC_OK;
        case SXT:
            printf("%o: SXT", *pc);
            return EXEC_OK;
        case TST:
            printf("%o: TST", *pc);
            op = (int16_t*)exec(dd, R, mem, pc, WORD);
            *pc += 2;
            tst_op(op, psw);
            printf("\n");
            return EXEC_OK;
        case TSTb:
            printf("%o: TSTb", *pc);
            op = (*)exec(dd, R, mem, pc, WORD);
            *pc += 2;
            tst_op(op, psw);
            printf("\n");
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

int decode_F_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw)// opcode = 13, command = 3
{
    int opcode = F_type & inst;
    int16_t* op1;
    int16_t dd =(int16_t)(slice(inst, 0, 3));
    switch(opcode)
    {
        case RTS:
            printf("%o: RTS", *pc);
            return EXEC_OK;
        default:
            return EXEC_EXIT;
    }
}

char* exec(int16_t operand, int16_t * R, char* mem, int16_t *pc, int byteORword)
{

    int16_t mode = (operand >> 3) & (int16_t)(0x7);
    int16_t reg = operand & (int16_t)(0x7);
    int16_t buf;
    switch(mode)
    {
        case 0:
            printf("r%o", reg);
            return (char*)(R+reg);

        case 1:
            printf("(r)%o", reg);
            return mem + R[reg];

        case 2:
            if (reg == 7)
            {
                *pc += 2;
                printf("#%06o", *(int16_t *)(mem + *pc));
                return mem + *pc;
            }
            printf("(r%o)+", reg);
            buf = R[reg];
            R[reg] += 1 + byteORword;
            return mem + buf;
        case 3:
            if (reg == 7)
            {
                *pc += 2;
                printf("#%06o",*(int16_t *)(mem + *(int16_t *)(mem + *pc)));
                return mem + *(int16_t *)(mem + *pc);
            }
            printf("@(r%o)+", reg);
            buf = R[reg];
            R[reg] += 2;
            return mem + *(int16_t *)(mem + buf);

        case 4:
            printf("-(r%o)", reg);
            R[reg] -= 1 + byteORword;
            return mem + R[reg];

        case 5:
            printf("@-(r%o)", reg);
            R[reg] -= 2;
            return mem + *(int16_t *)(mem + R[reg]);

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

    while(1)
    {

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