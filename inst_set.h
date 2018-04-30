#ifndef PDP11_INST_SET_H
#define PDP11_INST_SET_H

#include <stdint.h>
#include <stdio.h>

enum bit_scheme // N -> 1_bit; Z -> 2_bit; V -> 3_bit; C -> 4_bit
{
    N_mask = 0x1,
    Z_mask = 0x2,
    V_mask = 0x4,
    C_mask = 0x8
};


//******************** ARITHMETIC OPERATIONS ********************

inline void  add_op(int16_t* op1, int16_t* op2, int16_t* pc, int16_t* psw)
{
    *op2 = *op1 + *op2;
    *pc += 2;
}

//************************ STORE AND LOAD ************************

inline void  mov_op(int16_t* op1, int16_t* op2, int16_t* pc, int16_t* psw)
{
    *op2 = *op1;
    *pc += 2;
}

inline void clr_op(int16_t* op1, int16_t* pc, int16_t* psw)
{
    *op1 = 0;
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
    *pc += (((*psw & C_mask) >> 3) == 0) ? ((*offset) << 1) : 2;
}

inline void bcs_op(int16_t * offset, int16_t* pc, int16_t* psw) //C = 1
{
    *pc += (((*psw & C_mask) >> 3) == 1) ? ((*offset) << 1) : 2;
}

inline void beq_op(int16_t * offset, int16_t* pc, int16_t* psw) //Z = 1
{
    *pc += (((*psw & Z_mask) >> 1) == 1) ? ((*offset) << 1) : 2;
}

inline void bge_op(int16_t * offset, int16_t* pc, int16_t* psw) // N ^ V = 0
{
    *pc += (((*psw & N_mask) ^ ((*psw & V_mask) >> 2)) == 0) ? ((*offset) << 1) : 2;
}

inline void bgt_op(int16_t * offset, int16_t* pc, int16_t* psw) // Z * (N ^ V) = 0
{
    *pc += (((*psw & Z_mask) >> 1) & ((*psw & N_mask) ^ ((*psw & V_mask) >> 2)) == 0) ? ((*offset) << 1) : 2;
}

inline void bhi_op(int16_t * offset, int16_t* pc, int16_t* psw) // C * Z = 0
{
    *pc += ((((*psw & C_mask) >> 3) ^ ((*psw & Z_mask) >> 1)) == 0) ? ((*offset) << 1) : 2;
}

inline void bhis_op(int16_t * offset, int16_t* pc, int16_t* psw) // C = 0
{
    *pc += (((*psw & C_mask) >> 3) == 0) ? ((*offset) << 1) : 2;
}

inline void ble_op(int16_t * offset, int16_t* pc, int16_t* psw) // Z * (N ^ V) = 1
{
    *pc += (((*psw & Z_mask) >> 1) & ((*psw & N_mask) ^ ((*psw & V_mask) >> 2)) == 1) ? ((*offset) << 1) : 2; // Z * (N ^ V) = 1
}

inline void blo_op(int16_t * offset, int16_t* pc, int16_t* psw) // C = 1
{
    *pc += (((*psw & C_mask) >> 3) == 1) ? ((*offset) << 1) : 2;
}
inline void blos_op(int16_t * offset, int16_t* pc, int16_t* psw) // C * Z = 1
{
    *pc += ((((*psw & C_mask) >> 3) ^ ((*psw & Z_mask) >> 1)) == 1) ? ((*offset) << 1) : 2;
}

inline void blt_op(int16_t * offset, int16_t* pc, int16_t* psw) // N ^ V = 1
{
    *pc += (((*psw & N_mask) ^ ((*psw & V_mask) >> 2)) == 1) ? ((*offset) << 1) : 2;
}

inline void bmi_op(int16_t * offset, int16_t* pc, int16_t* psw) // N = 1
{
    *pc += ((*psw & N_mask) == 1) ? ((*offset) << 1) : 2;
}

inline void bne_op(int16_t * offset, int16_t* pc, int16_t* psw) // Z = 0
{
    *pc += (((*psw & Z_mask) >> 1) == 0) ? ((*offset) << 1) : 2;
}

inline void bpl_op(int16_t * offset, int16_t* pc, int16_t* psw) // N = 0
{
    *pc += ((*psw & N_mask) == 0) ? ((*offset) << 1) : 2;
}

inline void br_op(int16_t * offset, int16_t* pc, int16_t* psw) // Unconditional
{
    *pc += ((*offset) << 2);
}

inline void bvc_op(int16_t * offset, int16_t* pc, int16_t* psw) // V = 0
{
    *pc += (((*psw & V_mask) >> 2) == 0) ? ((*offset) << 1) : 2;
}

inline void bvs_op(int16_t * offset, int16_t* pc, int16_t* psw) // V = 1
{
    *pc += (((*psw & V_mask) >> 2) == 1) ? ((*offset) << 1) : 2;
}




#endif //PDP11_INST_SET_H
