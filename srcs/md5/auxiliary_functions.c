#include "../../incs/md5.h"

u_int32_t   f(u_int32_t x, u_int32_t y, u_int32_t z)
{
    return ((x & y) | ((~x) & z));
}

u_int32_t   g(u_int32_t x, u_int32_t y, u_int32_t z)
{
    return ((x & z) | (y & (~z)));
}

u_int32_t   h(u_int32_t x, u_int32_t y, u_int32_t z)
{
    return (x ^ y ^ z);
}

u_int32_t   i(u_int32_t x, u_int32_t y, u_int32_t z)
{
    return (y ^ (x | (~z)));
}