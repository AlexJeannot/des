#include "../../incs/base.h"

int main(int argc, char **argv)
{
    t_data data;
    t_args args;

    bzero(&data, sizeof(t_data));
    bzero(&args, sizeof(t_args));

    process_args(&data, &args, &argv[1], argc - 1);
    get_content(&data, &args);

    if (args.algorithm == ALGO_DES)
        des(&data, &args);
    else if (args.algorithm == ALGO_BASE64)
        base64(&data, &args, NULL);
    
    return (0);
}