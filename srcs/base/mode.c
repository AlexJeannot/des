#include "../../incs/des.h"

void    get_initial_vector(char *input_iv)
{
    u_int64_t   input_size;

    if (!(is_hexadecimal(input_iv)))
        args_error("not a hexadecimal initialization vector provided", NULL);

    input_size = strlen(input_iv);
    if (input_size > 16)
    {
        printf("Initialization vector is too long, ignoring excess\n");
        input_size = 16;
    }
    else if (input_size < 16)
        printf("Initialization vector is too short, padding with zero bytes to length\n");
    
    memset(args->iv, 48, 16);
    strncpy(args->iv, input_iv, input_size);
    args->v = TRUE;
}

void    create_initial_vector(void)
{
    char        buf[8];
    int32_t     fd;
    ssize_t     ret;

    bzero(&buf[0], 8);
    if ((fd = open("/dev/urandom", O_RDONLY)) == -1)
        fatal_error("random file opening");
    if ((ret = read(fd, buf, 8)) == -1)
        fatal_error("random file reading");
    str_to_hex_str(buf, args->iv, 8);
    args->v = TRUE;
}

void    get_operation_mode(char *input)
{
    if (input[0] && input[0] == '-')
    {
        if (input[1] && strncmp(&input[1], "ecb", 3) == 0)
            args->mode = MODE_ECB;
        else if (input[1] && strncmp(&input[1], "cbc", 3) == 0)
            args->mode = MODE_CBC;
    }
    if (args->mode == FALSE)
        args_error("wrong operation mode provided", input);
}

void    xor_plaintext(char *input, char *cmp, u_int64_t block_index)
{
    char first_xor[64];

    bzero(first_xor, 64);
    if (block_index == 0)
    {
        hex_str_to_bin_str(args->iv, &first_xor[0], 16);
        xor_bits_string(input, &first_xor[0], input, 64);
    }
    else
        xor_bits_string(input, cmp, input, 64);
}
