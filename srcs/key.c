#include "../incs/des.h"

u_int8_t shift_number(int round)
{
    if (round == 1 || round == 2 || round == 9 || round == 16)
        return (1);
    return (2);
}

void set_round_keys(t_keys *keys, char *input_key)
{
    int key_compression[48] = { 14, 17, 11, 24, 1, 5,
                                3, 28, 15, 6, 21, 10,
                                23, 19, 12, 4, 26, 8,
                                16, 7, 27, 20, 13, 2,
                                41, 52, 31, 37, 47, 55,
                                30, 40, 51, 45, 33, 48,
                                44, 49, 39, 56, 34, 53,
                                46, 42, 50, 36, 29, 32 };

    char shifted_key[56];
    char round_key[48];
    u_int8_t shift;

    bzero(&shifted_key[0], 56);
    bzero(&round_key[0], 48);

    for (u_int8_t round = 0; round < 16; round++)
    {
        shift = shift_number(round + 1);

        strncpy(&shifted_key[0], &input_key[shift], 28 - shift);
        strncpy(&shifted_key[28 - shift], &input_key[0], shift);
        strncpy(&shifted_key[28], &input_key[28 + shift], 28 - shift);
        strncpy(&shifted_key[56 - shift], &input_key[28], shift);

        permute(&shifted_key[0], &round_key[0], &key_compression[0], 48);
        strncpy(&keys->round_keys[round][0], &round_key[0], 48);
        strncpy(&input_key[0], &shifted_key[0], 56);
    }
}

void truncate_key(char *key, char *truncated_key)
{
    int key_permutation[56] = { 57, 49, 41, 33, 25, 17, 9,
                                1, 58, 50, 42, 34, 26, 18,
                                10, 2, 59, 51, 43, 35, 27,
                                19, 11, 3, 60, 52, 44, 36,
                                63, 55, 47, 39, 31, 23, 15,
                                7, 62, 54, 46, 38, 30, 22,
                                14, 6, 61, 53, 45, 37, 29,
                                21, 13, 5, 28, 20, 12, 4 };
    
    permute(&key[0], &truncated_key[0], &key_permutation[0], 56);
}

void create_all_round_keys(t_keys *keys)
{
    char binary_key[64];
    char truncated_binary_key[56];

    bzero(&binary_key[0], 64);
    bzero(&truncated_binary_key[0], 56);

    hexadecimal_to_binary(keys->origin_key, &binary_key[0]);
    truncate_key(&binary_key[0], &truncated_binary_key[0]);
    set_round_keys(keys, &truncated_binary_key[0]);
}