#include "../../incs/base.h"

void    display_help(void)
{
    printf("\nUsage: algorithm [-p -q -r] [-s string] [file...]\n");
    printf("    algorithm       Algorithm to hash input (md5/sha256)\n");
    printf("    file            files to digest\n");
    printf("    -p              Process STDIN input\n");
    printf("    -q              Quiet mode (output hash only)\n");
    printf("    -r              Reverse mode (output source after the hash)\n");
    printf("    -s              Process string\n");
    printf("\nexamples:\n");
    printf("    ./ft_ssl md5 file.txt\n");
    printf("    ./ft_ssl sha256 -s \"hello world\"\n");
    printf("    echo \"hello world\" | ./ft_ssl md5\n");
    printf("    echo \"hello world\" | ./ft_ssl sha256 -p file.txt\n");
    printf("    echo \"hello world\" | ./ft_ssl md5 -p -s \"hello world\" file.txt\n");
}

void    display_src(const t_message_hash *msg)
{
    if (args->r)
        printf(" ");
    if (msg->src_type == SRC_STDIN && args->p)
        printf("(\"%s\")", msg->src);
    else if (msg->src_type == SRC_STDIN)
        printf("(stdin)");
    else if (msg->src_type == SRC_ARG)
        printf("(\"%s\")", msg->raw_content);
    else if (msg->src_type == SRC_FILE)
        printf("(%s)", msg->src);
    if (!args->r)
        printf(" = ");
}

void    display_hash(const t_message_hash *msg)
{
    if (msg->nofile) {
        printf("Error: no such file [%s]\n", msg->src);
        return ;
    }
    if (!args->q)
    {
        if (args->algorithm == ALGO_MD5)
            printf("[MD5] ");
        else if (args->algorithm == ALGO_SHA256)
            printf("[SHA256] ");
        
        if (!(args->r))
            display_src(msg);
    }
    printf("%s", msg->hash);
    if (!args->q && args->r)
        display_src(msg);
    printf("\n");
}