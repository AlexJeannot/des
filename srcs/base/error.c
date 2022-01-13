#include "../../incs/des.h"

// void        clean_msg(t_message *msg)
// {
//     if (msg->input)
//         free(msg->input);
// }

void        clean_data(void)
{
    if (!data)
        return ;
    if (data->input)
        free(data->input);
}

void        clean_args(void)
{
    if (!args)
        return ;
    if (args->input_path)
        free(args->input_path);
    if (args->output_path)
        free(args->output_path);
}

void    fatal_error(const char *reason)
{
    printf("Error: %s\n", reason);
    clean_data();
    clean_args();
    exit(1);
}

void    args_error(const char *reason, const char *input)
{
    if (input)
        printf("Error: %s [%s]\n", reason, input);
    else
        printf("Error: %s\n", reason);
    clean_args();
    exit(1);
}