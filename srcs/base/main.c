#include "../../incs/base.h"

t_data *data;
t_args *args;
t_key *key;

void control_args(int argc)
{
    if (argc < 2)
        args_error("No arguments provided", NULL);
}

void process_hash(void)
{

}

void process_other(void)
{
    if (args->algorithm == ALGO_DES)
        des();
    else if (args->algorithm == ALGO_BASE64)
        base64(NULL);  
}

int main(int argc, char **argv)
{
    data = NULL;
    args = NULL;
    key = NULL;

    process_args(&argv[1], argc - 1);
    pbkdf2(8, 32, 310000);
    if (args->algorithm == ALGO_MD5) // SWITCH
        md5();
    else if (args->algorithm == ALGO_SHA256)
        sha256(data, NULL);  
    else if (args->algorithm == ALGO_BASE64)
        base64(NULL);
    else if (args->algorithm == ALGO_DES)
        des();  


    
    return (0);
}