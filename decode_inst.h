#ifndef PDP11_DECODE_INST_H
#define PDP11_DECODE_INST_H

#define slice(val, lsb, len) (((val) >> (lsb)) & ((1 << (len)) - 1))

enum opcode
{
    MOV  = 01,
    ADD  = 06,
    SOB  = 077,
    MOVB = 011,
    BEQ  = 014,
    BR   = 04,
    TSTB = 01057,
    CLR  = 050,
    HALT = 00
};

enum byteORword
{
    BYTE,
    WORD
};

enum exec_command_status
{
    EXEC_OK,
    EXEC_EXIT
};

int16_t * before_exec(int16_t operand, int16_t * R, char* mem, int16_t *pc);


int exec_command(int16_t* R, char* mem, int16_t* pc);

int decode_A_type(int16_t inst, int16_t *R, char *mem, int16_t *pc);
int decode_B_type(int16_t inst, int16_t *R, char *mem, int16_t *pc);
int decode_C_type(int16_t inst, int16_t *R, char *mem, int16_t *pc);
int decode_D_type(int16_t inst, int16_t *R, char *mem, int16_t *pc);
int decode_E_type(int16_t inst, int16_t *R, char *mem, int16_t *pc);
int decode_F_type(int16_t inst, int16_t *R, char *mem, int16_t *pc);

#endif //PDP11_DECODE_INST_H
