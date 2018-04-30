#include "inst_set.h"

extern void  add_op(int16_t* op1, int16_t* op2, int16_t* pc);
extern void  mov_op(int16_t* op1, int16_t* op2, int16_t* pc);
extern void  clr_op(int16_t* op1, int16_t* pc);
extern void  sob_op(int16_t* op1, int16_t* op2, int16_t* pc);

//TODO: beq_op, br_op, tstb_op;