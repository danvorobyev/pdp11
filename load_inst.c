#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define N_mem 65536

extern char mem[N_mem];
extern int16_t R;

int load_inst (char* file, int16_t* R)
{
    FILE *f = NULL;

    f = fopen(file, "r");
    if (f == NULL)
    {
        perror(file);
        exit (1);
    }

    int start, len, i, j, sum;
    j = 0;
    while (fscanf (f, "%x%x", &start, &len) == 2)
    {
        sum = start + len;
        for (i = start; i < sum; i++)
        {
//            if (j == 0)
//            {
//                pc = (int16_t )(start);
//                j++;
//            }
            fscanf(f, "%x", &mem[i]);
            //printf("%02x\n", mem[i] & 0xff);
        }
    }
    R[7] = (int16_t )(start);
    //printf("pc = %o", pc);
    fclose(f);

    return EXIT_SUCCESS;
}