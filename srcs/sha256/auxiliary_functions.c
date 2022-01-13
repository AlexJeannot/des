#include "../../incs/sha256.h"

u_int32_t   ch(u_int32_t x, u_int32_t y, u_int32_t z)
{
    return ((x & y) ^ (~x & z));
}

u_int32_t   maj(u_int32_t x, u_int32_t y, u_int32_t z)
{
    return ((x & y) ^ (x & z) ^ (y & z));
}

u_int32_t   ssig0(u_int32_t x)
{
    return ((rotate_right(x, 7)) ^ (rotate_right(x, 18)) ^ shift_right(x, 3));
}

u_int32_t   ssig1(u_int32_t x)
{
    return ((rotate_right(x, 17)) ^ (rotate_right(x, 19)) ^ shift_right(x, 10));
}

u_int32_t   bsig0(u_int32_t x)
{
    return ((rotate_right(x, 2)) ^ (rotate_right(x, 13)) ^ rotate_right(x, 22));
}

u_int32_t   bsig1(u_int32_t x)
{
    return ((rotate_right(x, 6)) ^ (rotate_right(x, 11)) ^ rotate_right(x, 25));
}