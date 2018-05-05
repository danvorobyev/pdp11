#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "load_inst.h"
#include "decode_inst.h"
#define slice(val, lsb, len) (((val) >> (lsb)) & ((1 << (len)) - 1))
#define N_mem 65536
char mem[N_mem];
int16_t R[8];
int16_t psw;



int main(int argc, char * argv[])
{

    mem[65396] = (char)0200;
//************LOADING INFORMATION*************

    if (load_inst(argv[1], &R) != EXIT_SUCCESS)
        return EXIT_FAILURE;

//******DECODE AND EXECUTE OPERATIONS*********

    printf("\n---------------- running --------------\n");
    while (1)
    {
        int op_status = exec_command(R, mem, &R[7], &psw);
        if (op_status == EXEC_EXIT)
            break;
    }

//**********PRINTING REGISTERS****************

    printf("r0 = %06o r2 = %06o r4 = %06o sp = %06o\n", R[0], (int8_t)R[2], R[4], R[6]);
    printf("r1 = %06o r3 = %06o r5 = %06o pc = %06o\n", R[1], R[3], R[5], R[7]);
    printf("\npsw = %o", psw);

    return 0;


}