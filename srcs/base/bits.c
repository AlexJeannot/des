#include "../../incs/base.h"

u_int32_t   rotate_left(u_int32_t x, u_int32_t offset)
{
    return ((x << offset) | (x >> (32 - offset)));
}

u_int32_t   rotate_right(u_int32_t x, u_int32_t offset)
{
    return ((x >> offset) | (x << (32 - offset)));
}

u_int32_t   shift_right(u_int32_t x, u_int32_t offset)
{
    return (x >> offset);
}