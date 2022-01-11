#include "../../incs/des.h"

void permute(char *input, char *output, const u_int8_t *array, int size)
{
	for (int count = 0; count < size; count++)
		output[count] = input[array[count] - 1];
}

void xor_bits_string(char *first, char *second, char *output, u_int64_t size)
{
    for (u_int64_t count = 0; count < size; count++)
    {
        if (first[count] == second[count])
            output[count] = '0';
        else
            output[count] = '1';
    }
}