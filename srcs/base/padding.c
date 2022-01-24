#include "../../incs/base.h"

void    format_msg(t_message_hash *msg, const u_int8_t swap)
{
    msg->fc_size = msg->rc_size + 8 + (64 - ((msg->rc_size + 8) % 64));
    if (!(msg->fmt_content = (char *)malloc(msg->fc_size)))
        fatal_error("formated content memory allocation");
    ft_bzero(msg->fmt_content, msg->fc_size);

    ft_memcpy(msg->fmt_content, msg->raw_content, msg->rc_size);
    msg->fmt_content[msg->rc_size] = 0b10000000;

    if (swap == TRUE)
        *(u_int64_t *)&(msg->fmt_content[msg->fc_size - 8]) = swap_uint_64(msg->rc_size * 8);
    else
        *(u_int64_t *)&(msg->fmt_content[msg->fc_size - 8]) = msg->rc_size * 8;
}

void    add_padding(char *output, u_int64_t bytes, u_int64_t size)
{
    u_int8_t    count;
    u_int8_t    padding_value;

    count = 0;
    padding_value = size - bytes;
    for (; bytes < size; bytes++)
    {
        for (int8_t bits = 7; bits >= 0; bits--)
        {
            if (((padding_value >> bits) & 1) == 0)
                output[count] = '0';
            else if (((padding_value >> bits) & 1) == 1)
                output[count] = '1';
            count++;
        }
    }
}