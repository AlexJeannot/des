#include "../../incs/base.h"

void    ask_password(void)
{
    char    *first_input;
    char    *save_first_input;
    char    *second_input;

    if (!(first_input = getpass("Enter DES encryption password:")))
        fatal_error("user password request");

    if (!(save_first_input = (char *)malloc(strlen(first_input) + 1)))
        fatal_error("string input memory allocation");
    bzero(save_first_input, strlen(first_input) + 1);
    strncpy(save_first_input, first_input, strlen(first_input));

    if (!(second_input = getpass("Verification - enter DES encryption password:")))
        fatal_error("user password request");

    if (strncmp(save_first_input, second_input, 127) != 0)
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

    key->dkey.password_length = (strlen(input_password) < 127) ? strlen(input_password) : 127;

    if (key->dkey.password_length > 127)
        printf("Password is too long (> 127 characters), ignoring excess\n");
    else if (key->dkey.password_length < 32)
        printf("Password is too short, padding with zero bytes to length\n");

    if (!(key->dkey.password = (char *)malloc(key->dkey.password_length)))
        fatal_error("string input memory allocation");
    strncpy(key->dkey.password, input_password, key->dkey.password_length);
    args->p = TRUE;
}

void    create_salt(void)
{
    char        buf[8];
    int32_t     fd;
    ssize_t     ret;

    bzero(&buf[0], 8);
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
        args_error("Not a hexadecimal salt provided", NULL);

    if (!key)
        allocate_key();

    if (strlen(input_salt) > 16)
        printf("Salt is too long, ignoring excess\n");
    else if (strlen(input_salt) < 16)
        printf("Salt is too short, padding with zero bytes to length\n");

    strncpy(key->dkey.salt, input_salt, 16);
    args->s = TRUE;
}

void    allocate_key(void)
{
    if (!(key = (t_key *)malloc(sizeof(t_key))))
        fatal_error("argument structure memory allocation");
    bzero(key, sizeof(t_key));
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
        args_error("Not a hexadecimal key provided", NULL);

    if (!key)
        allocate_key();

    input_size = strlen(input_key);
    if (input_size > 16)
    {
        printf("Hexadecimal key is too long, ignoring excess\n");
        input_size = 16;
    }
    else if (input_size < 16)
        printf("Hexadecimal key is too short, padding with zero bytes to length\n");

    memset(args->key, 48, 16);
    strncpy(args->key, input_key, input_size);
    args->k = TRUE;
}