#include "../incs/des.h"

int is_one_shift_round(u_int8_t round)
{
    return (round == 1 || round == 2 || round == 9 || round == 16);
}