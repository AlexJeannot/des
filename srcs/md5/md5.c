#include "../../incs/md5.h"

static void retrieve_data(t_data *data, t_message_hash *msg)
{
    
}

void    md5(t_data *data)
{
    t_message_hash msg;

    bzero(&msg, sizeof(t_message_hash));

    retrieve_data(data, &msg);
    format_msg(msg, FALSE);
    process_msg_md5(msg);
}