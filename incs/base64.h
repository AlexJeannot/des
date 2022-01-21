#ifndef BASE64
# define BASE64

#include "./base.h"

# define ENCODING 5
# define DECODING 6

typedef struct  s_block
{
    u_int8_t    a;
    u_int8_t    b;
    u_int8_t    c;
}               t_block;

/*
**  DECODE.C
*/
void process_decoding(t_message_base64 *msg, t_message_des *msg_des, t_args *args);

/*
**  ENCODE.C
*/
void process_encoding(t_message_base64 *msg, t_message_des *msg_des, t_args *args);

/*
**  IN OTHERS DIRECTORIES
*/
u_int8_t is_last_block(u_int64_t total_block, u_int64_t current_block);

#endif