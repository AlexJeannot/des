#include "../../incs/base.h"

void    format_msg(t_message_hash *msg, const u_int8_t swap)
{
    msg->fc_size = msg->rc_size + 8 + (64 - ((msg->rc_size + 8) % 64));
    if (!(msg->fmt_content = (char *)malloc(msg->fc_size)))
        fatal_error("formated content memory allocation");
    bzero(msg->fmt_content, msg->fc_size);

    memcpy(msg->fmt_content, msg->raw_content, msg->rc_size);
    msg->fmt_content[msg->rc_size] = 0b10000000;

    if (swap == TRUE)
        *(u_int64_t *)&(msg->fmt_content[msg->fc_size - 8]) = swap_uint_64(msg->rc_size * 8);
    else
        *(u_int64_t *)&(msg->fmt_content[msg->fc_size - 8]) = msg->rc_size * 8;
}