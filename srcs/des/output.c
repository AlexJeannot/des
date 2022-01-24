#include "../../incs/des.h"

void    prepare_output(t_message_des *msg)
{
    if (!(msg->pc_content = (char *)malloc(msg->fc_size)))
        fatal_error("processed content memory allocation");
}

void    increment_output(t_args *args, t_message_des *msg, t_block *block, char *output, u_int8_t is_last_block)
{
    u_int8_t    padding;

    ft_strncpy(&block->processed[0], &block->left[0], 32);
    ft_strncpy(&block->processed[32], &block->right[0], 32);
    permute(&block->processed[0], &block->permuted[0], &final_permutation[0], 64);

    if (args->mode == MODE_CBC)
        ft_strncpy(&msg->prev_block[0], &block->permuted[0], 64);
    
    for (u_int8_t bytes = 0; bytes < 8; bytes++)
    {
        for (u_int8_t bits = 0; bits < 8; bits++)
        {
            output[bytes] = output[bytes] << 1;
            output[bytes] = output[bytes] | (block->permuted[(bytes * 8) + bits] - 48);
        }
    }

    padding = (is_last_block && args->process_type == DECRYPTION) ? is_block_padded(output) : 0;
    msg->pc_size += (8 - padding);
}

void    write_output(t_data *data, t_args *args, t_message_des *msg)
{
    if (base64_option())
    {
        free(data->input);
        data->input = msg->pc_content;
        data->rc_size = msg->pc_size;
        base64(msg);
    }
    if (write(args->output_fd, &msg->pc_content[0], msg->pc_size) == -1)
        fatal_error("output writing on file descriptor");
    if (base64_option() && args->process_type == ENCRYPTION)
        if (write(args->output_fd, "\n", 1) == -1)
            fatal_error("output writing on file descriptor");
}

