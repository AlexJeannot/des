#include "../../incs/base.h"

void    fatal_error(char *reason)
{
    ft_putstr_fd("ft_ssl: Fatal error: ", 2);
    ft_putstr_fd(reason, 2);
    ft_putstr_fd("\n", 2);
    clean_data();
    clean_args();
    exit(1);
}

void    args_error(char *reason, char *input)
{
    if (input)
    {
        ft_putstr_fd("ft_ssl: Argument error: ", 2);
        ft_putstr_fd(reason, 2);
        ft_putstr_fd(" [", 2);
        ft_putstr_fd(input, 2);
        ft_putstr_fd("]\n", 2);
    }
    else
    {
        ft_putstr_fd("ft_ssl: Argument error: ", 2);
        ft_putstr_fd(reason, 2);
        ft_putstr_fd("\n", 2);
    }
    display_help();
    clean_data();
    clean_args();
    exit(1);
}