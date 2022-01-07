#ifndef DES
# define DES

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <strings.h>
# include <string.h>

typedef struct  s_keys
{
    char *origin_key;
    char round_keys[16][48];
}               t_keys;


void create_all_round_keys(t_keys *keys);
void permute(char *bin, char *per_bin, int *array, int size);
void hexadecimal_to_binary(char *key, char *binkey);

#endif