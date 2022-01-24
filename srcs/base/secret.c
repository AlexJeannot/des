#include "../../incs/base.h"

void    ask_password(void)
{
    char    *first_input;
    char    *save_first_input;
    char    *second_input;

    if (!(first_input = getpass("Enter DES encryption password:")))
        fatal_error("user password request");

    if (!(save_first_input = (char *)malloc(ft_strlen(first_input) + 1)))
        fatal_error("string input memory allocation");
    ft_bzero(save_first_input, ft_strlen(first_input) + 1);
    ft_memcpy(save_first_input, first_input, ft_strlen(first_input));

    if (!(second_input = getpass("Verification - enter DES encryption password:")))
        fatal_error("user password request");

    if (ft_strncmp(save_first_input, second_input, 127) != 0)
    {
        free(save_first_input);
        fatal_error("password verification failure");
    }

    get_password(save_first_input);
    free(save_first_input);
}

void    get_password(char *input_password)
{
    if (!key)
        allocate_key();

    key->dkey.password_length = (ft_strlen(input_password) < 127) ? ft_strlen(input_password) : 127;

    if (key->dkey.password_length > 127)
        ft_putstr_fd("Password is too long (> 127 characters), ignoring excess\n", 1);
    else if (key->dkey.password_length < 32)
        ft_putstr_fd("Password is too short, padding with zero bytes to length\n", 1);

    if (!(key->dkey.password = (char *)malloc(key->dkey.password_length)))
        fatal_error("string input memory allocation");
    ft_memcpy(key->dkey.password, input_password, key->dkey.password_length);
    args->p = TRUE;
}

void    create_salt(void)
{
    char        buf[8];
    int32_t     fd;
    ssize_t     ret;

    ft_bzero(&buf[0], 8);
    if ((fd = open("/dev/urandom", O_RDONLY)) == -1)
        fatal_error("random file opening");
    if ((ret = read(fd, buf, 8)) == -1)
        fatal_error("random file reading");
    str_to_hex_str(buf, key->dkey.salt, 8);
    args->s = TRUE;
}

void    get_salt(char *input_salt)
{
    if (!(is_hexadecimal(input_salt)))
        args_error("not a hexadecimal salt provided", NULL);

    if (!key)
        allocate_key();

    if (ft_strlen(input_salt) > 16)
        ft_putstr_fd("Salt is too long, ignoring excess\n", 1);
    else if (ft_strlen(input_salt) < 16)
        ft_putstr_fd("Salt is too short, padding with zero bytes to length\n", 1);

    ft_memcpy(key->dkey.salt, input_salt, 16);
    args->s = TRUE;
}

void    allocate_key(void)
{
    if (!(key = (t_key *)malloc(sizeof(t_key))))
        fatal_error("argument structure memory allocation");
    ft_bzero(key, sizeof(t_key));
}

void    clean_key(void)
{
    if (key->dkey.password)
        free(key->dkey.password);
    free(key);
}

void    get_key(char *input_key)
{
    u_int64_t   input_size;

    if (!(is_hexadecimal(input_key)))
        args_error("not a hexadecimal key provided", NULL);

    if (!key)
        allocate_key();

    input_size = ft_strlen(input_key);
    if (input_size > 16)
    {
        ft_putstr_fd("Hexadecimal key is too long, ignoring excess\n", 1);
        input_size = 16;
    }
    else if (input_size < 16)
        ft_putstr_fd("Hexadecimal key is too short, padding with zero bytes to length\n", 1);

    ft_memset(args->key, 48, 16);
    ft_memcpy(args->key, input_key, input_size);
    args->k = TRUE;
}