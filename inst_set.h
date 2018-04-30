#ifndef PDP11_INST_SET_H
#define PDP11_INST_SET_H

#include <stdint.h>
#include <stdio.h>

enum bit_scheme // N -> 1_bit; Z -> 2_bit; V -> 3_bit; C -> 4_bit
{
    N = 0x1,
    Z = 0x2,
    V = 0x4,
    C = 0x8
};


//******************** ARITHMETIC OPERATIONS ********************

inline void  add_op(int16_t* op1, int16_t* op2, int16_t* pc)
{
    *op2 = *op1 + *op2;
    *pc += 2;
}

//************************ STORE AND LOAD ************************

inline void  mov_op(int16_t* op1, int16_t* op2, int16_t* pc)
{
    *op2 = *op1;
    *pc += 2;
}

inline void clr_op(int16_t* op1, int16_t* pc)
{
    *op1 = 0;
    *pc += 2;
}


//*************************** BRANCH *****************************

inline void sob_op(int16_t* op1, int16_t* op2, int16_t* pc)
{
    int16_t buf = ((*op2) << 1);

    if(*op1 != 1)
    {
        *pc -= buf;
        *op1 -= 1;
    }
    *pc += 2;
}

inline void bcc_op(int16_t* offset, int16_t* pc)
{
    *pc += ((psw & C) == 0) ? ((*offset) << 1) : 2; //C = 0
}

inline void bcs_op(int16_t * offset, int16_t* pc)
{
    *pc += ((psw & C) == 1) ? ((*offset) << 1) : 2; //C = 1
}

inline void beq_op(int16_t * offset, int16_t* pc)
{

}

inline void bge_op(int16_t * offset, int16_t* pc)
{

}

inline void bgt_op(int16_t * offset, int16_t* pc)
{

}

inline void bhi_op(int16_t * offset, int16_t* pc)
{

}

inline void bhis_op(int16_t * offset, int16_t* pc)
{

}

inline void ble_op(int16_t * offset, int16_t* pc)
{

}

inline void blo_op(int16_t * offset, int16_t* pc)
{

}
inline void blos_op(int16_t * offset, int16_t* pc)
{

}

inline void blt_op(int16_t * offset, int16_t* pc)
{

}

inline void bmi_op(int16_t * offset, int16_t* pc)
{

}

inline void bne_op(int16_t * offset, int16_t* pc)
{

}

inline void bpl_op(int16_t * offset, int16_t* pc)
{

}

inline void br_op(int16_t * offset, int16_t* pc)
{

}

inline void bvc_op(int16_t * offset, int16_t* pc)
{

}

inline void bvs_op(int16_t * offset, int16_t* pc)
{

}




#endif //PDP11_INST_SET_H
