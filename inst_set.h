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

inline void  add_op(int16_t* op1, int16_t* op2, int16_t* pc, int16_t* psw)
{
    int16_t sign_op1 = ((*op1) >> 15) & (int16_t)0x1;
    int16_t sign_op2 = ((*op2) >> 15) & (int16_t)0x1;

    *op2 = *op1 + *op2;
    *pc += 2;

    int16_t sign_sum = ((*op2) >> 15) & (int16_t)0x1;

    *psw = (*op2 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*op2 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    *psw = (((sign_op1 ^ sign_op2) | ((sign_op1 + sign_sum) & 0x1) ^ 0x1) == 1) ? (*psw | V_mask) : (*psw & V_to_zero);
    *psw = (((sign_op1 ^ sign_op2) | ((sign_op1 + sign_sum) & 0x1) ^ 0x1) == 1) ? (*psw | C_mask) : (*psw & C_to_zero);

}


//************************ STORE AND LOAD ************************

inline void  mov_op(int16_t* op1, int16_t* op2, int16_t* pc, int16_t* psw)
{
    *op2 = *op1;
    *pc += 2;

    *psw = (*op1 < 0) ? (*psw | N_mask) : (*psw & N_to_zero);
    *psw = (*op1 == 0) ? (*psw | Z_mask) : (*psw & Z_to_zero);
    *psw = (*psw & V_to_zero);
}

inline void clr_op(int16_t* op1, int16_t* pc, int16_t* psw)
{
    *op1 = 0;
    *pc += 2;

    *psw = (*psw & N_to_zero);
    *psw = (*psw | Z_mask);
    *psw = (*psw & V_to_zero);
    *psw = (*psw & C_to_zero);
}

inline void movb_op(int16_t* op1, int16_t* op2, int16_t* pc, int16_t* psw)
{
    *op2 = *op1;
    *pc += 2;
}

//*************************** BRANCH *****************************

inline void sob_op(int16_t* op1, int16_t* op2, int16_t* pc, int16_t* psw)
{
    int16_t buf = ((*op2) << 1);

    if(*op1 != 1)
    {
        *pc -= buf;
        *op1 -= 1;
    }
    *pc += 2;
}

inline void bcc_op(int16_t* offset, int16_t* pc, int16_t* psw) //C = 0
{
    *pc += (((*psw & C_mask) & (int16_t)0x1) == 0) ? ((*offset) << 1) : 2;
}

inline void bcs_op(int16_t * offset, int16_t* pc, int16_t* psw) //C = 1
{
    *pc += (((*psw & C_mask) & (int16_t)0x1) == 1) ? ((*offset) << 1) : 2;
}

inline void beq_op(int16_t * offset, int16_t* pc, int16_t* psw) //Z = 1
{
    *pc += ((((*psw & Z_mask) >> 2) & (int16_t)0x1) == 1) ? ((*offset) << 1) : 2;
}

inline void bge_op(int16_t * offset, int16_t* pc, int16_t* psw) // N ^ V = 0
{
    *pc += (((((*psw & N_mask) >> 3) ^ ((*psw & V_mask) >> 1)) & (int16_t)0x1) == 0) ? ((*offset) << 1) : 2;
}

inline void bgt_op(int16_t * offset, int16_t* pc, int16_t* psw) // Z * (N ^ V) = 0
{
    *pc += ((((*psw & Z_mask) >> 2) & (((*psw & N_mask) >> 3) ^ ((*psw & V_mask) >> 1)) & (int16_t)0x1) == 0) ? ((*offset) << 1) : 2;
}

inline void bhi_op(int16_t * offset, int16_t* pc, int16_t* psw) // C * Z = 0
{
    *pc += ((((*psw & C_mask) ^ ((*psw & Z_mask) >> 2)) & (int16_t)0x1) == 0) ? ((*offset) << 1) : 2;
}

inline void bhis_op(int16_t * offset, int16_t* pc, int16_t* psw) // C = 0
{
    *pc += (((*psw & C_mask) & (int16_t)0x1) == 0) ? ((*offset) << 1) : 2;
}

inline void ble_op(int16_t * offset, int16_t* pc, int16_t* psw) // Z * (N ^ V) = 1
{
    *pc += ((((*psw & Z_mask) >> 2) & (((*psw & N_mask) >> 3) ^ ((*psw & V_mask) >> 1)) & (int16_t)0x1) == 1) ? ((*offset) << 1) : 2; // Z * (N ^ V) = 1
}

inline void blo_op(int16_t * offset, int16_t* pc, int16_t* psw) // C = 1
{
    *pc += (((*psw & C_mask) & (int16_t)0x1) == 1) ? ((*offset) << 1) : 2;
}
inline void blos_op(int16_t * offset, int16_t* pc, int16_t* psw) // C * Z = 1
{
    *pc += ((((*psw & C_mask) ^ ((*psw & Z_mask) >> 2)) & (int16_t)0x1) == 1) ? ((*offset) << 1) : 2;
}

inline void blt_op(int16_t * offset, int16_t* pc, int16_t* psw) // N ^ V = 1
{
    *pc += (((((*psw & N_mask) >> 3) ^ ((*psw & V_mask) >> 1)) & (int16_t)0x1) == 1) ? ((*offset) << 1) : 2;
}

inline void bmi_op(int16_t * offset, int16_t* pc, int16_t* psw) // N = 1
{
    *pc += ((((*psw & N_mask) >> 3) & (int16_t)0x1) == 1) ? ((*offset) << 1) : 2;
}

inline void bne_op(int16_t * offset, int16_t* pc, int16_t* psw) // Z = 0
{
    *pc += ((((*psw & Z_mask) >> 2) & (int16_t)0x1) == 0) ? ((*offset) << 1) : 2;
}

inline void bpl_op(int16_t * offset, int16_t* pc, int16_t* psw) // N = 0
{
    *pc += ((((*psw & N_mask) >> 3) & (int16_t)0x1) == 0) ? ((*offset) << 1) : 2;
}

inline void br_op(int16_t * offset, int16_t* pc, int16_t* psw) // Unconditional
{
    *pc += ((*offset) << 2);
}

inline void bvc_op(int16_t * offset, int16_t* pc, int16_t* psw) // V = 0
{
    *pc += ((((*psw & V_mask) >> 1) & (int16_t)0x1) == 0) ? ((*offset) << 1) : 2;
}

inline void bvs_op(int16_t * offset, int16_t* pc, int16_t* psw) // V = 1
{
    *pc += ((((*psw & V_mask) >> 1) & (int16_t)0x1) == 1) ? ((*offset) << 1) : 2;
}




#endif //PDP11_INST_SET_H
