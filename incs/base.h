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



#
typedef struct s_args
{
    u_int8_t algorithm;
    u_int8_t d;
    u_int8_t process_type;
    u_int8_t i;
    u_int8_t o;
    u_int8_t k;
    u_int8_t a;
    u_int8_t n;

    char *input_path;
    char *output_path;
    char key[16];
}   t_args;

typedef struct  s_data
{
    char *input;
    u_int64_t rc_size;
    int32_t output_fd;
    char key[16];
}               t_data;

typedef struct  s_message_des
{
    char *input;
    char *output;
    u_int64_t rc_size;
    u_int64_t pc_size;
    int32_t output_fd;
    u_int64_t block_number;
}               t_message_des;

typedef struct  s_message_base64
{
    char                *raw_content;
    char                *fmt_content;
    char                *processed_content;
    u_int64_t           rc_size;
    u_int64_t           fc_size;
    u_int64_t           pc_size;
    u_int64_t           cc_size;
    u_int64_t           blocks_size;
    int32_t             output_fd;
}               t_message_base64;


/*
**  ARGS.c
*/
void        process_args(t_data *data, t_args *args, char **list_args, int32_t nb_args);

/*
**  BINARY.c
*/
void get_string_binary(char *input, char *output, u_int64_t input_size, u_int64_t output_size);
void get_hex_binary(char *input, char *output);
void get_sbox_binary(u_int8_t input, char *output);

/*
**  CONTROL.c
*/
u_int8_t is_hexadecimal(char *input);
u_int8_t base64_option(t_args *args);

/*
**  ERROR.c 
*/
// void        clean_msg(t_message *msg);
void    fatal_error(t_data *data, t_args *args, const char *reason);
void    args_error(t_args *args, const char *reason, const char *input);

/*
**  FILE.c
*/
int32_t     get_file(t_args *args, u_int8_t type);
void get_content(t_data *data, t_args *args);
void add_output_fd(t_data *data, t_args *args);






void base64(t_data *data, t_args *args, t_message_des *msg_des);
void des(t_data *data, t_args *args);

#endif