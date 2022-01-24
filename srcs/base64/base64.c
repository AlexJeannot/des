#include "../../incs/base64.h"

static void retrieve_data(t_data *data, t_message_base64 *msg)
{
    msg->raw_content = data->input;
    msg->rc_size = data->rc_size;
    args->output_fd = args->output_fd;
}

static void clean_msg(t_message_base64 *msg)
{
    if (msg->fmt_content)
        free(msg->fmt_content);
    if (msg->pc_content && args->algorithm == ALGO_BASE64)
        free(msg->pc_content);
}

void    base64(t_message_des *msg_des)
{
    t_message_base64 msg;

    ft_bzero(&msg, sizeof(t_message_base64));
    retrieve_data(data, &msg);
    if (args->process_type == ENCODING)
        process_encoding(&msg, msg_des, args);
    else
        process_decoding(&msg, msg_des, args);
    clean_msg(&msg);
}