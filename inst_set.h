#ifndef PDP11_INST_SET_H
#define PDP11_INST_SET_H

#include <stdint.h>
#include <stdio.h>

//******************** ARITHMETIC OPERATIONS ********************

inline void add_op()
{
    *rd = op1 + op2;
    *pc += 4; //+4 bits since pc is pointer to int32_t
    log(add_op);
}









#endif //PDP11_INST_SET_H
