#ifndef PDP11_DECODE_INST_H
#define PDP11_DECODE_INST_H

enum opcode {
    MOV  = 0x0,
    ADD  = 0x6,
    HALT = 0x0
};


enum exec_command_status
{
    EXEC_OK,
    EXEC_EXIT
};

int exec_command(int16_t* R, char* mem, int16_t* pc);

int decode_A_type(int16_t inst, int16_t *R, char *mem, int16_t *pc);

#endif //PDP11_DECODE_INST_H
