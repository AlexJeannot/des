#ifndef SHA256
# define SHA256

# include "./base.h"

typedef struct  s_buffers
{
    u_int32_t   a;
    u_int32_t   b;
    u_int32_t   c;
    u_int32_t   d;
    u_int32_t   e;
    u_int32_t   f;
    u_int32_t   g;
    u_int32_t   h;
}               t_buffers;

/*
** VARIABLES
*/
extern const u_int32_t sha256_computed_constants[64];


/*
** AUXILIARY_FUNCTIONS.C
*/
u_int32_t   ch(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t   maj(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t   ssig0(u_int32_t x);
u_int32_t   ssig1(u_int32_t x);
u_int32_t   bsig0(u_int32_t x);
u_int32_t   bsig1(u_int32_t x);

/*
** DIGEST.C
*/
void        process_msg_sha256(t_message *msg);

#endif