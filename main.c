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

int main(int argc, char * argv[])
{
    if (load_inst(argv[1]) != EXIT_SUCCESS)
        return EXIT_FAILURE;


    while (1)
    {
        int op_status = exec_command(R, mem, &pc);
        if (op_status == EXEC_EXIT)
            break;
    }

//    printf("%o\n", R[0]);
//    printf("%o\n", R[1]);
//    int16_t buf1 = 0x1;
//    int16_t buf2 = 0x2;
//    int16_t* x;
//    int16_t* y;
//    x = &buf1;
//    y = &buf2;
//
//    x = y;
//
//    printf("%x\n", *x);

//    int16_t inst = 0x28;
//    printf("%x\n", inst);
//    int kek = slice(inst, 0, 3);
//    printf("%x\n", kek);
    return 0;

}