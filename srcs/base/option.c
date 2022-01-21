#include "../../incs/base.h"

void        control_option(char *option)
{
    if (args->algorithm == ALGO_MD5)
    {
        if (option[1] != 'p' && option[1] != 'q' && option[1] != 'r'
            && option[1] != 's')
            args_error("wrong option for MD5 algorithm", option);
    }
    else if (args->algorithm == ALGO_SHA256)
    {
        if (option[1] != 'p' && option[1] != 'q' && option[1] != 'r'
            && option[1] != 's')
            args_error("wrong option for SHA256 algorithm", option);
    }
    else if (args->algorithm == ALGO_BASE64)
    {
        if (option[1] != 'd' && option[1] != 'e' && option[1] != 'i' 
            && option[1] != 'n' && option[1] != 'o')
            args_error("wrong option for BASE64 algorithm", option);
    }
    else if (args->algorithm == ALGO_DES)
    {
        if (option[1] != 'a' && option[1] != 'd' && option[1] != 'e'
            && option[1] != 'i' && option[1] != 'k' && option[1] != 'n'
            && option[1] != 'o' && option[1] != 'p' && option[1] != 's'
            && option[1] != 'v')
            args_error("wrong option for DES algorithm", option);
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
        args_error("option provided twice", "-a");
    args->a = TRUE;
    return (0);
}

u_int8_t    process_d(void)
{
    control_option("-d");
    if (!(args->process_type))
        args->process_type = DE;
    else if (args->process_type == DE)
        args_error("option provided twice", "-d");
    else if (args->process_type == EN)
        args_error("encryption option already provided", "-d");
    return (0);
}

u_int8_t    process_e(void)
{
    control_option("-e");
    if (!(args->process_type))
        args->process_type = EN;
    else if (args->process_type == EN)
        args_error("option provided twice", "-e");
    else if (args->process_type == DE)
        args_error("decryption option already provided", "-e");
    return (0);
}

u_int8_t    process_i(char *input, int32_t diff)
{
    control_option("-i");
    if (!control_option_value(input, diff))
        args_error("no file provided as input", NULL);
    if (!is_hash_algorithm() && args->i == TRUE)
        args_error("input file already provided", input);
    process_file(input, INPUT);
    return (1);
}

u_int8_t    process_k(char *input, int32_t diff)
{
    control_option("-k");
    if (!control_option_value(input, diff))
        args_error("no hexadecimal key provided", NULL);
    if (args->k == TRUE)
        args_error("key hexadecimal already provided", NULL);
    get_key(input);
    return (1);
}

u_int8_t    process_n(void)
{
    control_option("-n");
    if (args->n == TRUE)
        args_error("option provided twice", "-n");
    args->n = TRUE;
    return (0);
}

u_int8_t    process_o(char *input, int32_t diff)
{
    control_option("-o");
    if (!control_option_value(input, diff))
        args_error("no file provided as output", NULL);
    if (!is_hash_algorithm() && args->o == TRUE)
        args_error("output file already provided", input);
    process_file(input, OUTPUT);
    return (1);
}

u_int8_t    process_p(char *input, int32_t diff)
{
    control_option("-p");
    if (is_hash_algorithm())
    {
        if (args->p == TRUE)
            args_error("option provided twice", "-p");
        args->p = TRUE;
    }
    else
    {
        if (!control_option_value(input, diff))
            args_error("no password provided", NULL);
        if (args->p == TRUE)
            args_error("password already provided", NULL);
        get_password(input);
        return (1);
    }
    return (0);
}

u_int8_t    process_q(void)
{
    control_option("-q");
    if (args->q == TRUE)
        args_error("option provided twice", "-q");
    args->q = TRUE;
    return (0);
}

u_int8_t    process_r(void)
{
    control_option("-r");
    if (args->r == TRUE)
        args_error("option provided twice", "-r");
    args->r = TRUE;
    return (0);
}

u_int8_t    process_s(char *input, int32_t diff)
{
    control_option("-s");
    if (is_hash_algorithm())
    {
        if (!control_option_value(input, diff))
            args_error("no string provided", NULL);
        process_string(input);
    }
    else
    {
        if (!control_option_value(input, diff))
            args_error("no salt provided", NULL);
        if (args->s == TRUE)
            args_error("salt already provided", NULL);
        get_salt(input);
    }
    return (1);
}

u_int8_t    process_v(char *input, int32_t diff)
{
    control_option("-v");
    if (!control_option_value(input, diff))
        args_error("no string provided", NULL);
    if (args->v == TRUE)
        args_error("option provided twice", "-v");
    get_initial_vector(input);
    return (1);
}

u_int8_t    parse_options(char *input, char *next_input, int32_t args_diff)
{
    if (!input)
        args_error("no option provided", NULL);
    else if (strlen(input) != 2)
        args_error("wrong option provided", input);

    switch(input[1])
    {
        case ('a'): return(process_a());                        break;
        case ('d'): return(process_d());                        break;
        case ('e'): return(process_e());                        break;
        case ('i'): return(process_i(next_input, args_diff));   break;
        case ('k'): return(process_k(next_input, args_diff));   break;
        case ('n'): return(process_n());                        break;
        case ('o'): return(process_o(next_input, args_diff));   break;
        case ('p'): return(process_p(next_input, args_diff));   break;
        case ('q'): return(process_q());                        break;
        case ('r'): return(process_r());                        break;
        case ('s'): return(process_s(next_input, args_diff));   break;
        case ('v'): return(process_v(next_input, args_diff));   break;
        default:    args_error("wrong option provided", input);
    }
    return (0);
}
