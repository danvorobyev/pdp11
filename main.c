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
//************LOADING INFORMATION**********
    if (load_inst(argv[1]) != EXIT_SUCCESS)
        return EXIT_FAILURE;

//******DECODE AND EXECUTE OPERATIONS******
    while (1)
    {
        int op_status = exec_command(R, mem, &pc);
        if (op_status == EXEC_EXIT)
            break;
    }
//**********PRINTING REGISTERS**************
    for(int i = 0; i < 7; i++)
        printf("R[%d] = %o\n",i, R[i]);
    printf("pc = %o\n", pc);

    return 0;

}