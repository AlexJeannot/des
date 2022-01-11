#include "../../incs/des.h"

u_int8_t shift_number(int round)
{
    if (round == 1 || round == 2 || round == 9 || round == 16)
        return (1);
    return (2);
}

void set_round_keys(t_keys *keys, char *input_key, u_int8_t type)
{

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
        if (type == ENCRYPTION)
            strncpy(&keys->round_keys[round][0], &round_key[0], 48);
        else
            strncpy(&keys->round_keys[15 - round][0], &round_key[0], 48);

        strncpy(&input_key[0], &shifted_key[0], 56);
    }
}

void create_all_round_keys(t_keys *keys, u_int8_t type)
{
    char binary_key[64];
    char truncated_binary_key[56];

    bzero(&binary_key[0], 64);
    bzero(&truncated_binary_key[0], 56);
    
    get_hex_binary(keys->origin_key, &binary_key[0]);
    permute(&binary_key[0], &truncated_binary_key[0], &key_permutation[0], 56);
    set_round_keys(keys, &truncated_binary_key[0], type);
}