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
    ADC    = 055,
    ADCb   = 01055,
    ADD    = 06,
    ASH    = 072,
    ASHC   = 073,
    ASL    = 063,
    ASLb   = 01063,
    ASR    = 062,
    ASRb   = 01062,
    BCC    = 01030,
    BCS    = 01034,
    BEQ    = 014,
    BGE    = 020,
    BGT    = 030,
    BIC    = 04,
    BICb   = 014,
    BIS    = 05,
    BISb   = 015,
    BIT    = 03,
    BITb   = 013,
    BHI    = 01010,
    BLE    = 034,
    BLT    = 024,
    BLOS   = 01014,
    BMI    = 01004,
    BNE    = 010,
    BPL    = 01000,
    BR     = 04,
    BVC    = 01020,
    BVS    = 01024,
    CALL   = 047,
    CCC    = 0257,
    CLC    = 0241,
    CLN    = 0250,
    CLR    = 050,
    CLRb   = 01050,
    CLV    = 0242,
    CLZ    = 0244,
    CMP    = 02,
    CMPb   = 012,
    COM    = 051,
    COMb   = 01051,
    DEC    = 053,
    DECb   = 01053,
    HALT   = 00,
    INC    = 052,
    INCb   = 01052,
    JMP    = 01,
    JSR    = 04,
    MOV    = 01,
    MOVb   = 011,
    NEG    = 054,
    NEGb   = 01054,
    NOP    = 0240,
    RESET  = 05,
    RETURN = 0207,
    ROL    = 061,
    ROLb   = 01061,
    ROR    = 060,
    RORb   = 01060,
    RTS    = 020,
    SBC    = 056,
    SBCb   = 01056,
    SCC    = 0277,
    SEC    = 0251,
    SEN    = 0270,
    SEV    = 0262,
    SEZ    = 0264,
    SOB    = 077,
    SUB    = 016,
    SWAB   = 03,
    SXT    = 067,
    TST    = 057,
    TSTb   = 01057,
    XOR    = 074
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


int exec_command(int16_t* R, char* mem, int16_t* pc, int16_t* psw);

int decode_A_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw);
int decode_B_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw);
int decode_C_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw);
int decode_D_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw);
int decode_E_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw);
int decode_F_type(int16_t inst, int16_t *R, char *mem, int16_t *pc, int16_t* psw);

#endif //PDP11_DECODE_INST_H
