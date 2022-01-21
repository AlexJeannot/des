#include "../../incs/des.h"

void    fatal_error(const char *reason)
{
    printf("ft_ssl: Fatal error: %s\n", reason);
    clean_data();
    clean_args();
    exit(1);
}

void    args_error(const char *reason, const char *input)
{
    if (input)
        printf("ft_ssl: Argument error: %s [%s]\n", reason, input);
    else
        printf("ft_ssl: Argument error: %s\n", reason);
    clean_data();
    clean_args();
    exit(1);
}