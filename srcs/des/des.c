#include "../../incs/des.h"

void print_binary_str(char *str, char *type, int size)
{
    printf("%s = ", type);
    fflush(stdout);
    int bytes = size / 8;
    for (int count = 0; count < bytes; count++) {

        write(1, &str[count * 8], 8);
        write(1, " ", 1);

    }
    printf("\n");
}

u_int8_t    is_block_padded(char *input)
{
    u_int8_t padding;

    padding = 0;
    for (u_int8_t bytes = 0; bytes < 8; bytes++)
    {
        if ((u_int8_t)input[bytes] == (8 - bytes))
        {
            for (u_int8_t cmp = bytes; cmp < 8; cmp++)
            {
                if ((u_int8_t)input[cmp] != (8 - bytes))
                {
                    padding = 0;
                    break ;
                }
                padding++;
            }
        }
    }

    return (padding);
}

void increment_output(t_args *args, t_message_des *msg, t_block *block, char *output, u_int8_t is_last_block)
{
    u_int8_t padding;

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

    padding = (is_last_block && args->process_type == DECRYPTION) ? is_block_padded(output) : 0;
    msg->pc_size += (8 - padding);
}

void write_output(t_data *data, t_args *args, t_message_des *msg)
{
    if (base64_option())
    {
        free(data->input);
        data->input = msg->output;
        data->rc_size = msg->pc_size;
        base64(msg);
    }

    if (write(msg->output_fd, &msg->output[0], msg->pc_size) == -1)
        fatal_error("Output writing on file descriptor"); //TODO
    if (base64_option() && args->process_type == ENCRYPTION)
        if (write(msg->output_fd, "\n", 1) == -1)
            fatal_error("Output writing on file descriptor"); //TODO
}

static void retrieve_data(t_message_des *msg, t_keys *keys)
{
    if (args->a && args->process_type == DECRYPTION)
        base64(msg);
    else
    {
        msg->input = data->input;
        msg->rc_size = data->rc_size;
    }
    strncpy(keys->origin_key, args->key, 16);
    msg->output_fd = args->output_fd;
    msg->block_number = (msg->rc_size % 8 == 0) ? msg->rc_size / 8 : (msg->rc_size / 8) + 1;
}

void prepare_output(t_message_des *msg)
{
    if (!(msg->output = (char *)malloc(msg->rc_size)))
        fatal_error("Processed content memory allocation");
}

void des(void)
{
    t_keys keys;
    t_message_des msg;
    t_block block;

    bzero(&msg, sizeof(t_message_des));
    bzero(&keys, sizeof(t_keys));

    retrieve_data(&msg, &keys);
    prepare_output(&msg);
    create_all_round_keys(&keys, args->process_type);

    for (u_int64_t block_index = 0; block_index < msg.block_number; block_index++)
    {
        prepare_rounds(&msg, &block, &msg.input[block_index * 8]);
        for (u_int8_t round = 0; round < 16; round++)
            execute_round(&block, &keys, round);
        increment_output(args, &msg, &block, &msg.output[block_index * 8], TRUE); //todo
    }
    write_output(data, args, &msg);
}