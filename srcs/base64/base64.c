#include "../../incs/base64.h"

u_int8_t is_last_block(u_int64_t total_block, u_int64_t current_block)
{
    if (total_block == (current_block + 1))
        return (TRUE);
    return (FALSE);
}

int base64(t_message_base64 *msg_des, t_args *args)
{
    t_message_base64 msg_base64;
    (void)msg_des;

    bzero(&msg_base64, sizeof(t_message_base64));

    if (args->process_type == ENCODING)
        process_encoding(&msg_base64, args);
    else
        process_decoding(&msg_base64, args);

    // clean_msg(&msg);

    return (0);
}