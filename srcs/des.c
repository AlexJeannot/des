#include "../incs/des.h"

// char *

void permute(char *bin, char *per_bin, int *array, int size)
{
	for (int count = 0; count < size; count++)
    {
		per_bin[count] += bin[array[count] - 1];
	}
}

void tobinary(char *pt, char *bin_pt)
{
    int count = 0;
    for (int bytes = 0; bytes < 8; bytes++)
    {
        for (int bits = 7; bits >= 0; bits--)
        {
            if (((pt[bytes] >> bits) & 0b00000001) == 0)
                bin_pt[count] = '0';
            else if (((pt[bytes] >> bits) & 0b00000001) == 1)
                bin_pt[count] = '1';
            count++;
        }
    }
}

void print_binary_str(char *str, char *type, int size)
{
    printf("%s = ", type);
    fflush(stdout);
    write(1, str, size);
    printf("\n");
}

int is_one_shift_round(int round)
{
    return (round == 1 || round == 2 || round == 9 || round == 16);
}

void set_round_key(char *key, char *round_key, int round)
{
    int key_comp[48] = { 14, 17, 11, 24, 1, 5,
                         3, 28, 15, 6, 21, 10,
                         23, 19, 12, 4, 26, 8,
                         16, 7, 27, 20, 13, 2,
                         41, 52, 31, 37, 47, 55,
                         30, 40, 51, 45, 33, 48,
                         44, 49, 39, 56, 34, 53,
                         46, 42, 50, 36, 29, 32 };

    char tmp_key[56];
    char tmp_key_a[28];
    char tmp_key_b[28];

    bzero(&tmp_key[0], 56);
    bzero(&round_key[0], 48);

    if (is_one_shift_round(round))
    {
        strncpy(&tmp_key_a[0], &key[1], 27);
        strncpy(&tmp_key_a[27], &key[0], 1);

        strncpy(&tmp_key_b[0], &key[29], 27);
        strncpy(&tmp_key_b[27], &key[28], 1);
    }
    else
    {
        strncpy(&tmp_key_a[0], &key[2], 26);
        strncpy(&tmp_key_a[26], &key[0], 2);

        strncpy(&tmp_key_b[0], &key[30], 26);
        strncpy(&tmp_key_b[26], &key[28], 2);
    }

    strncpy(&tmp_key[0], &tmp_key_a[0], 28);
    strncpy(&tmp_key[28], &tmp_key_b[0], 28);

    strncpy(&key[0], &tmp_key[0], 56);

    permute(&tmp_key[0], &round_key[0], &key_comp[0], 48);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    char bin_pt[64];
    bzero(&bin_pt[0], 64);

    char *pt = "ABCDEFGH";
    tobinary(pt, &bin_pt[0]);

    print_binary_str(bin_pt, "bin_pt", 64);


	int initial_perm[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
							60, 52, 44, 36, 28, 20, 12, 4,
							62, 54, 46, 38, 30, 22, 14, 6,
							64, 56, 48, 40, 32, 24, 16, 8,
							57, 49, 41, 33, 25, 17, 9, 1,
							59, 51, 43, 35, 27, 19, 11, 3,
							61, 53, 45, 37, 29, 21, 13, 5,
							63, 55, 47, 39, 31, 23, 15, 7 };
    
    char per_bin_pt[64];
    bzero(&per_bin_pt[0], 64);
    permute(&bin_pt[0], &per_bin_pt[0], &initial_perm[0], 64);
    print_binary_str(per_bin_pt, "per_bin_pt", 64);

    // ------------------------------------ KEYS -----------------------------------
    char *key = "12345678";
    char bin_key[64];
    bzero(&bin_key[0], 64);
    tobinary(key, &bin_key[0]);
    print_binary_str(bin_key, "bin_key", 64);

    char trunc_bin_key[56];
    bzero(&trunc_bin_key[0], 56);

    int count2 = 0;
    for (int count = 1; count <= 64; count++)
    {
        if (count % 8 != 0)
            trunc_bin_key[count2++] = bin_key[count - 1];
    }
    print_binary_str(trunc_bin_key, "trunc_bin_key", 56);

    char round_key[48]; 

    char all_round_keys[16][48];

    for (int round = 1; round <= 16; round++)
    {

        set_round_key(trunc_bin_key, round_key, round);
        strncpy(&all_round_keys[round - 1][0], round_key, 48);
        print_binary_str(round_key, "round_key", 48);

    }

    // ------------------------------------ END KEYS -----------------------------------








    // ------------------------------------ DES FUNCTION -----------------------------------

    char pt_a[32];
    char pt_b[32];
    strncpy(&pt_a[0], &per_bin_pt[0], 32);
    strncpy(&pt_b[0], &per_bin_pt[32], 32);

    print_binary_str(pt_a, "pt_a", 32);
    print_binary_str(pt_b, "pt_b", 32);

    char exp_pt[48];

    for (int round = 0; round < 16; round++)
    {

        // --------------- EXPANSION PERMUTATION 

        bzero(&exp_pt[0], 48);
        int exp_d[48] = { 32, 1, 2, 3, 4, 5, 4, 5,
                            6, 7, 8, 9, 8, 9, 10, 11,
                            12, 13, 12, 13, 14, 15, 16, 17,
                            16, 17, 18, 19, 20, 21, 20, 21,
                            22, 23, 24, 25, 24, 25, 26, 27,
                            28, 29, 28, 29, 30, 31, 32, 1 };

        permute(&pt_b[0], &exp_pt[0], &exp_d[0], 48);
        print_binary_str(exp_pt, "exp_pt", 48);


        // --------------- S BOXES

        

    }

}