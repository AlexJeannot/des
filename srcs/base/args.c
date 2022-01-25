#include "../../incs/base.h"

u_int8_t    is_option(char *input)
{
    if (input && input[0] == '-')
        return (TRUE);
    return (FALSE);
}

void        allocate_args(void)
{
    if (!(args = (t_args *)malloc(sizeof(t_args))))
        fatal_error("argument structure memory allocation");
    bzero(args, sizeof(t_args));
}

void        clean_args(void)
{
    if (args)
        free(args);
    close(args->output_fd);
}

void        get_algorithm(char *input)
{
    if (!input)
        args_error("no algorithm provided", NULL);

    if (strncmp(input, "des", 3) == 0)
    {
        args->algorithm = ALGO_DES;
        get_operation_mode(&input[3]);
    }
    else if (strncmp(input, "base64", 6) == 0)
        args->algorithm = ALGO_BASE64;
    else if (strncmp(input, "md5", 3) == 0)
        args->algorithm = ALGO_MD5;
    else if (strncmp(input, "sha256", 6) == 0)
        args->algorithm = ALGO_SHA256;
    else
        args_error("wrong algorithm provided", input);
}

void        parse_args(char **list_args, int32_t nb_args)
{
    int32_t index_args;

    if (nb_args == 0)
        args_error("no arguments provided", NULL);

    index_args = 0;
    get_algorithm(list_args[index_args]);
    for (index_args = 1; index_args < nb_args ; index_args++)
    {
        if (is_option(list_args[index_args]))
            index_args += parse_options(list_args[index_args], list_args[index_args + 1], (nb_args - index_args));
        else if (is_hash_algorithm())
            break;
        else
            args_error("wrong option", list_args[index_args]);
    }
    if (is_hash_algorithm())
    {
        for (; index_args < nb_args; index_args++)
                process_file(list_args[index_args], INPUT);
    }
}

void        format_args(void)
{
    if (!(args->process_type))
        args->process_type = EN;

    if (args->algorithm == ALGO_DES && args->k == FALSE)
    {
        if (args->p == FALSE)
            ask_password();
        if (args->s == FALSE)
            create_salt();
        pbkdf2(8, 32, 310000);
    }

    if (args->algorithm == ALGO_DES && args->mode == MODE_CBC && args->v == FALSE)
        create_initial_vector();

    if (is_stdin_process())
        process_stdin();
}

void        process_args(char **list_args, int32_t nb_args)
{
    allocate_args();
    parse_args(list_args, nb_args);
    format_args();
}