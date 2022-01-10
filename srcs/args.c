#include "../incs/des.h"

u_int8_t    is_option(char *input)
{
    if (input && input[0] == '-')
        return (TRUE);
    return (FALSE);
}

int32_t save_io(t_message *msg, t_args *args, char *file, int32_t args_diff, u_int8_t type)
{
    char *tmp_file;

    if (args_diff < 2 || !(file))
    {
        if (type == INPUT)
            args_error(msg, "No file provided as input", NULL);
        else
            args_error(msg, "No file provided as output", NULL);
    }

    if (!(tmp_file = (char *)malloc(strlen(file) + 1)))
        fatal_error(msg, "input/output filename memory allocation");
    bzero(tmp_file, strlen(file) + 1);
    strncpy(tmp_file, file, strlen(file));
     
    if (type == INPUT)
    {
        args->i = TRUE;
        args->input_path = tmp_file;
    }
    else
    {
        args->o = TRUE;
        args->output_path = tmp_file;
    }
    
    return (1);
}

int32_t     parse_options(t_message *msg, t_args *args, char *input, char *next_input, int32_t args_diff)
{
    if (!input)
        args_error(msg, "No option provided", NULL);
    else if (strlen(input) != 2)
        args_error(msg, "Wrong option provided", input);

    if (input[1] == 'd') {
        if (!(args->process_type))
            args->process_type = DECRYPTION;
        else if (args->process_type == DECRYPTION)
            args_error(msg, "Option provided twice", input);
        else if (args->process_type == ENCRYPTION)
            args_error(msg, "Encryption option already provided", input);
    }
    else if (input[1] == 'e') {
        if (!(args->process_type))
            args->process_type = ENCRYPTION;
        else if (args->process_type == ENCRYPTION)
            args_error(msg, "Option provided twice", input);
        else if (args->process_type == ENCRYPTION)
            args_error(msg, "Decryption option already provided", input);
    }
    // else if (input[1] == 'n') {
    //     if (args->n == TRUE)
    //         args_error(msg, "Option provided twice", input);
    //     args->n = TRUE;
    // }
    else if (input[1] == 'i')
        return (save_io(msg, args, next_input, args_diff, INPUT));
    else if (input[1] == 'o')
        return (save_io(msg, args, next_input, args_diff, OUTPUT));
    else
        args_error(msg, "Wrong option provided", input);

    return (0);
}

void        parse_args(t_args *args, t_message *msg, char **list_args, int32_t nb_args)
{
    for (int32_t index_args = 0; index_args < nb_args; index_args++)
    {
        if (is_option(list_args[index_args]))
            index_args += parse_options(msg, args, list_args[index_args], list_args[index_args + 1], (nb_args - index_args));
        else 
            args_error(msg, "Wrong option", list_args[index_args]);
    }

    if (!(args->process_type))
        args->process_type = ENCRYPTION;
    add_output_fd(args, msg);
}
