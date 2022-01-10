#include "../incs/des.h"


void expansion_permutation(char *right, char *expanded_right)
{
    int exp_perm[48] = {   32, 1, 2, 3, 4, 5, 4, 5,
                        6, 7, 8, 9, 8, 9, 10, 11,
                        12, 13, 12, 13, 14, 15, 16, 17,
                        16, 17, 18, 19, 20, 21, 20, 21,
                        22, 23, 24, 25, 24, 25, 26, 27,
                        28, 29, 28, 29, 30, 31, 32, 1 };

    permute(right, expanded_right, &exp_perm[0], 48);
}

void s_box(char *xored, char *s_boxed)
{
    u_int8_t x;
    u_int8_t y;

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
        
        sboxes_tobinary(s_boxes[count][(16 * x) + y], &s_boxed[count * 4]);
    }
}

void swap_blocks(char *left, char *right, char *p_boxed, u_int8_t round)
{
    char xor_result[32];

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

void execute_round(t_block *block, t_keys *keys, u_int8_t round)
{
    expansion_permutation(block->right, block->expanded);
    xor_bits_string(block->expanded, keys->round_keys[round], block->xored, 48);
    s_box(block->xored, block->s_boxed);
    permute(block->s_boxed, block->p_boxed, &p_box[0], 32);
    swap_blocks(&block->left[0], &block->right[0], &block->p_boxed[0], round);
}