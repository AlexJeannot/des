#include "../../incs/base64.h"

u_int8_t is_last_block(u_int64_t total_block, u_int64_t current_block)
{
    if (total_block == (current_block + 1))
        return (TRUE);
    return (FALSE);
}

static void retrieve_data(void *data, t_args *args, t_message_base64 *msg)
{
    if (args->algorithm == ALGO_DES)
    {
        msg->raw_content = ((t_message_des *)data)->input;
        msg->rc_size = ((t_message_des *)data)->rc_size;
        msg->output_fd = ((t_message_des *)data)->output_fd;
    }
    else
    {
        msg->raw_content = ((t_data *)data)->input;
        msg->rc_size = ((t_data *)data)->rc_size;
        msg->output_fd = ((t_data *)data)->output_fd;
    }
}

int base64(void *data, t_args *args)
{
    t_message_base64 msg;


    bzero(&msg, sizeof(t_message_base64));
    retrieve_data(data, args, &msg);
    if (args->process_type == ENCODING)
        process_encoding(&msg, args);
    else
        process_decoding(&msg, args);

    // clean_msg(&msg);

    return (0);
}