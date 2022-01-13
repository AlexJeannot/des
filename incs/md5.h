#ifndef MD5
# define MD5

# include "./base.h"

typedef struct  s_buffers
{
    u_int32_t   a;
    u_int32_t   b;
    u_int32_t   c;
    u_int32_t   d;
}               t_buffers;

/*
** VARIABLES
*/
typedef u_int32_t(*round_function)(u_int32_t, u_int32_t, u_int32_t);

extern const u_int32_t md5_constants[64];
extern const u_int32_t md5_computed_constants[64];
extern const u_int32_t md5_blocks_constants[64];


/*
** AUXILIARY_FUNCTIONS.C
*/
u_int32_t   f(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t   g(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t   h(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t   i(u_int32_t x, u_int32_t y, u_int32_t z);

/*
** DIGEST.C
*/
void        process_msg_md5(t_message *msg);

#endif