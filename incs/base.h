#ifndef BASE
# define BASE

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <strings.h>
# include <string.h>

# define FALSE 0
# define TRUE 1
# define INPUT 2
# define OUTPUT 3
# define ERROR 4
# define EN 5 // ENCRYPTION/ENCODING
# define DE 6 // DECRYPTION/DECODING

# define ALGO_DES 7
# define ALGO_BASE64 8
# define ALGO_MD5 9
# define ALGO_SHA256 10

# define SRC_STDIN 11
# define SRC_FILE 12
# define SRC_ARG 13

typedef struct s_args
{
    u_int8_t algorithm;
    u_int8_t process_type;

    u_int8_t a;
    u_int8_t d;
    u_int8_t e;
    u_int8_t i;
    u_int8_t k;
    u_int8_t n;
    u_int8_t o;
    u_int8_t p;
    u_int8_t q;
    u_int8_t r;
    u_int8_t s;
    u_int8_t v;

    char key[16];
    int32_t output_fd;
}   t_args;

typedef struct  s_data
{
    char *input;
    u_int64_t rc_size;
    u_int8_t            nofile;
    char                *src;
    u_int8_t            src_type;
    struct s_data *next;
}               t_data;

typedef struct  s_message_des
{
    char *raw_content;
    char *pc_content;
    u_int64_t rc_size;
    u_int64_t pc_size;
    int32_t output_fd;
    u_int64_t block_number;
}               t_message_des;

typedef struct  s_message_base64
{
    char                *raw_content;
    char                *fmt_content;
    char                *pc_content;
    u_int64_t           rc_size;
    u_int64_t           fc_size;
    u_int64_t           pc_size;
    u_int64_t           cc_size;
    u_int64_t           blocks_size;
    int32_t             output_fd;
}               t_message_base64;

typedef struct  s_message_hash
{
    char                *raw_content;
    char                *fmt_content;
    char                *src;
    char                *hash;
    u_int64_t           rc_size;
    u_int64_t           fc_size;
    u_int64_t           cc_size;
    u_int8_t            nofile;
    u_int8_t            src_type;
}               t_message_hash;


extern t_data *data;
extern t_args *args;

u_int8_t    parse_options(char *input, char *next_input, int32_t args_diff);
u_int8_t is_hash_algorithm(void);
void create_data(t_data **new_data);
void organize_data(t_data *new_data);
int32_t     get_file(t_data *new_data, char *file_path, u_int8_t type);
void process_io(char *file_path, u_int8_t type);
void get_key(char *key);
void        set_file_context(t_data *new_data, char *file_path);
void process_string(char *input);
u_int8_t is_stdin_process(void);
void base64(t_message_des *msg_des);
void des(void);
void    format_msg(t_message_hash *msg, const u_int8_t swap);
void    display_hash(const t_message_hash *msg);
void    md5(void);
void    build_hash(t_message_hash *msg, void *buffers, u_int32_t nb_words, const u_int8_t swap);

/*
**  ARGS.c
*/
void        process_args(char **list_args, int32_t nb_args);

/*
**  BINARY.c
*/
void get_string_binary(char *input, char *output, u_int64_t input_size, u_int64_t output_size);
void get_hex_binary(char *input, char *output);
void get_sbox_binary(u_int8_t input, char *output);

/*
** BITS.C
*/
u_int32_t           rotate_left(u_int32_t x, u_int32_t offset);
u_int32_t           rotate_right(u_int32_t x, u_int32_t offset);
u_int32_t           shift_right(u_int32_t x, u_int32_t offset);

/*
**  CONTROL.c
*/
u_int8_t is_hexadecimal(char *input);
u_int8_t base64_option(void);

/*
**  ERROR.c 
*/
void    fatal_error(const char *reason);
void    args_error(const char *reason, const char *input);


/*
**  FILE.c
*/
// void get_content(t_data *data, t_args *args);
void get_file_content(t_data *current_data, int32_t fd);


/*
** SWAP.C
*/
u_int16_t           swap_uint_16(u_int16_t val);
int16_t             swap_int_16(int16_t val);
u_int32_t           swap_uint_32(u_int32_t val);
int32_t             swap_int_32(int32_t val);
u_int64_t           swap_uint_64(u_int64_t val);
int64_t             swap_int_64(int64_t val);


#endif