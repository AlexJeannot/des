#include "../../incs/base.h"

void binary_str_to_str(char *binary_str, char *str)
{
    u_int64_t size;

    size = strlen(binary_str) / 8;
    for (int bytes = 0; bytes < size; bytes++)
    {
        for (int bits = 0; bits < 8; bits++)
        {
            str[bytes] = str[bytes] << 1;
            str[bytes] = str[bytes] | (binary_str[(bytes * 8) + bits] - 48);
        }
    }
}