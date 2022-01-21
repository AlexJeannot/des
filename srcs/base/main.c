#include "../../incs/base.h"

t_data  *data;
t_args  *args;
t_key   *key;

void    init_global_variables(void)
{
    data = NULL;
    args = NULL;
    key = NULL;
}

int32_t main(int argc, char **argv)
{
    init_global_variables();
    process_args(&argv[1], argc - 1);
    switch (args->algorithm)
    {
        case ALGO_MD5:      md5();              break;
        case ALGO_SHA256:   sha256(data, NULL); break;
        case ALGO_BASE64:   base64(NULL);       break;
        case ALGO_DES:      des();              break;
    }
    return (0);
}