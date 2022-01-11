#include "../../incs/des.h"

void print_binary_str(char *str, char *type, int size)
{
    printf("%s = ", type);
    fflush(stdout);
    write(1, str, size);
    printf("\n");
}

void increment_output(t_block *block, char *output)
{
    strncpy(&block->processed[0], &block->left[0], 32);
    strncpy(&block->processed[32], &block->right[0], 32);
    permute(&block->processed[0], &block->permuted[0], &final_permutation[0], 64);

    for (int bytes = 0; bytes < 8; bytes++)
    {
        for (int bits = 0; bits < 8; bits++)
        {
            output[bytes] = output[bytes] << 1;
            output[bytes] = output[bytes] | (block->permuted[(bytes * 8) + bits] - 48);
        }
    }
}

void write_output(t_message_des *msg)
{
    if (write(msg->output_fd, &msg->output[0], 8) == -1)
        fatal_error(NULL, NULL, "Output writing on file descriptor"); //TODO
}

static void retrieve_data(t_data *data, t_message_des *msg, t_keys *keys)
{
    strncpy(keys->origin_key, data->key, 16);
    msg->input = data->input;
    msg->rc_size = data->rc_size;
    msg->output_fd = msg->output_fd;
}

void des(t_data *data, t_args *args)
{
    t_keys keys;
    t_message_des msg;
    t_block block;

    bzero(&msg, sizeof(t_message_des));
    bzero(&keys, sizeof(t_keys));


    retrieve_data(data, &msg, &keys);
    create_all_round_keys(&keys, args->process_type);

    if (args->a && args->process_type == DECRYPTION)
    {
        base64(&msg, args);
        free(msg.input);
        msg.input = msg.base64_processed;
        msg.rc_size = msg.base64_size;
    }

    for (u_int64_t block_index = 0; block_index < 1; block_index++)
    {
        prepare_rounds(&msg, &block);
        for (u_int8_t round = 0; round < 16; round++)
            execute_round(&block, &keys, round);
        increment_output(&block, msg.output);
        write_output(&msg);
    }

    printf("\n");
    // clean_msg(&msg);
}