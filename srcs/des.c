#include "../incs/des.h"

// char *

void permute(char *bin, char *per_bin, int *array, int size)
{
	for (int count = 0; count < size; count++)
    {
		per_bin[count] += bin[array[count] - 1];
	}
}

void tobinary(char *pt, char *bin_pt, int bytes_size)
{
    int count = 0;
    for (int bytes = 0; bytes < bytes_size; bytes++)
    {
        printf("bytes = %d\n", bytes);
        for (int bits = 7; bits >= 0; bits--)
        {
            printf("((pt[bytes] >> bits) & 0b00000001) = %d\n", ((pt[bytes] >> bits) & 0b00000001));
            if (((pt[bytes] >> bits) & 0b00000001) == 0)
                bin_pt[count] = '0';
            else if (((pt[bytes] >> bits) & 0b00000001) == 1)
                bin_pt[count] = '1';
            count++;
        }
    }
}

void sboxes_tobinary(int result, char *bin_pt)
{
    int count = 0;

    for (int bits = 3; bits >= 0; bits--)
    {
        if (((result >> bits) & 0b00000001) == 0)
            bin_pt[count] = '0';
        else if (((result >> bits) & 0b00000001) == 1)
            bin_pt[count] = '1';
        count++;
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
    tobinary(pt, &bin_pt[0], 8);

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
    tobinary(key, &bin_key[0], 8);
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

        
        int s_boxes[8][64] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                            0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                            4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                            15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
                            { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                            3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                            0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                            13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },

                            { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                            13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                            13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                            1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
                            { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                            13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                            10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                            3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
                            { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                            14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                            4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                            11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
                            { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                            10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                            9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                            4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
                            { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                            13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                            1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                            6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
                            { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                            1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                            7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                            2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };
        
        
        
        int x, y;


        char s_boxes_result[32];
        bzero(&s_boxes_result[0], 32);


        for (int count = 0; count < 8; count++)
        {
            if (exp_pt[count * 6] == '0')
            {
                if (exp_pt[(count * 6) + 5] == '0')
                    x = 0;
                else
                    x = 1;
            }
            else
            {
                if (exp_pt[(count * 6) + 5] == '0')
                    x = 3;
                else
                    x = 4;
            }

            if (exp_pt[(count * 6) + 1] == '0')
            {
                if (exp_pt[(count * 6) + 2] == '0')
                {
                    if (exp_pt[(count * 6) + 3] == '0')
                    {
                        if (exp_pt[(count * 6) + 4] == '0')
                            y = 0;
                        else
                            y = 1;
                    }
                    else
                    {
                        if (exp_pt[(count * 6) + 4] == '0')
                            y = 2;
                        else
                            y = 3;
                    }
                }
                else
                {
                    if (exp_pt[(count * 6) + 3] == '0')
                    {
                        if (exp_pt[(count * 6) + 4] == '0')
                            y = 4;
                        else
                            y = 5;
                    }
                    else
                    {
                        if (exp_pt[(count * 6) + 4] == '0')
                            y = 6;
                        else
                            y = 7;
                    }
                }
            }
            else
            {
                if (exp_pt[(count * 6) + 2] == '0')
                {
                    if (exp_pt[(count * 6) + 3] == '0')
                    {
                        if (exp_pt[(count * 6) + 4] == '0')
                            y = 8;
                        else
                            y = 9;
                    }
                    else
                    {
                        if (exp_pt[(count * 6) + 4] == '0')
                            y = 10;
                        else
                            y = 11;
                    }
                }
                else
                {
                    if (exp_pt[(count * 6) + 3] == '0')
                    {
                        if (exp_pt[(count * 6) + 4] == '0')
                            y = 12;
                        else
                            y = 13;
                    }
                    else
                    {
                        if (exp_pt[(count * 6) + 4] == '0')
                            y = 14;
                        else
                            y = 15;
                    }
                }
            }

            // printf("s_boxes[count][(16 * x) + y] = %d\n", s_boxes[count][(16 * x) + y]);
            sboxes_tobinary(s_boxes[count][(16 * x) + y], &s_boxes_result[count * 4]);
            // print_binary_str(&s_boxes_result[0], "s_boxes_result", 32);
            


        }

        // --------------- STRAIGHT PERMUTATION


        int per[32] = { 16, 7, 20, 21,
                    29, 12, 28, 17,
                    1, 15, 23, 26,
                    5, 18, 31, 10,
                    2, 8, 24, 14,
                    32, 27, 3, 9,
                    19, 13, 30, 6,
                    22, 11, 4, 25 };

        char p_box_result[32];
        bzero(&p_box_result[0], 32);


        permute(&s_boxes_result[0], &p_box_result[0], &per[0], 32);

        print_binary_str(&p_box_result[0], "p_box_result", 32);
    }



}