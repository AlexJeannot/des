#include "../../incs/base.h"

u_int16_t   swap_uint_16(u_int16_t val)
{
    val = (val << 8) | (val >> 8);
    return (val);
}

int16_t     swap_int_16(int16_t val)
{
    val = (val << 8) | ((val >> 8) & 0x00FF);
    return (val);
}

u_int32_t   swap_uint_32(u_int32_t val)
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0x00FF00FF);
    val = (val << 16) | (val >> 16);
    return (val);
}

int32_t     swap_int_32(int32_t val)
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0x00FF00FF);
    val = (val << 16) | ((val >> 16) & 0x0000FFFF );
    return (val);
}

u_int64_t   swap_uint_64(u_int64_t val)
{
    val = ((val << 8) & 0xFF00FF00FF00) | ((val >> 8) & 0x00FF00FF00FF);
    val = ((val << 16) & 0xFFFF0000FFFF0000) | ((val >> 16) & 0x0000FFFF0000FFFF);
    val = (val << 32) | (val >> 32);
    return (val);
}

int64_t     swap_int_64(int64_t val)
{
    val = ((val << 8) & 0xFF00FF00FF00) | ((val >> 8) & 0x00FF00FF00FF);
    val = ((val << 16) & 0xFFFF0000FFFF0000) | ((val >> 16) & 0x0000FFFF0000FFFF);
    val = (val << 32) | ((val >> 32) & 0x00000000FFFFFFFF);
    return (val);
}