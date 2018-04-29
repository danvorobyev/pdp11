#ifndef PDP11_INST_SET_H
#define PDP11_INST_SET_H

#include <stdint.h>
#include <stdio.h>

//******************** ARITHMETIC OPERATIONS ********************

inline void  add_op(int16_t* op1, int16_t* op2, int16_t* pc)
{
    int16_t buf;
    buf = *op1 + *op2;
    op2 = &buf;
    *pc += 2;
}

inline void  mov_op(int16_t* op1, int16_t* op2, int16_t* pc)
{
    op2 = op1;
    *pc += 4;
}








#endif //PDP11_INST_SET_H
