#include "inst_set.h"

extern void  add_op(int16_t* op1, int16_t* op2, int16_t* pc, int16_t* psw);
extern void  inc_op(int16_t* op1, int16_t* pc, int16_t* psw);
extern void  dec_op(int16_t* op1, int16_t* pc, int16_t* psw);
extern void adc_op(int16_t* op1, int16_t* pc, int16_t* psw);
extern void sbc_op(int16_t* op1, int16_t* pc, int16_t* psw);

extern void  mov_op(int16_t* op1, int16_t* op2, int16_t* pc, int16_t* psw);
extern void  movb_op(int16_t* op1, int16_t* op2, int16_t* pc, int16_t* psw);
extern void  clr_op(int16_t* op1, int16_t* pc, int16_t* psw);


extern void  sob_op(int16_t* op1, int16_t* op2, int16_t* pc, int16_t* psw);
extern void  bcc_op(int16_t* offset, int16_t* pc, int16_t* psw);
extern void  bcs_op(int16_t * offset, int16_t* pc, int16_t* psw);
extern void  beq_op(int16_t * offset, int16_t* pc, int16_t* psw);
extern void  bge_op(int16_t * offset, int16_t* pc, int16_t* psw);
extern void  bgt_op(int16_t * offset, int16_t* pc, int16_t* psw);
extern void  bhi_op(int16_t * offset, int16_t* pc, int16_t* psw);
extern void  bhis_op(int16_t * offset, int16_t* pc, int16_t* psw);
extern void  ble_op(int16_t * offset, int16_t* pc, int16_t* psw);
extern void  blo_op(int16_t * offset, int16_t* pc, int16_t* psw);
extern void  blos_op(int16_t * offset, int16_t* pc, int16_t* psw);
extern void  blt_op(int16_t * offset, int16_t* pc, int16_t* psw);
extern void  bmi_op(int16_t * offset, int16_t* pc, int16_t* psw);
extern void  bne_op(int16_t * offset, int16_t* pc, int16_t* psw);
extern void  bpl_op(int16_t * offset, int16_t* pc, int16_t* psw);
extern void  br_op(int16_t * offset, int16_t* pc, int16_t* psw);
extern void  bvc_op(int16_t * offset, int16_t* pc, int16_t* psw);
extern void  bvs_op(int16_t * offset, int16_t* pc, int16_t* psw);

extern void tst_op(int16_t* op1, int16_t* pc, int16_t* psw);


//TODO: beq_op, br_op, tstb_op;