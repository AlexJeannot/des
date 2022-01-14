#include "../../incs/des.h"

u_int8_t is_hexadecimal(char *input)
{
    u_int64_t size;

    size = (input) ? strlen(input) : 0;
    for (u_int64_t count = 0; count < size; count++)
    {
        if (input[count] < 48
            || (input[count] > 57 && input[count] < 65)
            || (input[count] > 70 && input[count] < 97)
            || input[count] > 102)
            return (FALSE);
    }
    return (TRUE);
}

u_int8_t base64_option(void)
{
    return (args->a);
}

u_int8_t is_stdin_process(void)
{
    if ((is_hash_algorithm() && args->p == TRUE) || data == NULL)
        return (TRUE);
    return (FALSE);
}

u_int8_t is_hash_algorithm(void)
{
    return (args->algorithm == ALGO_MD5 || args->algorithm == ALGO_SHA256);
}