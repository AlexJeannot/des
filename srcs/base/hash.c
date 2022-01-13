#include "../../incs/base.h"



u_int8_t is_hash_algorithm(void)
{
    return (args->algorithm == ALGO_MD5 || args->algorithm == ALGO_SHA256);
}