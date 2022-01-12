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

u_int8_t base64_option(t_args *args)
{
    return (args->a);
}