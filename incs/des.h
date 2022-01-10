#ifndef DES
# define DES

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <strings.h>
# include <string.h>

typedef struct  s_keys
{
    char *origin_key;
    char round_keys[16][48];
}               t_keys;

typedef struct  s_block
{
    char    left[32];
    char    right[32];
    char    expanded[48];
    char    xored[48];
    char    s_boxed[32];
    char    p_boxed[32];
}               t_block;


void create_all_round_keys(t_keys *keys);
void execute_round(t_block *block, t_keys *keys, u_int8_t round);




void xor_bits_string(char *pt_a, char *pt_b, char *result, int size);
void hexadecimal_to_binary(char *key, char *binkey);
void sboxes_tobinary(int result, char *bin_pt);
void permute(char *bin, char *per_bin, const int *array, int size);


extern const int s_boxes[8][64];
extern const int p_box[32];

#endif