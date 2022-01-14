#include "../../incs/sha256.h"

static void retrieve_data(t_data *current_data, t_message_hash *msg)
{
    bzero(msg, sizeof(t_message_hash));
    msg->raw_content = current_data->input;
    msg->rc_size = current_data->rc_size;
    msg->nofile = current_data->nofile;
    msg->src_type = current_data->src_type;
    msg->src = current_data->src;

}

void    sha256(void)
{
    t_data *tmp_data;
    t_message_hash msg;

    tmp_data = data;
    while (tmp_data)
    {
        retrieve_data(tmp_data, &msg);
        if (!msg.nofile)
        {
            format_msg(&msg, TRUE);
            process_msg_sha256(&msg);
        }
        display_hash(&msg);
        // clean_msg(msg);
        tmp_data = tmp_data->next;
    }
}