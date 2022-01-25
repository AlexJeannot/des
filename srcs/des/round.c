#include "../../incs/des.h"

void    prepare_rounds(t_message_des *msg, t_block *block, u_int64_t block_index)
{
    bzero(block, sizeof(t_block));

    if (is_last_block(msg->block_number, block_index) && msg->is_last_block_empty)
        str_to_bin_str("", &block->raw[0], msg->rc_size, 8);
    else
        str_to_bin_str(&msg->raw_content[block_index * 8], &block->raw[0], msg->rc_size, 8);

    if (args->process_type == ENCRYPTION && args->mode == MODE_CBC)
        xor_plaintext(&block->raw[0], &msg->prev_block[0], block_index);
    else if (args->process_type == DECRYPTION && args->mode == MODE_CBC)
    {
        strncpy(&msg->prev_block[0], &msg->current_block[0], 64);
        strncpy(&msg->current_block[0], &block->raw[0], 64);
    }

    msg->rc_size -= 8;

    permute(&block->raw[0], &block->permuted[0], &initial_permutation[0], 64);
    strncpy(&block->left[0], &block->permuted[0], 32);
    strncpy(&block->right[0], &block->permuted[32], 32);

}

void    get_sbox_binary(u_int8_t input, char *output)
{
    u_int8_t    count;

    count = 0;
    for (int8_t bits = 3; bits >= 0; bits--)
    {
        if (((input >> bits) & 1) == 0)
            output[count] = '0';
        else if (((input >> bits) & 1) == 1)
            output[count] = '1';
        count++;
    }
}

void    s_box(char *xored, char *s_boxed)
{
    u_int8_t    x;
    u_int8_t    y;

    for (u_int8_t count = 0; count < 8; count++)
    {
        x = 3;
        y = 15;

        if (xored[count * 6] == '0')
            x -= 2;
        if (xored[(count * 6) + 5] == '0')
            x -= 1;

        if (xored[(count * 6) + 1] == '0')
            y -= 8;
        if (xored[(count * 6) + 2] == '0')
            y -= 4;
        if (xored[(count * 6) + 3] == '0')
            y -= 2;
        if (xored[(count * 6) + 4] == '0')
            y -= 1;
        
        get_sbox_binary(s_boxes[count][(16 * x) + y], &s_boxed[count * 4]);
    }
}

void    swap_blocks(char *left, char *right, char *p_boxed, u_int8_t round)
{
    char    xor_result[32];

    bzero(xor_result, 32);

    xor_bits_string(p_boxed, left, &xor_result[0], 32);
    if (round < 15)
    {
        strncpy(left, right, 32);
        strncpy(right, xor_result, 32); 
    }
    else
        strncpy(left, xor_result, 32);
}

void    execute_round(t_block *block, t_keys *keys, u_int8_t round)
{
    permute(block->right, block->expanded, &expansion_permutation[0], 48);
    xor_bits_string(block->expanded, keys->round_keys[round], block->xored, 48);
    s_box(block->xored, block->s_boxed);
    permute(block->s_boxed, block->p_boxed, &p_box[0], 32);
    swap_blocks(&block->left[0], &block->right[0], &block->p_boxed[0], round);
}