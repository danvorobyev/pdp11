#ifndef PDP11_INST_SET_H
#define PDP11_INST_SET_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum bit_scheme // N -> 1_bit; Z -> 2_bit; V -> 3_bit; C -> 4_bit
{
    N_mask = 0x8,
    Z_mask = 0x4,
    V_mask = 0x2,
    C_mask = 0x1
};

enum flag_to_zero{
    N_to_zero = 0xFFF7,
    Z_to_zero = 0xFFFB,
    V_to_zero = 0xFFFD,
    C_to_zero = 0xFFFE
};


//******************** ARITHMETIC OPERATIONS ********************

inline void  add_op(int16_t* op1, int16_t* op2, int16_t* psw)
{
    int16_t sign_op1 = ((*op1) >> 15) & (int16_t)0x1;
    int16_t sign_op2 = ((*op2) >> 15) & (int16_t)0x1;

    *op2 = *op1 + *op2;

    int16_t sign_sum = ((*op2) >> 15) & (int16_t)0x1;

    *psw = (*op2 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*op2 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    *psw = ((((sign_op1 ^ sign_op2) | ((sign_op1 + sign_sum) & 0x1)) ^ (0x1)) == 0) ? (*psw | V_mask) : (*psw & V_to_zero);
    *psw = ((sign_op2 & sign_sum) == 1) ? (*psw | C_mask) : (*psw & C_to_zero);
}

inline void sub_op(int16_t* op1, int16_t* op2, int16_t* psw)
{
    int16_t sign_op1 = ((*op1) >> 15) & (int16_t)0x1;
    int16_t sign_op2 = ((*op2) >> 15) & (int16_t)0x1;

    *op2 += ~(*op1) + (int16_t)1;

    int16_t sign_sub = ((*op2) >> 15) & (int16_t)0x1;

    *psw = (*op2 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*op2 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    *psw = (((sign_op1 ^ sign_op2) & (sign_op2 ^ sign_sub)) == 1) ? (*psw | V_mask) : (*psw & V_to_zero);
    *psw = ((sign_op2 & sign_sub) == 1) ?  (*psw & C_to_zero) : (*psw | C_mask);
}

inline void inc_op(int16_t* op1, int16_t* psw)
{
    *psw = (*op1 == 077777) ? (*psw | V_mask) : (*psw & V_to_zero);

    *op1 += 1;

    *psw = (*op1 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*op1 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);

}

inline void ash_op(int16_t op1, int16_t* op2, int16_t* psw, int16_t* R)
{
    int16_t sign_op2 = (((*op2) >> 5) & (int16_t)0x1);
    int16_t n = ((int16_t)0x3f & *op2) ;
    if (sign_op2 == 0)
    {
        R[op1] = (R[op1] << abs(n));
        *psw = (((*op2 >> 15) & 0x1) == 1) ? (*psw | C_mask) : (*psw & C_to_zero);
    }
    else
    {
        n = n | (int16_t)0xFFC0;
        R[op1] = (R[op1] >> abs(n));
        *psw = ((*op2 & 0x1) == 1) ? (*psw | C_mask) : (*psw & C_to_zero);
    }
    *psw = (R[op1] < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (R[op1] == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);


}

inline void incb_op(char* op1, int16_t* psw, int mode)
{
    *psw = ((int16_t)(*op1) == 0177) ? (*psw | V_mask) : (*psw & V_to_zero);

    if(mode == 0)
        *(int16_t*)op1 += 1;
    else
        *(int8_t*)op1 += 1;

    *psw = (*(int8_t*)op1 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*(int8_t*)op1 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
}

inline void dec_op(int16_t* op1, int16_t* psw)
{
    //*psw = (*op1 == 0x8000) ? (*psw | V_mask) : (*psw & V_to_zero);

    *op1 -= 1;

    *psw = (*op1 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*op1 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);

}

inline void adc_op(int16_t* op1, int16_t* psw)
{
    int16_t buf = *op1;

    *op1 += ((*psw & C_mask) == 0) ? 0 : 1;

    *psw = (*op1 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*op1 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    *psw = (buf == 077777) ? (*psw | V_mask) : (*psw & V_to_zero);
    //*psw = ((buf == 0177777) && ((*psw & C_mask) == 1))? (*psw | C_mask) : (*psw & C_to_zero);
}

inline void sbc_op(int16_t* op1, int16_t* psw)
{
    int16_t buf = *op1;

    *op1 -= ((*psw & C_mask) == 0) ? 0 : 1;

    *psw = (*op1 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*op1 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    //*psw = (buf == 0x8000) ? (*psw | V_mask) : (*psw & V_to_zero);
    *psw = ((buf == 000000) && ((*psw & C_mask) == 1))?  (*psw & C_to_zero) : (*psw | C_mask);
}

inline void neg_op(int16_t* op1, int16_t* psw)
{
    *op1 = ~(*op1) + (int16_t)1;

    *psw = (*op1 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*op1 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    //*psw = (*op1 == 0100000) ? (*psw | V_mask) : (*psw & V_to_zero);
    *psw = (*op1 == 0) ?  (*psw & C_to_zero) : (*psw | C_mask);
}

inline void mul_op(int16_t op1, int16_t* op2, int16_t* R, int16_t* psw)
{
    int32_t res = R[op1] * (*op2);

    if(op1 % 2 == 0)
    {
        R[op1] = (int16_t)((res >> 16) & 0xFFFF);
        R[op1 + 1] = (int16_t)((res) & 0xFFFF);
    }
    else
    {
        R[op1] = (int16_t)((res) & 0xFFFF);
    }

    *psw = (res < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (res == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    *psw = (*psw & V_to_zero);
    *psw = ((res < -0x8000) || (res > 0x7FFF)) ?  (*psw | C_mask) : (*psw & C_to_zero);
}

inline void div_op(int16_t op1, int16_t* op2, int16_t* R, int16_t* psw) {
    if (op1 % 2 == 0) {
        int32_t buf = (int32_t) (((R[op1] << 16) & 0xFFFF0000) | (R[op1 + 1] & 0xFFFF));
        R[op1] = (int16_t) (buf / *op2);
        int16_t sign = (int16_t) (R[op1] & 0x8000);
        R[op1 + 1] = (int16_t) ((buf % *op2) | sign);
    }

    *psw = (R[op1] < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (R[op1] == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    *psw = ((op1 % 2 == 1) || (*op2 == 0) || (R[op1] < *op2)) ?  (*psw | V_mask) : (*psw & V_to_zero);
    *psw = (*op2 == 0) ?  (*psw | C_mask) : (*psw & C_to_zero);
}

inline void cmp_op(int16_t* op1, int16_t* op2, int16_t* psw)
{
    int16_t sign_op1 = ((*op1) >> 15) & (int16_t)0x1;
    int16_t sign_op2 = ((*op2) >> 15) & (int16_t)0x1;

    int16_t buf = *op1 + (~(*op2) + (int16_t)1);

    int16_t sign_buf = ((*op2) >> 15) & (int16_t)0x1;

    *psw = (buf < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (buf == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    *psw = (((sign_op1 ^ sign_op2) & (sign_op1 ^ sign_buf)) == 1) ? (*psw | V_mask) : (*psw & V_to_zero);
    *psw = ((sign_op1 & sign_buf) == 1) ? (*psw | C_mask) : (*psw & C_to_zero);
}

inline void asr_op(int16_t* op1, int16_t* psw)
{
    int c = *op1 & 1;
    *op1 = *op1 >> 1;

    *psw = (*op1 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*op1 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    *psw = (c == 1) ? (*psw | C_mask) : (*psw & C_to_zero);
    *psw = ((*psw >> 3)^ *psw) ? (*psw | V_mask) : (*psw & V_to_zero);
}

inline void asl_op(int16_t* op1, int16_t* psw)
{
    *psw = (((*op1 >> 15) & (int16_t)0x1) | *psw); // for C

    *op1 = (*op1 << 1);

    *psw = (*op1 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*op1 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    *psw = (*psw | ((((*psw >> 3) & (int16_t)(0x1)) ^ ((*psw >> 2) & (int16_t)(0x1))) << 1));
}

inline void  bic_op(int16_t* op1, int16_t* op2, int16_t* psw)
{
    *op2 = (~(*op1)) & *op2;

    *psw = (*op2 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*op2 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    *psw = (*psw & V_to_zero);
}

//************************ STORE AND LOAD ************************

inline void  mov_op(int16_t* op1, int16_t* op2, int16_t* psw)
{
    *op2 = *op1;

    *psw = (*op1 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*op1 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    *psw = (*psw & V_to_zero);
}

inline void clr_op(int16_t* op1, int16_t* psw)
{
    *op1 = 0;

    *psw = (*psw & N_to_zero);
    *psw = (*psw | Z_mask);
    *psw = (*psw & V_to_zero);
    *psw = (*psw & C_to_zero);
}

inline void movb_op(int8_t* op1, char* op2, int16_t* psw, int mode)
{
    if(mode == 0)
        *(int16_t*)(op2) = *(op1);
    else
        *(int8_t*)(op2) = *(op1);

    *psw = (*op1 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*op1 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    *psw = *psw & V_to_zero;
}

//*************************** JUMP *****************************

inline void sob_op(int16_t* op1, int16_t* op2, int16_t* pc, int16_t* psw)
{
    int16_t buf = ((*op2) << 1);
    *op1 -= 1;
    if(*op1 != 0)
        *pc -= buf;
}

inline void jsr_op(int16_t op1, int16_t* op2, int16_t* pc, int16_t* R, char* mem)
{
    *(int16_t*)(mem + R[6]+1000) = R[op1];
    R[6] -= 2;
    R[op1] = *pc;
    *pc = *op2;
}

inline void jmp_op(int16_t* op1, int16_t* pc)
{
    *pc = *op1;
}

inline void rts_op(int16_t* op1, int16_t* pc, int16_t* R, char* mem)
{
    *pc = R[*op1];
    R[6] += 2;
    R[*op1] = *(int16_t*)(mem + R[6] + 1000);
}

//*************************** BRANCH *****************************

inline void bcc_op(int16_t * offset, int16_t* pc, int16_t* psw) //C = 0
{
    *pc += (((*psw & C_mask) & (int16_t)0x1) == 0) ? ((*offset) << 1) : 0;
}

inline void bcs_op(int16_t * offset, int16_t* pc, int16_t* psw) //C = 1
{
    *pc += (((*psw & C_mask) & (int16_t)0x1) == 1) ? ((*offset) << 1) : 0;
}

inline void beq_op(int16_t * offset, int16_t* pc, int16_t* psw) //Z = 1
{
    *pc += ((((*psw & Z_mask) >> 2) & (int16_t)0x1) == 1) ? ((*offset) << 1) : 0;
}

inline void bge_op(int16_t * offset, int16_t* pc, int16_t* psw) // N ^ V = 0
{
    *pc += (((((*psw & N_mask) >> 3) ^ ((*psw & V_mask) >> 1)) & (int16_t)0x1) == 0) ? ((*offset) << 1) : 0;
}

inline void bgt_op(int16_t * offset, int16_t* pc, int16_t* psw) // Z | (N ^ V) = 0
{
    *pc += ((((*psw & Z_mask) >> 2) | (((*psw & N_mask) >> 3) ^ ((((*psw & V_mask) >> 1)) & (int16_t)0x1)))) == 0 ? ((*offset) << 1) : 0;
}

inline void bhi_op(int16_t * offset, int16_t* pc, int16_t* psw) // C * Z = 0
{
    *pc += ((((*psw & C_mask) ^ ((*psw & Z_mask) >> 2)) & (int16_t)0x1) == 0) ? ((*offset) << 1) : 0;
}

inline void bhis_op(int16_t * offset, int16_t* pc, int16_t* psw) // C = 0
{
    *pc += (((*psw & C_mask) & (int16_t)0x1) == 0) ? ((*offset) << 1) : 0;
}

inline void ble_op(int16_t * offset, int16_t* pc, int16_t* psw) // Z * (N ^ V) = 1
{
    *pc += ((((*psw & Z_mask) >> 2) & (((*psw & N_mask) >> 3) ^ ((*psw & V_mask) >> 1)) & (int16_t)0x1) == 1) ? ((*offset) << 1) : 0; // Z * (N ^ V) = 1
}

inline void blo_op(int16_t * offset, int16_t* pc, int16_t* psw) // C = 1
{
    *pc += (((*psw & C_mask) & (int16_t)0x1) == 1) ? ((*offset) << 1) : 0;
}
inline void blos_op(int16_t * offset, int16_t* pc, int16_t* psw) // C * Z = 1
{
    *pc += ((((*psw & C_mask) ^ ((*psw & Z_mask) >> 2)) & (int16_t)0x1) == 1) ? ((*offset) << 1) : 0;
}

inline void blt_op(int16_t * offset, int16_t* pc, int16_t* psw) // N ^ V = 1
{
    *pc += (((((*psw & N_mask) >> 3) ^ ((*psw & V_mask) >> 1)) & (int16_t)0x1) == 1) ? ((*offset) << 1) : 0;
}

inline void bmi_op(int16_t * offset, int16_t* pc, int16_t* psw) // N = 1
{
    *pc += ((((*psw & N_mask) >> 3) & (int16_t)0x1) == 1) ? ((*offset) << 1) : 0;
}

inline void bne_op(int16_t * offset, int16_t* pc, int16_t* psw) // Z = 0
{
    *pc += ((((*psw & Z_mask) >> 2) & (int16_t)0x1) == 0) ? ((*offset) << 1) : 0;
}

inline void bpl_op(int16_t * offset, int16_t* pc, int16_t* psw) // N = 0
{
    *pc += ((((*psw & N_mask) >> 3) & (int16_t)0x1) == 0) ? ((*offset) << 1) : 0;
}

inline void br_op(int16_t * offset, int16_t* pc, int16_t* psw) // Unconditional
{
    *pc += ((*offset) << 1);
}

inline void bvc_op(int16_t * offset, int16_t* pc, int16_t* psw) // V = 0
{
    *pc += ((((*psw & V_mask) >> 1) & (int16_t)0x1) == 0) ? ((*offset) << 1) : 0;
}

inline void bvs_op(int16_t * offset, int16_t* pc, int16_t* psw) // V = 1
{
    *pc += ((((*psw & V_mask) >> 1) & (int16_t)0x1) == 1) ? ((*offset) << 1) : 0;
}

//*************************** TEST *****************************

inline void tst_op(int16_t* op1, int16_t* psw)
{
    *psw = (*op1 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*op1 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    *psw = (*psw & V_to_zero);
    *psw = (*psw & C_to_zero);
}

inline void tstb_op(int8_t * op1, int16_t* psw)
{
    *psw = (*op1 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*op1 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    *psw = (*psw & V_to_zero);
    *psw = (*psw & C_to_zero);
}
#endif //PDP11_INST_SET_H
