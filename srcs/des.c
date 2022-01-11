#include "../incs/des.h"

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

void write_output(t_message *msg)
{
    if (write(msg->output_fd, &msg->output[0], 8) == -1)
        fatal_error(msg, "Output writing on file descriptor");
}

int main(int argc, char **argv)
{
    t_args args;
    t_keys keys;
    t_message msg;
    t_block block;

    bzero(&args, sizeof(t_args));
    bzero(&msg, sizeof(t_message));
    bzero(&keys, sizeof(t_keys));

    parse_args(&args, &msg, &keys, &argv[1], argc - 1);
    get_content(&msg, &args);
    create_all_round_keys(&keys, args.process_type);
    for (u_int64_t block_index = 0; block_index < 1; block_index++)
    {
        prepare_rounds(&msg, &block);
        for (u_int8_t round = 0; round < 16; round++)
            execute_round(&block, &keys, round);
        increment_output(&block, msg.output);
        write_output(&msg);
    }

    printf("\n");
    clean_msg(&msg);
}