#include "../../incs/base64.h"

/*
** DECODING UTILITY FUCNTIONS
*/

u_int8_t add_decoded_char(char encoded_char)
{
    u_int8_t bits;

    bits = '\0';
    if (encoded_char >= 'A' && encoded_char <= 'Z')
        bits = encoded_char - 65;
    else if (encoded_char >= 'a' && encoded_char <= 'z')
        bits = encoded_char - 71;
    else if (encoded_char >= '0' && encoded_char <= '9')
        bits = encoded_char + 4;
    else if (encoded_char == '+')
        bits = 62;
    else if (encoded_char == '/')
        bits = 63;
    else if (encoded_char == '=')
        bits = 0;

    return (bits);
}

void set_first_char(t_block *block, u_int8_t bits)
{
    block->a = (bits << 2);
}

void set_second_char(t_block *block, u_int8_t bits)
{
    block->a = (bits & 0b00110000) >> 4 | block->a;
    block->b = (bits & 0b00001111) << 4;
}

void set_third_char(t_block *block, u_int8_t bits)
{
    block->b = (bits & 0b00111100) >> 2 | block->b;
    block->c = (bits & 0b00000011) << 6;
}

void set_fourth_char(t_block *block, u_int8_t bits)
{
    block->c = bits | block->c;
}


/*
** DECODING MAIN FUCNTIONS
*/

void format_encoded_msg(t_message_base64 *msg)
{
    u_int64_t nl_size = 0;

    for (u_int64_t count = 0; count < msg->rc_size; count++)
    {
        if (msg->raw_content[count] == '\n')
            nl_size++;
    }

    msg->fc_size = msg->rc_size - nl_size;


    if (!(msg->fmt_content = (char *)malloc(msg->fc_size)))
        fatal_error("formated content memory allocation"); //TODO

    u_int64_t count_formated = 0;
    for (u_int64_t count = 0; count < msg->rc_size; count++)
    {
        if (msg->raw_content[count] != '\n')
        {
            msg->fmt_content[count_formated] = msg->raw_content[count];
            count_formated++;
        }
    }
}

void prepare_decoded_output(t_message_base64 *msg)
{
    msg->pc_size = msg->fc_size - (msg->fc_size / 4);
    msg->blocks_size = msg->pc_size / 3;

    if (!(msg->processed_content = (char *)malloc(msg->pc_size + 1)))
        fatal_error("Processed content memory allocation"); //TODO
    bzero(msg->processed_content, (msg->pc_size + 1));
}

void decode_msg_base64(t_message_base64 *msg)
{
    t_block *block;

    for (u_int64_t count = 0; count < msg->blocks_size; count++)
    {
        block = (t_block *)msg->processed_content + count;

        set_first_char(block, add_decoded_char(msg->fmt_content[count * 4]));
        set_second_char(block, add_decoded_char(msg->fmt_content[1 + count * 4]));
        set_third_char(block, add_decoded_char(msg->fmt_content[2 + count * 4]));
        set_fourth_char(block, add_decoded_char(msg->fmt_content[3 + count * 4]));

        if (is_last_block(msg->blocks_size, count))
        {
            if (!add_decoded_char(msg->fmt_content[2 + count * 4]))
                msg->pc_size--;
            if (!add_decoded_char(msg->fmt_content[3 + count * 4]))
                msg->pc_size--;
        }
    }
}

void write_decoded(t_message_base64 *msg)
{
    for (u_int64_t count = 0; count < msg->pc_size; count++)
        write(msg->output_fd, &msg->processed_content[count], 1);
}

void set_des_vars(t_message_base64 *msg, t_message_des *msg_des)
{
    msg_des->input = msg->processed_content;
    msg_des->rc_size = msg->pc_size;
}

void process_decoding(t_message_base64 *msg, t_message_des *msg_des, t_args *args)
{
    format_encoded_msg(msg);
    prepare_decoded_output(msg);
    decode_msg_base64(msg);
    if (args->algorithm == ALGO_DES)
        set_des_vars(msg, msg_des);
    else if (args->algorithm == ALGO_BASE64)
        write_decoded(msg);
}