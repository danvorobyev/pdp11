#ifndef PDP11_DECODE_INST_H
#define PDP11_DECODE_INST_H

#define slice(val, lsb, len) (((val) >> (lsb)) & ((1 << (len)) - 1))

enum masks
{
    B_type = 0xF000,
    C_type = 0xFE00,
    D_type = 0xFF00,
    E_type = 0xFFC0,
    F_type = 0xFFF8
};

enum opcode
{
    ADC    = 0005500,
    ADCb   = 0105500,
    ADD    = 0060000,
    ASH    = 0072000,
    ASHC   = 0073000,
    ASL    = 0006300,
    ASLb   = 0106300,
    ASR    = 0006200,
    ASRb   = 0106200,
    BCC    = 0103000,
    BCS    = 0103400,
    BEQ    = 0001400,
    BGE    = 0002000,
    BGT    = 0003000,
    BIC    = 0040000,
    BICb   = 0140000,
    BIS    = 0050000,
    BISb   = 0150000,
    BIT    = 0030000,
    BITb   = 0130000,
    BHI    = 0101000,
    BLE    = 0003400,
    BLT    = 0002400,
    BLOS   = 0101400,
    BMI    = 0100400,
    BNE    = 0001000,
    BPL    = 0100000,
    BR     = 0000400,
    BVC    = 0102000,
    BVS    = 0102400,
    CCC    = 0000257,
    CLC    = 0000241,
    CLN    = 0000250,
    CLR    = 0005000,
    CLRb   = 0105000,
    CLV    = 0000242,
    CLZ    = 0000244,
    CMP    = 0020000,
    CMPb   = 0120000,
    COM    = 0005100,
    COMb   = 0105100,
    DEC    = 0005300,
    DECb   = 0105300,
    DIV    = 0071000,
    HALT   = 0000000,
    INC    = 0005200,
    INCb   = 0105200,
    JMP    = 0000100,
    JSR    = 0004000,
    MOV    = 0010000,
    MOVb   = 0110000,
    MUL    = 0070000,
    NEG    = 0005400,
    NEGb   = 0105400,
    NOP    = 0000240,
    RESET  = 0000005,
    ROL    = 0006100,
    ROLb   = 0106100,
    ROR    = 0006000,
    RORb   = 0106000,
    RTS    = 0000200,
    SBC    = 0005600,
    SBCb   = 0105600,
    SCC    = 0000277,
    SEC    = 0000261,
    SEN    = 0000270,
    SEV    = 0000262,
    SEZ    = 0000264,
    SOB    = 0077000,
    SUB    = 0160000,
    SWAB   = 0000300,
    SXT    = 0006700,
    TST    = 0005700,
    TSTb   = 0105700,
    XOR    = 0074000
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

char* exec(int16_t operand, int16_t * R, char* mem, int16_t *pc, int byteORword);
char* execjump(int16_t operand, int16_t * R, char* mem, int16_t *pc);


int exec_command(int16_t* R, char* mem, int16_t* pc, int16_t* psw);

int decode_A_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw);
int decode_B_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw);
int decode_C_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw);
int decode_D_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw);
int decode_E_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw);
int decode_F_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw);

#endif //PDP11_DECODE_INST_H
