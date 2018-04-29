#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern char mem[20000];
extern int16_t pc;

int load_inst (char * file)
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
    pc = (int16_t )(start);
    //printf("pc = %o", pc);
    fclose(f);

    return EXIT_SUCCESS;
}