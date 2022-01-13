#include "../../incs/des.h"

void control_option(char *option)
{
    if (args->algorithm == ALGO_MD5)
    {
        if (option[1] != 'p' && option[1] != 'q' && option[1] != 'r')
            args_error("Wrong option for MD5 algorithm", option);
    }
    else if (args->algorithm == ALGO_SHA256)
    {
        if (option[1] != 'p' && option[1] != 'q' && option[1] != 'r')
            args_error("Wrong option for SHA256 algorithm", option);
    }
    else if (args->algorithm == ALGO_BASE64)
    {
        if (option[1] != 'd' && option[1] != 'e' && option[1] != 'i' 
            && option[1] != 'n' && option[1] != 'o')
            args_error("Wrong option for BASE64 algorithm", option);
    }
    else if (args->algorithm == ALGO_DES)
    {
        if (option[1] != 'a' && option[1] != 'd' && option[1] != 'e'
            && option[1] != 'i' && option[1] != 'k' && option[1] != 'n'
            && option[1] != 'o' && option[1] != 'p' && option[1] != 's'
            && option[1] != 'v')
            args_error("Wrong option for DES algorithm", option);
    }
}

u_int8_t    control_option_value(char *input, int32_t diff)
{
    if (diff < 2 || !(input))
        return (FALSE);
    return (TRUE);
}

u_int8_t    process_a(void)
{
    control_option("-a");
    if (args->a == TRUE)
        args_error("Option provided twice", "-a");
    args->a = TRUE;
    return (0);
}

u_int8_t    process_d(void)
{
    control_option("-d");
    if (!(args->process_type))
        args->process_type = DE;
    else if (args->process_type == DE)
        args_error("Option provided twice", "-d");
    else if (args->process_type == EN)
        args_error("Encryption option already provided", "-d");
    return (0);
}

u_int8_t    process_e(void)
{
    control_option("-e");
    if (!(args->process_type))
        args->process_type = EN;
    else if (args->process_type == EN)
        args_error("Option provided twice", "-e");
    else if (args->process_type == DE)
        args_error("Decryption option already provided", "-e");
    return (0);
}

u_int8_t    process_i(char *input, int32_t diff)
{
    control_option("-i");
    if (!control_option_value(input, diff))
        args_error("No file provided as input", NULL);
    process_io(input, INPUT);
    return (1);
}

u_int8_t    process_k(char *input, int32_t diff)
{
    control_option("-k");
    if (!control_option_value(input, diff))
        args_error("No hexadecimal key provided", NULL);
    save_key(input, diff);
    return (1);
}

u_int8_t    process_n(void)
{
    control_option("-n");
    if (args->n == TRUE)
        args_error("Option provided twice", "-n");
    args->n = TRUE;
    return (0);
}

u_int8_t    process_o(char *input, int32_t diff)
{
    control_option("-o");
    if (!control_option_value(input, diff))
        args_error("No file provided as output", NULL);
    process_io(input, OUTPUT);
    return (1);
}

u_int8_t    process_p(char *input, int32_t diff)
{
    control_option("-p");

    (void)input;
    (void)diff;
    // if (!control_option_value(input, diff))
    //     args_error("No file provided as output", NULL);
    //TODO

    return (1);
}

u_int8_t    process_q(void)
{
    control_option("-q");
    if (args->q == TRUE)
        args_error("Option provided twice", "-q");
    args->q = TRUE;
    return (0);
}

u_int8_t    process_r(void)
{
    control_option("-r");
    if (args->r == TRUE)
        args_error("Option provided twice", "-r");
    args->r = TRUE;
    return (0);
}

u_int8_t    process_s(char *input, int32_t diff)
{
    control_option("-s");
    if (!control_option_value(input, diff))
        args_error("No string provided", NULL);
    // TODO
    return (1);
}

u_int8_t    process_v(void)
{
    control_option("-v");
    if (args->v == TRUE)
        args_error("Option provided twice", "-v");
    args->v = TRUE;
    // TODO
    return (0);
}

u_int8_t    parse_options(char *input, char *next_input, int32_t args_diff)
{
    if (!input)
        args_error("No option provided", NULL);
    else if (strlen(input) != 2)
        args_error("Wrong option provided", input);

    switch(input[1])
    {
        case ('a'): return(process_a()); break;
        case ('d'): return(process_d()); break;
        case ('e'): return(process_e()); break;
        case ('i'): return(process_i(next_input, args_diff)); break;
        case ('k'): return(process_k(next_input, args_diff)); break;
        case ('n'): return(process_n()); break;
        case ('o'): return(process_o(next_input, args_diff)); break;
        case ('p'): return(process_p(next_input, args_diff)); break;
        case ('q'): return(process_q()); break;
        case ('r'): return(process_r()); break;
        case ('s'): return(process_s(next_input, args_diff)); break;
        default:    args_error("Wrong option provided", input);
    }

    return (0);
}