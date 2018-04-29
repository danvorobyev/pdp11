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

//    int16_t inst = *(int16_t*)(mem + pc);
//    printf("%x\n", inst);
//    int kek = slice(inst, 12, 4);
//    printf("%x\n", kek);
    return 0;

}