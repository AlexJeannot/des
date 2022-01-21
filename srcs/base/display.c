#include "../../incs/base.h"

void    display_help(void)
{
    printf("\nEncoding commands:\n");
    printf("base64\n");
    printf("\nMessage digest commands:\n");
    printf("md5\n");
    printf("sha256\n");
    printf("\nCipher commands:\n");
    printf("des-ecb\n");
    printf("des-cbc\n");

    if (args->algorithm == FALSE || args->algorithm == ALGO_BASE64)
    {
        printf("\n> BASE64\n");
        printf("Usage: base64 [-d -e -n] [-i file] [-o file]\n");
        printf("    -d              Decode option\n");
        printf("    -e              Encode option (default)\n");
        printf("    -n              Add newline for encoding output\n");
        printf("    -i  file        Path to input file\n");
        printf("    -o  file        Path to output file\n");
        printf("\nexamples:\n");
        printf("    ./ft_ssl base64 -i input.txt\n");
        printf("    ./ft_ssl base64 -i input.txt -o output.txt\n");
        printf("    ./ft_ssl base64 -n -i input.txt -o output.txt\n");
        printf("    ./ft_ssl base64 -e -n -i input.txt -o output.txt\n");
        printf("    ./ft_ssl base64 -d -i input.txt -o output.txt\n");
        printf("    echo -n \"hello world\" | ./ft_ssl base64 -e\n");
        printf("    echo -n \"aGVsbG8gd29ybGQ=\" | ./ft_ssl base64 -d\n");
    }

    if (args->algorithm == FALSE || is_hash_algorithm())
    {
        printf("\n> MD5 / SHA256\n");
        printf("Usage: algorithm [-p -q -r] [-s string] [file...]\n");
        printf("    algorithm       Algorithm to hash input (md5/sha256)\n");
        printf("    file            files to digest\n");
        printf("    -p              Process STDIN input\n");
        printf("    -q              Quiet mode (output hash only)\n");
        printf("    -r              Reverse mode (output source after the hash)\n");
        printf("    -s              Process string\n");
        printf("\nexamples:\n");
        printf("    ./ft_ssl md5 file.txt\n");
        printf("    ./ft_ssl sha256 -s \"hello world\"\n");
        printf("    echo -n \"hello world\" | ./ft_ssl md5\n");
        printf("    echo -n \"hello world\" | ./ft_ssl sha256 -p file.txt\n");
        printf("    echo -n \"hello world\" | ./ft_ssl md5 -p -s \"hello world\" file.txt\n");
    }

    if (args->algorithm == FALSE || args->algorithm == ALGO_DES)
    {
        printf("\n> DES\n");
        printf("Usage: des-mode [-a -d -e] [-i file] [-o file] [-k hex] [-p string] [-s hex] [-v hex]\n");
        printf("    mode            Operation mode (ecb/cbc)\n");
        printf("    -a              Decode/Encode in base64 depending on encrypt mode\n");
        printf("    -d              Decryption option\n");
        printf("    -e              Encryption option (default)\n");
        printf("    -i  file        Path to input file\n");
        printf("    -o  file        Path to output file\n");
        printf("    -k  hex         Key in hexadecimal\n");
        printf("    -p  string      Password in ascii\n");
        printf("    -s  hex         Salt in hexadecimal\n");
        printf("    -v  hex         Initialization vextor in hexadecimal\n");
        printf("\nexamples:\n");
        printf("    ./ft_ssl des-ecb\n");
        printf("    ./ft_ssl des-ecb -i input.txt -k AAAABBBBCCCCDDDD\n");
        printf("    ./ft_ssl des-ecb -d -i input.txt -o output -k AAAABBBBCCCCDDDD\n");
        printf("    ./ft_ssl des-ecb -e -i input.txt -p password\n");
        printf("    ./ft_ssl des-ecb -e -i input.txt -p password -s AAAABBBBCCCCDDDD\n");
        printf("    ./ft_ssl des-cbc -e -i input.txt -o output.txt -p password -s AAAABBBBCCCCDDDD -v AAAABBBBCCCCDDDD\n");
        printf("    ./ft_ssl des-cbc -d -i output.txt -p password -s AAAABBBBCCCCDDDD -v AAAABBBBCCCCDDDD\n");
        printf("    echo -n \"hello world\" | ./ft_ssl des-cbc -k AAAABBBBCCCCDDDD\n");
    }
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