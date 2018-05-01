#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "load_inst.h"
#include "decode_inst.h"
#define slice(val, lsb, len) (((val) >> (lsb)) & ((1 << (len)) - 1))
#define N_mem 20000

char mem[N_mem];
int16_t R[7];
int16_t pc;
int16_t psw;


int main(int argc, char * argv[])
{

//************LOADING INFORMATION**********
    if (load_inst(argv[1]) != EXIT_SUCCESS)
        return EXIT_FAILURE;

//******DECODE AND EXECUTE OPERATIONS******
    while (1)
    {
        int op_status = exec_command(R, mem, &pc, &psw);
        if (op_status == EXEC_EXIT)
            break;
    }
//**********PRINTING REGISTERS**************
    for(int i = 0; i < 7; i++)
        printf("R[%d] = %o\n",i, R[i]);
    printf("pc = %o\n", pc);
    
//    int16_t op1 = -32768;
//    int16_t op2 = -1;
//
//
//    int16_t sign_op1 = ((op1) >> 15) & (int16_t)0x1;
//    int16_t sign_op2 = ((op2) >> 15) & (int16_t)0x1;
//
//    op2 = op1 + op2;
//
//    int16_t sign_sum = ((op2) >> 15) & (int16_t)0x1;
//
//    printf("sign_op1 = %x; sign_op2 = %x; sign_sum = %x; \n", sign_op1, sign_op2, sign_sum);
//
//    printf("%x\n",(sign_op1 ^ sign_op2) | ((sign_op1 + sign_sum) & 0x1) ^ 0x1);

    return 0;

}