#include "../../incs/base64.h"

/*
** ENCODING UTILITY FUNCTIONS
*/

void add_encoded_char(t_message_base64 *msg, u_int8_t nb)
{
    char encoded_char;

    encoded_char = '\0';
    if (nb <= 25)
        encoded_char = 'A' + nb;
    else if (nb > 25 && nb <= 51)
        encoded_char = 'a' + (nb - 26);
    else if (nb > 51 && nb <= 61)
        encoded_char = '0' + (nb - 52);
    else if (nb == 62)
        encoded_char = '+';
    else if (nb == 63)
        encoded_char = '/';

    msg->processed_content[msg->cc_size++] = encoded_char;
}

void add_complement(t_message_base64 *msg)
{
    msg->processed_content[msg->cc_size++] = '=';
}

u_int8_t get_first_char(t_block *block)
{
    return ((block->a & 0b11111100) >> 2);
}

u_int8_t get_second_char(t_block *block)
{
    return (((block->a & 0b00000011) << 4) | ((block->b & 0b11110000) >> 4));
}

u_int8_t get_third_char(t_block *block)
{
    return (((block->b & 0b00001111) << 2) | ((block->c & 0b11000000) >> 6));
}

u_int8_t get_fourth_char(t_block *block)
{
    return (block->c & 0b00111111);
}


/*
** ENCODING MAIN FUCNTIONS
*/

void format_decoded_msg(t_message_base64 *msg)
{
    msg->fc_size = (!(msg->rc_size % 3)) ? msg->rc_size : msg->rc_size + (3 - (msg->rc_size % 3));

    if (msg->rc_size == msg->fc_size)
        msg->fmt_content = msg->raw_content;
    else {
        if (!(msg->fmt_content = (char *)malloc(msg->fc_size)))
            fatal_error(NULL, NULL, "formated content memory allocation"); //TODO
        
        bzero(msg->fmt_content, msg->fc_size);
        memcpy(msg->fmt_content, msg->raw_content, msg->rc_size);
    }
}

void prepare_encoded_output(t_message_base64 *msg)
{
    msg->pc_size = msg->fc_size + (msg->fc_size / 3);
    msg->blocks_size = msg->fc_size / 3;

    if (!(msg->processed_content = (char *)malloc(msg->pc_size + 1)))
        fatal_error(NULL, NULL, "Processed content memory allocation"); //TODO
    bzero(msg->processed_content, (msg->pc_size + 1));
}

void encode_msg_base64(t_message_base64 *msg)
{
    t_block *block;

    for (u_int64_t count = 0; count < msg->blocks_size; count++)
    {
        block = (t_block *)msg->fmt_content + count;

        add_encoded_char(msg, get_first_char(block));
        add_encoded_char(msg, get_second_char(block));
        if (is_last_block(msg->blocks_size, count)) {
            if (!get_third_char(block))
                add_complement(msg);
            else
                add_encoded_char(msg, get_third_char(block));

            if (!get_fourth_char(block))
                add_complement(msg);
            else
                add_encoded_char(msg, get_fourth_char(block));
        }
        else
        {
            add_encoded_char(msg, get_third_char(block));
            add_encoded_char(msg, get_fourth_char(block));
        }
    }
}

void write_encoded(t_message_base64 *msg, t_args *args)
{
    u_int64_t count = 0;
    int32_t fd;

    if (args->o == TRUE)
        fd = get_file(args, OUTPUT);
    else
        fd = 1;

    for (; count < msg->pc_size; count++)
    {
        write(fd, &msg->processed_content[count], 1);
        if (args->n == TRUE && count != 0 && (count + 1) % 64 == 0)
            write(fd, "\n", 1);
    }
    if (args->n == FALSE || (count + 1) % 64 != 0)
        write(fd, "\n", 1);
}

void process_encoding(t_message_base64 *msg, t_args *args)
{
    (void)args;
    format_decoded_msg(msg);
    prepare_encoded_output(msg);
    encode_msg_base64(msg);
    // write_encoded(msg, args);
}