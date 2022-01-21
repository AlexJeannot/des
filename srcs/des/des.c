#include "../../incs/des.h"

static void retrieve_data(t_message_des *msg, t_keys *keys)
{
    if (args->a && args->process_type == DECRYPTION)
        base64(msg);
    else
    {
        msg->raw_content = data->input;
        msg->rc_size = data->rc_size;
    }
    strncpy(keys->origin_key, args->key, 16);
    msg->output_fd = args->output_fd;

    if (args->process_type == ENCRYPTION)
    {
        msg->block_number = (msg->rc_size / 8) + 1;
        msg->is_last_block_empty = (msg->rc_size % 8 == 0) ? TRUE : FALSE;
        msg->fc_size = msg->rc_size + (8 - msg->rc_size);
    }
    else
        msg->block_number = (msg->rc_size % 8 == 0) ? (msg->rc_size / 8) : (msg->rc_size / 8)+ 1;
}

static void clean_msg(t_message_des *msg)
{
    if (msg->pc_content)
        free(msg->pc_content);
}

void        des(void)
{
    t_keys          keys;
    t_message_des   msg;
    t_block         block;

    bzero(&msg, sizeof(t_message_des));
    bzero(&keys, sizeof(t_keys));

    retrieve_data(&msg, &keys);
    prepare_output(&msg);
    create_all_round_keys(&keys, args->process_type);

    for (u_int64_t block_index = 0; block_index < msg.block_number; block_index++)
    {
        prepare_rounds(&msg, &block, block_index);
        for (u_int8_t round = 0; round < 16; round++)
            execute_round(&block, &keys, round);
        increment_output(args, &msg, &block, &msg.pc_content[block_index * 8], TRUE); //todo
    }
    write_output(data, args, &msg);
    clean_msg(&msg);
}