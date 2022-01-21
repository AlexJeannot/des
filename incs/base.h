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

# define EN 5
# define DE 6

# define ALGO_DES 7
# define ALGO_BASE64 8
# define ALGO_MD5 9
# define ALGO_SHA256 10

# define SRC_STDIN 11
# define SRC_FILE 12
# define SRC_ARG 13

# define HMAC_FIRST 14
# define HMAC_SECOND 15

# define MODE_ECB 16
# define MODE_CBC 17

/*
**  STRUCTURES
*/

typedef struct  s_args
{
    u_int8_t    algorithm;
    u_int8_t    process_type;
    u_int8_t    mode;

    u_int8_t    a;
    u_int8_t    d;
    u_int8_t    e;
    u_int8_t    i;
    u_int8_t    k;
    u_int8_t    n;
    u_int8_t    o;
    u_int8_t    p;
    u_int8_t    q;
    u_int8_t    r;
    u_int8_t    s;
    u_int8_t    v;

    char        key[16];
    char        iv[16];
    int32_t     output_fd;
}               t_args;

typedef struct  s_data
{   
    char            *input;
    u_int64_t       rc_size;

    u_int8_t        nofile;
    char            *src;
    u_int8_t        src_type;

    struct s_data   *next;
}               t_data;

typedef struct   s_derivated_key
{
    char        *password;
    char        fmt_password[64];
    u_int8_t    password_length;
    char        salt[16];

    char        hash_result[64];

    char        i_key_pad[64];
    char        o_key_pad[64];
}               t_derivated_key;

typedef struct  s_key
{
    char            key[16];
    t_derivated_key dkey;
}               t_key;

typedef struct  s_message_des
{
    char        *raw_content;
    char        *pc_content;

    u_int64_t   rc_size;
    u_int64_t   fc_size;
    u_int64_t   pc_size;

    u_int64_t   block_number;
    u_int8_t    is_last_block_empty;
    char        prev_block[64];
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
}               t_message_base64;

typedef struct  s_message_hash
{
    char                *raw_content;
    char                *fmt_content;
    char                *hash;

    u_int64_t           rc_size;
    u_int64_t           fc_size;
    u_int64_t           cc_size;

    char                *src;
    u_int8_t            nofile;
    u_int8_t            src_type;
}               t_message_hash;

/*
**  GLOBAL VARIABLES
*/
extern t_data   *data;
extern t_args   *args;
extern t_key    *key;


/*
**  ARGS.C
*/
void        clean_args(void);
void        process_args(char **list_args, int32_t nb_args);

/*
**  BITS.C
*/
u_int32_t   rotate_left(u_int32_t x, u_int32_t offset);
u_int32_t   rotate_right(u_int32_t x, u_int32_t offset);
u_int32_t   shift_right(u_int32_t x, u_int32_t offset);

/*
**  CONTROL.C
*/
u_int8_t    is_last_block(u_int64_t total_block, u_int64_t current_block);
u_int8_t    is_block_padded(char *input);
u_int8_t    is_hexadecimal(char *input);
u_int8_t    base64_option(void);
u_int8_t    is_stdin_process(void);
u_int8_t    is_hash_algorithm(void);

/*
**  CONVERSION.C
*/
void    bin_str_to_str(char *binary_str, char *str, u_int64_t binary_size);
void    str_to_bin_str(char *input, char *output, u_int64_t input_size, u_int64_t output_size);
void    str_to_hex_str(char *str, char *hex_str, u_int64_t size);
void    hex_str_to_str(char *hex_str, char *str, u_int64_t hex_size);
void    hex_str_to_bin_str(char *input, char *output, u_int64_t input_size);

/*
**  DATA.C
*/
void        clean_data(void);
void        create_data(t_data **new_data);
void        organize_data(t_data *new_data);

/*
**  DISPLAY.C
*/
void        display_help(void);
void        display_hash(const t_message_hash *msg);

/*
**  ERROR.C
*/
void        fatal_error(const char *reason);
void        args_error(const char *reason, const char *input);


/*
**  FILE.C
*/
int32_t     get_file(t_data *new_data, char *file_path, u_int8_t type);
void        get_file_content(t_data *current_data, int32_t fd);
void        set_file_context(t_data *new_data, char *file_path);

/*
**  HASH.C
*/
void        build_hash(t_message_hash *msg, void *buffers, u_int32_t nb_words, const u_int8_t swap);


/*
**  IO.C
*/
void        process_string(char *input);
void        process_stdin(void);
void        process_file(char *file_path, u_int8_t type);

/*
**  MODE.C
*/
void        get_initial_vector(char *input_iv);
void        create_initial_vector(void);
void        get_operation_mode(char *input);

/*
**  OPTION.C
*/
u_int8_t    parse_options(char *input, char *next_input, int32_t args_diff);

/*
**  PADDING.C
*/
void        format_msg(t_message_hash *msg, const u_int8_t swap);
void        add_padding(char *output, u_int64_t bytes, u_int64_t size);

/*
**  PBKDF2.C
*/
void        pbkdf2(u_int32_t dkey_length, u_int32_t hash_length, u_int64_t round);

/*
** SECRET.C
*/
void        ask_password(void);
void        get_password(char *input_password);
void        create_salt(void);
void        get_salt(char *input_salt);
void        allocate_key(void);
void        get_key(char *input_key);

/*
** SWAP.C
*/
int16_t     swap_int_16(int16_t val);
u_int32_t   swap_uint_32(u_int32_t val);
int32_t     swap_int_32(int32_t val);
u_int16_t   swap_uint_16(u_int16_t val);
u_int64_t   swap_uint_64(u_int64_t val);
int64_t     swap_int_64(int64_t val);

/*
**  IN OTHERS DIRECTORIES
*/
void        base64(t_message_des *msg_des);
void        des(void);
void        md5(void);
void        sha256(t_data *current_data, char *output);

#endif