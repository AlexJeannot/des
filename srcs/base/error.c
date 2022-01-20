#include "../../incs/des.h"

void    fatal_error(const char *reason)
{
    printf("Error: %s\n", reason);
    clean_data();
    clean_args();
    exit(1);
}

void    args_error(const char *reason, const char *input)
{
    if (input)
        printf("Error: %s [%s]\n", reason, input);
    else
        printf("Error: %s\n", reason);
    clean_args();
    exit(1);
}