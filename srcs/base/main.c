#include "../../incs/base.h"

int main(int argc, char **argv)
{
    t_data data;
    t_args args;

    bzero(&data, sizeof(t_data));
    bzero(&args, sizeof(t_args));

    process_args(&data, &args, &argv[1], argc - 1);
    get_content(&data, &args);


}