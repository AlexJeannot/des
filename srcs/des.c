#include "../incs/des.h"




void print_binary_str(char *str, char *type, int size)
{
    printf("%s = ", type);
    fflush(stdout);
    write(1, str, size);
    printf("\n");
}

void prepare_rounds(t_block *block, char *input)
{
    bzero(block, sizeof(t_block));
    get_string_binary(input, &block->raw[0], 8);
    permute(&block->raw[0], &block->permuted[0], &initial_permutation[0], 64);
    strncpy(&block->left[0], &block->permuted[0], 32);
    strncpy(&block->right[0], &block->permuted[32], 32);
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

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    char pt[8] = "ABCDEFGH";
    char *key = "AABBCCDDEEFF1122";
    char test[8];

    t_data data;
    t_keys keys;
    t_block block;

    bzero(&data, sizeof(t_data));
    bzero(&keys, sizeof(t_keys));
    bzero(test, 8);
    keys.origin_key = key;
    data.input = pt;
    data.output = test;

    create_all_round_keys(&keys, ENCRYPTION);
    for (u_int64_t block_index = 0; block_index < 1; block_index++)
    {
        prepare_rounds(&block, data.input);
        for (u_int8_t round = 0; round < 16; round++)
            execute_round(&block, &keys, round);
        increment_output(&block, &data.output[block_index * 8]);
    }

    printf("res =\n");
    write(1, data.output, 8);
    printf("\n");


    memcpy(&pt[0], &data.output[0], 8);
    key = "AABBCCDDEEFF1122";
    bzero(&data, sizeof(t_data));
    bzero(&keys, sizeof(t_keys));
    bzero(test, 8);
    bzero(&keys, sizeof(t_keys));
    keys.origin_key = key;
    data.input = pt;
    data.output = test;

    create_all_round_keys(&keys, DECRYPTION);
    for (u_int64_t block_index = 0; block_index < 1; block_index++)
    {
        prepare_rounds(&block, data.input);
        for (u_int8_t round = 0; round < 16; round++)
            execute_round(&block, &keys, round);
        increment_output(&block, &data.output[block_index * 8]);
    }

    printf("res =\n");
    write(1, data.output, 8);
    printf("\n");
}