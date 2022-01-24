#include "../../incs/sha256.h"

static void retrieve_data(t_data *current_data, t_message_hash *msg)
{
    ft_bzero(msg, sizeof(t_message_hash));
    msg->raw_content = current_data->input;
    msg->rc_size = current_data->rc_size;
    msg->nofile = current_data->nofile;
    msg->src_type = current_data->src_type;
    msg->src = current_data->src;
}

static void clean_msg(t_message_hash *msg)
{
    if (msg->fmt_content)
        free(msg->fmt_content);
    if (msg->hash)
        free(msg->hash);
}

void        sha256(t_data *current_data, char *output)
{
    t_message_hash  msg;

    while (current_data)
    {
        retrieve_data(current_data, &msg);
        if (!msg.nofile)
        {
            format_msg(&msg, TRUE);
            process_msg_sha256(&msg);
        }
        if (args->algorithm == ALGO_SHA256)
            display_hash(&msg);
        else
            ft_memcpy(output, msg.hash, 64);
        clean_msg(&msg);
        current_data = current_data->next;
    }
}