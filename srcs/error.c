#include "../incs/des.h"

void        clean_msg(t_message *msg)
{
    if (msg->input)
        free(msg->input);
}

void    fatal_error(t_message *msg, const char *reason)
{
    printf("Error: %s\n", reason);
    clean_msg(msg);
    exit(1);
}

void    args_error(t_message *msg, const char *reason, const char *input)
{
    if (input)
        printf("Error: %s [%s]\n", reason, input);
    else
        printf("Error: %s\n", reason);
    clean_msg(msg);
    exit(1);
}