#include "../incs/des.h"

// void print_binary_str(char *str, char *type, int size)
// {
//     printf("%s = ", type);
//     fflush(stdout);
//     write(1, str, size);
//     printf("\n");
// }

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
    if (write(msg->output_fd, msg->output, 64) == -1)
        fatal_error(msg, "Output writing on file descriptor");
}

int main(int argc, char **argv)
{
    // (void)argc;
    // (void)argv;
    // char pt[8] = "ABCDEFGH";
    char *key = "AABBCCDDEEFF1122";
    char test[8];

    t_message msg;
    t_keys keys;
    t_block block;
    t_args args;

    bzero(&args, sizeof(t_args));
    bzero(&msg, sizeof(t_message));
    bzero(&keys, sizeof(t_keys));


    parse_args(&args, &msg, &argv[1], argc - 1);

    get_content(&msg, &args);

    bzero(test, 8);
    keys.origin_key = key;
    // msg.output = test;

    create_all_round_keys(&keys, args.process_type);
    for (u_int64_t block_index = 0; block_index < 1; block_index++)
    {
        prepare_rounds(&block, msg.input);
        for (u_int8_t round = 0; round < 16; round++)
            execute_round(&block, &keys, round);
        increment_output(&block, &msg.output[block_index * 8]);
        write_output(&msg);
    }

    // printf("res =\n");
    // write(1, msg.output, 8);
    // printf("\n");


    // memcpy(&pt[0], &msg.output[0], 8);
    // key = "AABBCCDDEEFF1122";
    // bzero(&msg, sizeof(t_message));
    // bzero(&keys, sizeof(t_keys));
    // bzero(test, 8);
    // bzero(&keys, sizeof(t_keys));
    // keys.origin_key = key;
    // msg.input = pt;
    // msg.output = test;

    // create_all_round_keys(&keys, DECRYPTION);
    // for (u_int64_t block_index = 0; block_index < 1; block_index++)
    // {
    //     prepare_rounds(&block, msg.input);
    //     for (u_int8_t round = 0; round < 16; round++)
    //         execute_round(&block, &keys, round);
    //     increment_output(&block, &msg.output[block_index * 8]);
    // }

    // printf("res =\n");
    // write(1, msg.output, 8);
    // printf("\n");

    clean_msg(&msg);
}