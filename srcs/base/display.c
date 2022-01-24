#include "../../incs/base.h"

void    display_help(void)
{
    ft_putstr_fd("\nEncoding commands:\n", 2);
    ft_putstr_fd("base64\n", 2);
    ft_putstr_fd("\nMessage digest commands:\n", 2);
    ft_putstr_fd("md5\n", 2);
    ft_putstr_fd("sha256\n", 2);
    ft_putstr_fd("\nCipher commands:\n", 2);
    ft_putstr_fd("des-ecb\n", 2);
    ft_putstr_fd("des-cbc\n", 2);

    if (args->algorithm == FALSE || args->algorithm == ALGO_BASE64)
    {
        ft_putstr_fd("\n> BASE64\n", 2);
        ft_putstr_fd("Usage: base64 [-d -e -n] [-i file] [-o file]\n", 2);
        ft_putstr_fd("    -d              Decode option\n", 2);
        ft_putstr_fd("    -e              Encode option (default)\n", 2);
        ft_putstr_fd("    -n              Add newline for encoding output\n", 2);
        ft_putstr_fd("    -i  file        Path to input file\n", 2);
        ft_putstr_fd("    -o  file        Path to output file\n", 2);
        ft_putstr_fd("\nexamples:\n", 2);
        ft_putstr_fd("    ./ft_ssl base64 -i input.txt\n", 2);
        ft_putstr_fd("    ./ft_ssl base64 -i input.txt -o output.txt\n", 2);
        ft_putstr_fd("    ./ft_ssl base64 -n -i input.txt -o output.txt\n", 2);
        ft_putstr_fd("    ./ft_ssl base64 -e -n -i input.txt -o output.txt\n", 2);
        ft_putstr_fd("    ./ft_ssl base64 -d -i input.txt -o output.txt\n", 2);
        ft_putstr_fd("    echo -n \"hello world\" | ./ft_ssl base64 -e\n", 2);
        ft_putstr_fd("    echo -n \"aGVsbG8gd29ybGQ=\" | ./ft_ssl base64 -d\n", 2);
    }

    if (args->algorithm == FALSE || is_hash_algorithm())
    {
        ft_putstr_fd("\n> MD5 / SHA256\n", 2);
        ft_putstr_fd("Usage: algorithm [-p -q -r] [-s string] [file...]\n", 2);
        ft_putstr_fd("    algorithm       Algorithm to hash input (md5/sha256)\n", 2);
        ft_putstr_fd("    file            files to digest\n", 2);
        ft_putstr_fd("    -p              Process STDIN input\n", 2);
        ft_putstr_fd("    -q              Quiet mode (output hash only)\n", 2);
        ft_putstr_fd("    -r              Reverse mode (output source after the hash)\n", 2);
        ft_putstr_fd("    -s              Process string\n", 2);
        ft_putstr_fd("\nexamples:\n", 2);
        ft_putstr_fd("    ./ft_ssl md5 file.txt\n", 2);
        ft_putstr_fd("    ./ft_ssl sha256 -s \"hello world\"\n", 2);
        ft_putstr_fd("    echo -n \"hello world\" | ./ft_ssl md5\n", 2);
        ft_putstr_fd("    echo -n \"hello world\" | ./ft_ssl sha256 -p file.txt\n", 2);
        ft_putstr_fd("    echo -n \"hello world\" | ./ft_ssl md5 -p -s \"hello world\" file.txt\n", 2);
    }

    if (args->algorithm == FALSE || args->algorithm == ALGO_DES)
    {
        ft_putstr_fd("\n> DES\n", 2);
        ft_putstr_fd("Usage: des-mode [-a -d -e] [-i file] [-o file] [-k hex] [-p string] [-s hex] [-v hex]\n", 2);
        ft_putstr_fd("    mode            Operation mode (ecb/cbc)\n", 2);
        ft_putstr_fd("    -a              Decode/Encode in base64 depending on encrypt mode\n", 2);
        ft_putstr_fd("    -d              Decryption option\n", 2);
        ft_putstr_fd("    -e              Encryption option (default)\n", 2);
        ft_putstr_fd("    -i  file        Path to input file\n", 2);
        ft_putstr_fd("    -o  file        Path to output file\n", 2);
        ft_putstr_fd("    -k  hex         Key in hexadecimal\n", 2);
        ft_putstr_fd("    -p  string      Password in ascii\n", 2);
        ft_putstr_fd("    -s  hex         Salt in hexadecimal\n", 2);
        ft_putstr_fd("    -v  hex         Initialization vextor in hexadecimal\n", 2);
        ft_putstr_fd("\nexamples:\n", 2);
        ft_putstr_fd("    ./ft_ssl des-ecb\n", 2);
        ft_putstr_fd("    ./ft_ssl des-ecb -i input.txt -k AAAABBBBCCCCDDDD\n", 2);
        ft_putstr_fd("    ./ft_ssl des-ecb -d -i input.txt -o output -k AAAABBBBCCCCDDDD\n", 2);
        ft_putstr_fd("    ./ft_ssl des-ecb -e -i input.txt -p password\n", 2);
        ft_putstr_fd("    ./ft_ssl des-ecb -e -i input.txt -p password -s AAAABBBBCCCCDDDD\n", 2);
        ft_putstr_fd("    ./ft_ssl des-cbc -e -i input.txt -o output.txt -p password -s AAAABBBBCCCCDDDD -v AAAABBBBCCCCDDDD\n", 2);
        ft_putstr_fd("    ./ft_ssl des-cbc -d -i output.txt -p password -s AAAABBBBCCCCDDDD -v AAAABBBBCCCCDDDD\n", 2);
        ft_putstr_fd("    echo -n \"hello world\" | ./ft_ssl des-cbc -k AAAABBBBCCCCDDDD\n", 2);
    }
}

void    display_src(const t_message_hash *msg)
{
    if (args->r)
        ft_putstr_fd(" ", 1);
    if (msg->src_type == SRC_STDIN && args->p)
    {
        ft_putstr_fd("(\"", 1);
        ft_putstr_fd(msg->src, 1);
        ft_putstr_fd("\")", 1);

    }
    else if (msg->src_type == SRC_STDIN)
        ft_putstr_fd("(stdin)", 1);
    else if (msg->src_type == SRC_ARG)
    {
        ft_putstr_fd("(\"", 1);
        ft_putstr_fd(msg->raw_content, 1);
        ft_putstr_fd("\")", 1);
    }
    else if (msg->src_type == SRC_FILE)
    {
        ft_putstr_fd("(", 1);
        ft_putstr_fd(msg->src, 1);
        ft_putstr_fd(")", 1);
    }
    if (!args->r)
        ft_putstr_fd(" = ", 1);
}

void    display_hash(const t_message_hash *msg)
{
    if (msg->nofile) {
        ft_putstr_fd("Error: no such file [", 1);
        ft_putstr_fd(msg->src, 1);
        ft_putstr_fd("]\n", 1);
        return ;
    }
    if (!args->q)
    {
        if (args->algorithm == ALGO_MD5)
            ft_putstr_fd("[MD5] ", 1);
        else if (args->algorithm == ALGO_SHA256)
            ft_putstr_fd("[SHA256] ", 1);
        
        if (!(args->r))
            display_src(msg);
    }

    ft_putstr_fd(msg->hash, 1);

    
    if (!args->q && args->r)
        display_src(msg);
    ft_putstr_fd("\n", 1);
}