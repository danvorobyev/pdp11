#ifndef PDP11_INST_SET_H
#define PDP11_INST_SET_H

#include <stdint.h>
#include <stdio.h>

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
    *pc += 4;
}

inline void clr_op(int16_t* op1, int16_t* pc)
{
    *op1 = 0;
    *pc += 2;
}

//*************************** BRANCH *****************************

inline void sobr_op(int16_t* op1, int16_t* pc)
{
    *op1 = 0;
    *pc += 2;
}


#endif //PDP11_INST_SET_H
