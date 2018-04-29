#ifndef PDP11_DECODE_INST_H
#define PDP11_DECODE_INST_H

enum opcode
{
    MOV  = 0x1,
    ADD  = 0x6,
    SOB  = 0x77,
    MOVB = 0x11,
    BEQ  = 0x14,
    BR   = 0x4,
    TSTB = 0x1057,
    HALT = 0x0
};


enum exec_command_status
{
    EXEC_OK,
    EXEC_EXIT
};

int exec_command(int16_t* R, char* mem, int16_t* pc);

int decode_A_type(int16_t inst, int16_t *R, char *mem, int16_t *pc);
int decode_B_type(int16_t inst, int16_t *R, char *mem, int16_t *pc);
int decode_C_type(int16_t inst, int16_t *R, char *mem, int16_t *pc);
int decode_D_type(int16_t inst, int16_t *R, char *mem, int16_t *pc);
int decode_E_type(int16_t inst, int16_t *R, char *mem, int16_t *pc);
int decode_F_type(int16_t inst, int16_t *R, char *mem, int16_t *pc);

#endif //PDP11_DECODE_INST_H
