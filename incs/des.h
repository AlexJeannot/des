#ifndef DES
# define DES

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <strings.h>
# include <string.h>

# define FALSE 0
# define TRUE 1
# define ENCRYPTION 2
# define DECRYPTION 3
# define INPUT 5
# define OUTPUT 6

typedef struct s_args
{
    u_int8_t d;
    u_int8_t process_type;
    u_int8_t i;
    u_int8_t o;
    // u_int8_t n;
    char *input_path;
    char *output_path;
}   t_args;

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

typedef struct  s_message
{
    char *input;
    u_int64_t rc_size;
    char output[64];
    int32_t output_fd;
}               t_message;


/*
**  ARGS.c
*/
void        parse_args(t_args *args, t_message *msg, char **list_args, int32_t nb_args);

/*
**  BINARY.c
*/
void get_string_binary(char *input, char *output, u_int64_t size);
void get_hex_binary(char *input, char *output);
void get_sbox_binary(u_int8_t input, char *output);

/*
**  CONST.c
*/
extern const u_int8_t expansion_permutation[48];
extern const u_int8_t s_boxes[8][64];
extern const u_int8_t p_box[32];
extern const u_int8_t initial_permutation[64];
extern const u_int8_t final_permutation[64];
extern const u_int8_t key_compression[48];
extern const u_int8_t key_permutation[56];

/*
**  CONTROL.c
*/

/*
**  ERROR.c 
*/
void        clean_msg(t_message *msg);
void    fatal_error(t_message *msg, const char *reason);
void    args_error(t_message *msg, const char *reason, const char *input);

/*
**  FILE.c
*/
void get_content(t_message *msg, t_args *args);
void add_output_fd(t_args *args, t_message *msg);

/*
**  KEY.c
*/
void create_all_round_keys(t_keys *keys, u_int8_t type);

/*
**  OPERATION.c
*/
void permute(char *input, char *output, const u_int8_t *array, int size);
void xor_bits_string(char *first, char *second, char *output, u_int64_t size);

/*
**  ROUND.c
*/
void prepare_rounds(t_block *block, char *input);
void execute_round(t_block *block, t_keys *keys, u_int8_t round);


#endif