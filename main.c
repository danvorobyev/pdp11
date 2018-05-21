#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "load_inst.h"
#include "decode_inst.h"
#define slice(val, lsb, len) (((val) >> (lsb)) & ((1 << (len)) - 1))
#define N_mem 65536
#define WRITE 0177564

char mem[N_mem];
int16_t R[8];
int16_t psw;
FILE* f1;


int main(int argc, char * argv[])
{

//**************WRITING IN FILE***************

    f1 = fopen(argv[2], "w");
//    if (f1 == NULL)
//    {
//        perror("print.txt");
//        exit (1);
//    }
    mem[WRITE] = (char)0200;

//************LOADING INFORMATION*************

    if (load_inst(argv[1], R) != EXIT_SUCCESS)
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

    printf("r0 = %06o r2 = %06o r4 = %06o sp = %06o\n", (uint16_t)R[0], (uint16_t)R[2], (uint16_t)R[4], (uint16_t)R[6]);
    printf("r1 = %06o r3 = %06o r5 = %06o pc = %06o\n", (uint16_t)R[1], (uint16_t)R[3], (uint16_t)R[5], (uint16_t)R[7]);
    printf("psw = %06o\n", psw);
    fclose(f1);
    return 0;
}