#include "../../incs/base64.h"

u_int8_t is_last_block(u_int64_t total_block, u_int64_t current_block)
{
    if (total_block == (current_block + 1))
        return (TRUE);
    return (FALSE);
}

static void retrieve_data(t_data *data, t_message_base64 *msg)
{
    msg->raw_content = data->input;
    msg->rc_size = data->rc_size;
    msg->output_fd = data->output_fd;
}

void base64(t_data *data, t_args *args, t_message_des *msg_des)
{
    t_message_base64 msg;


    bzero(&msg, sizeof(t_message_base64));
    retrieve_data(data, &msg);
    if (args->process_type == ENCODING)
        process_encoding(&msg, msg_des, args);
    else
        process_decoding(&msg, msg_des, args);

    // clean_msg(&msg);

}