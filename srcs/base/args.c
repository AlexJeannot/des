#include "../../incs/des.h"

u_int8_t    is_option(char *input)
{
    if (input && input[0] == '-')
        return (TRUE);
    return (FALSE);
}

void allocate_args(void)
{
    if (!(args = (t_args *)malloc(sizeof(t_args))))
        fatal_error("argument structure memory allocation");
    bzero(args, sizeof(t_args));
}


void process_io(char *file_path, u_int8_t type)
{
    t_data *new_data;

    new_data = NULL;
    if (!is_hash_algorithm() && type == INPUT && args->i == TRUE)
        args_error("Input file already provided", file_path);
    else if (!is_hash_algorithm() && type == OUTPUT && args->o == TRUE)
        args_error("OUTPUT file already provided", file_path);

    if (type == INPUT)
    {
        create_data(&new_data);
        get_file_content(new_data, get_file(file_path, INPUT));
        organize_data(new_data);
        args->i = TRUE;
    }
    else
    {
        args->output_fd = get_file(file_path, OUTPUT);
        args->o = TRUE;
    }
}

int32_t save_key(char *key, int32_t args_diff)
{
    if (args_diff < 2 || !(key))
        args_error("No hexadecimal key provided", NULL);

    if (args->k == TRUE)
        args_error("key hexadecimal already provided", NULL);

    if (!(is_hexadecimal(key)))
        args_error("Not a hexadecimal key provided", NULL);

    if (strlen(key) > 16)
        printf("Hexadecimal key is too long, ignoring excess\n");
    else if (strlen(key) > 16)
        printf("Hexadecimal key is too short, padding with zero bytes to length\n");

    strncpy(args->key, key, 16);

    args->k = TRUE;
    return (1);
}


void    get_algorithm(char *input)
{
    if (!input)
        args_error("No algorithm provided", NULL);

    if (strncmp(input, "des", 3) == 0)
        args->algorithm = ALGO_DES;
    else if (strncmp(input, "base64", 6) == 0)
        args->algorithm = ALGO_BASE64;
    else if (strncmp(input, "md5", 3) == 0)
        args->algorithm = ALGO_MD5;
    else if (strncmp(input, "sha256", 6) == 0)
        args->algorithm = ALGO_SHA256;
    else
        args_error("Wrong algorithm provided", input);
}

void        parse_args(char **list_args, int32_t nb_args)
{
    if (nb_args == 0)
        args_error("No arguments provided", NULL);

    get_algorithm(list_args[0]);

    for (int32_t index_args = 1; index_args < nb_args ; index_args++)
    {
        if (is_option(list_args[index_args]))
            index_args += parse_options(list_args[index_args], list_args[index_args + 1], (nb_args - index_args));
        else 
            args_error("Wrong option", list_args[index_args]);
    }

}

void format_args(void)
{
    if (!(args->process_type))
        args->process_type = EN;
    // add_output_fd(data, args);
    // strncpy(args->key, args->key, 16);
}

void        process_args(char **list_args, int32_t nb_args)
{
    allocate_args();
    parse_args(list_args, nb_args);
    format_args();
}