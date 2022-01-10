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
    char    raw[64];
    char    permuted[64];
    char    left[32];
    char    right[32];
    char    expanded[48];
    char    xored[48];
    char    s_boxed[32];
    char    p_boxed[32];
    char    processed[64];
}               t_block;

typedef struct  s_data
{
    char *input;
    char *output;
}               t_data;


void create_all_round_keys(t_keys *keys);
void execute_round(t_block *block, t_keys *keys, u_int8_t round);


void get_string_binary(char *input, char *output, u_int64_t size);
void get_hex_binary(char *input, char *output);
void get_sbox_binary(u_int8_t input, char *output);

void permute(char *input, char *output, const u_int8_t *array, int size);
void xor_bits_string(char *first, char *second, char *output, u_int64_t size);


// void xor_bits_string(char *pt_a, char *pt_b, char *result, int size);
void hexadecimal_to_binary(char *key, char *binkey);
void sboxes_tobinary(int result, char *bin_pt);
// void permute(char *bin, char *per_bin, const int *array, int size);

int is_one_shift_round(u_int8_t round);


extern const u_int8_t expansion_permutation[48];
extern const u_int8_t s_boxes[8][64];
extern const u_int8_t p_box[32];
extern const u_int8_t initial_permutation[64];
extern const u_int8_t final_permutation[64];
extern const u_int8_t key_compression[48];
extern const u_int8_t key_permutation[56];

#endif