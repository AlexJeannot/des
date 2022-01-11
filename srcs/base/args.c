#include "../../incs/des.h"

u_int8_t    is_option(char *input)
{
    if (input && input[0] == '-')
        return (TRUE);
    return (FALSE);
}

int32_t save_io(t_args *args, char *file, int32_t args_diff, u_int8_t type)
{
    char *tmp_file;

    if (args_diff < 2 || !(file))
    {
        if (type == INPUT)
            args_error(args, "No file provided as input", NULL);
        else
            args_error(args, "No file provided as output", NULL);
    }

    if (!(tmp_file = (char *)malloc(strlen(file) + 1)))
        fatal_error(NULL, args, "input/output filename memory allocation");
    bzero(tmp_file, strlen(file) + 1);
    strncpy(tmp_file, file, strlen(file));
     
    if (type == INPUT)
    {
        if (args->i == TRUE)
        {
            free(tmp_file);
            args_error(args, "Input file already provided", file);
        }
        args->i = TRUE;
        args->input_path = tmp_file;
    }
    else
    {
        if (args->o == TRUE)
        {
            free(tmp_file);
            args_error(args, "Output file already provided", file);
        }
        args->o = TRUE;
        args->output_path = tmp_file;
    }
    
    return (1);
}

int32_t save_key(t_args *args, char *key, int32_t args_diff)
{
    (void)args;
    
    if (args_diff < 2 || !(key))
        args_error(args, "No hexadecimal key provided", NULL);

    if (args->k == TRUE)
        args_error(args, "key hexadecimal already provided", NULL);

    if (!(is_hexadecimal(key)))
        args_error(args, "Not a hexadecimal key provided", NULL);

    if (strlen(key) > 16)
        printf("Hexadecimal key is too long, ignoring excess\n");
    else if (strlen(key) > 16)
        printf("Hexadecimal key is too short, padding with zero bytes to length\n");

    strncpy(args->key, key, 16);

    args->k = TRUE;
    return (1);
}

int32_t     parse_options(t_args *args, char *input, char *next_input, int32_t args_diff)
{
    if (!input)
        args_error(args, "No option provided", NULL);
    else if (strlen(input) != 2)
        args_error(args, "Wrong option provided", input);

    if (input[1] == 'd') {
        if (!(args->process_type))
            args->process_type = DE;
        else if (args->process_type == DE)
            args_error(args, "Option provided twice", input);
        else if (args->process_type == EN)
            args_error(args, "Encryption option already provided", input);
    }
    else if (input[1] == 'e') {
        if (!(args->process_type))
            args->process_type = EN;
        else if (args->process_type == EN)
            args_error(args, "Option provided twice", input);
        else if (args->process_type == EN)
            args_error(args, "Decryption option already provided", input);
    }
    else if (input[1] == 'a') {
        if (args->a == TRUE)
            args_error(args, "Option provided twice", input);
        args->a = TRUE;
    }
    else if (input[1] == 'n') {
        if (args->n == TRUE)
            args_error(args, "Option provided twice", input);
        args->n = TRUE;
    }
    else if (input[1] == 'i')
        return (save_io(args, next_input, args_diff, INPUT));
    else if (input[1] == 'o')
        return (save_io(args, next_input, args_diff, OUTPUT));
    else if (input[1] == 'k')
        return (save_key(args, next_input, args_diff));
    else
        args_error(args, "Wrong option provided", input);

    return (0);
}

void    process_algorithm(t_args *args, char *input)
{
    if (!input)
        args_error(args, "No algorithm provided", NULL);
    
    if (strncmp(input, "des", 3) == 0)
        args->algorithm = ALGO_DES;
    else if (strncmp(input, "base64", 6) == 0)
        args->algorithm = ALGO_BASE64;
    else
        args_error(args, "Wrong algorithm provided", input);
}

void        parse_args(t_args *args, char **list_args, int32_t nb_args)
{
    if (nb_args == 0)
        args_error(args, "No arguments provided", NULL);

    process_algorithm(args, list_args[0]);

    for (int32_t index_args = 1; index_args < nb_args ; index_args++)
    {
        if (is_option(list_args[index_args]))
            index_args += parse_options(args, list_args[index_args], list_args[index_args + 1], (nb_args - index_args));
        else 
            args_error(args, "Wrong option", list_args[index_args]);
    }
}

void control_args(t_data *data, t_args *args)
{
    if (!(args->process_type))
        args->process_type = EN;
    add_output_fd(data, args);
    strncpy(data->key, args->key, 16);
}

void        process_args(t_data *data, t_args *args, char **list_args, int32_t nb_args)
{
    parse_args(args, list_args, nb_args);
    control_args(data, args);
}

