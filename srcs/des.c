#include "../incs/des.h"

// char *


void print_binary_str(char *str, char *type, int size)
{
    printf("%s = ", type);
    fflush(stdout);
    write(1, str, size);
    printf("\n");
}


void permute(char *bin, char *per_bin, int *array, int size)
{
	for (int count = 0; count < size; count++)
    {
		per_bin[count] = bin[array[count] - 1];
	}
}

void tobinary(char *pt, char *bin_pt, int bytes_size)
{
    int count = 0;
    for (int bytes = 0; bytes < bytes_size; bytes++)
    {
        // printf("bytes = %d\n", bytes);
        for (int bits = 7; bits >= 0; bits--)
        {
            // printf("((pt[bytes] >> bits) & 0b00000001) = %d\n", ((pt[bytes] >> bits) & 0b00000001));
            if (((pt[bytes] >> bits) & 0b00000001) == 0)
                bin_pt[count] = '0';
            else if (((pt[bytes] >> bits) & 0b00000001) == 1)
                bin_pt[count] = '1';
            count++;
        }
    }
    printf("COUNT TO BINARY = %d\n", count);
}

void hexadecimal_to_binary(char *key, char *binkey)
{

	// mp['0'] = "0000";
	// mp['1'] = "0001";
	// mp['2'] = "0010";
	// mp['3'] = "0011";
	// mp['4'] = "0100";
	// mp['5'] = "0101";
	// mp['6'] = "0110";
	// mp['7'] = "0111";
	// mp['8'] = "1000";
	// mp['9'] = "1001";
	// mp['A'] = "1010";
	// mp['B'] = "1011";
	// mp['C'] = "1100";
	// mp['D'] = "1101";
	// mp['E'] = "1110";
	// mp['F'] = "1111";

    int size = strlen(key);
    for (int count = 0; count < size; count++)
    {
        switch(key[count])
        {
            case '0':   strcat(&binkey[0], "0000"); break;
            case '1':   strcat(&binkey[0], "0001"); break;
            case '2':   strcat(&binkey[0], "0010"); break;
            case '3':   strcat(&binkey[0], "0011"); break;
            case '4':   strcat(&binkey[0], "0100"); break;
            case '5':   strcat(&binkey[0], "0101"); break;
            case '6':   strcat(&binkey[0], "0110"); break;
            case '7':   strcat(&binkey[0], "0111"); break;
            case '8':   strcat(&binkey[0], "1000"); break;
            case '9':   strcat(&binkey[0], "1001"); break;
            case 'A':   strcat(&binkey[0], "1010"); break;
            case 'B':   strcat(&binkey[0], "1011"); break;
            case 'C':   strcat(&binkey[0], "1100"); break;
            case 'D':   strcat(&binkey[0], "1101"); break;
            case 'E':   strcat(&binkey[0], "1110"); break;
            case 'F':   strcat(&binkey[0], "1111"); break;
        }
    }
}

void xor_bits(char *pt_a, char *pt_b, char *result, int size)
{
    for (int count = 0; count < size; count++)
    {
        if (pt_a[count] == pt_b[count])
            result[count] = '0';
        else
            result[count] = '1';
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
    printf("sboxes int = %d\n", result);
    print_binary_str(&bin_pt[0], "sboxes bin", 4);
}

int is_one_shift_round(int round)
{
    return (round == 1 || round == 2 || round == 9 || round == 16);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    char bin_pt[64];
    bzero(&bin_pt[0], 64);

    char *pt = "ABCDEFGH";
    tobinary(pt, &bin_pt[0], 8);
    // char *pt = "123456ABCD132536";
    // hex2bin(pt, &bin_pt[0]);


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
    char *key = "AABBCCDDEEFF1122";
    // char *key = "133457799BBCDFF1";

    t_keys keys;

    bzero(&keys, sizeof(t_keys));
    keys.origin_key = key;

    create_all_round_keys(&keys);

    // char round_key[48]; 

    // char all_round_keys[16][48];

    // for (int round = 1; round <= 16; round++)
    // {
    //     printf("------------------- ROUND %d ----------------------\n", round);
    //     // print_binary_str(trunc_bin_key, "round trunc_bin_key", 56);
    //     set_round_key(trunc_bin_key, round_key, round);
    //     strncpy(&all_round_keys[round - 1][0], round_key, 48);
    //     print_binary_str(round_key, "round_key", 48);
    //     printf("\n");

    // }
    // printf("--------------------------------------------------\n");

    // ------------------------------------ END KEYS -----------------------------------








    // ------------------------------------ DES FUNCTION -----------------------------------

    char pt_a[32];
    char pt_b[32];
    strncpy(&pt_a[0], &per_bin_pt[0], 32);
    strncpy(&pt_b[0], &per_bin_pt[32], 32);

    print_binary_str(pt_a, "pt_a", 32);
    print_binary_str(pt_b, "pt_b", 32);

    char exp_pt[48];
    char xor_result_second[48];

    for (int round = 0; round < 16; round++)
    {
        
        printf("\n----------------------------- ROUND %d ---------------------------------\n", round + 1);
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



        // ------------------------- XOR

        char xor_result[48];
        bzero(&xor_result[0], 48);

        xor_bits(&exp_pt[0], &keys.round_keys[round][0], &xor_result[0], 48);
        
        // print_binary_str(&all_round_keys[round][0], "all_round_keys", 48);
        // print_binary_str(&xor_result[0], "xor_result", 48);


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
            if (xor_result[count * 6] == '0')
            {
                if (xor_result[(count * 6) + 5] == '0')
                    x = 0;
                else
                    x = 1;
            }
            else
            {
                if (xor_result[(count * 6) + 5] == '0')
                    x = 2;
                else
                    x = 3;
            }

            if (xor_result[(count * 6) + 1] == '0')
            {
                if (xor_result[(count * 6) + 2] == '0')
                {
                    if (xor_result[(count * 6) + 3] == '0')
                    {
                        if (xor_result[(count * 6) + 4] == '0')
                            y = 0;
                        else
                            y = 1;
                    }
                    else
                    {
                        if (xor_result[(count * 6) + 4] == '0')
                            y = 2;
                        else
                            y = 3;
                    }
                }
                else
                {
                    if (xor_result[(count * 6) + 3] == '0')
                    {
                        if (xor_result[(count * 6) + 4] == '0')
                            y = 4;
                        else
                            y = 5;
                    }
                    else
                    {
                        if (xor_result[(count * 6) + 4] == '0')
                            y = 6;
                        else
                            y = 7;
                    }
                }
            }
            else
            {
                if (xor_result[(count * 6) + 2] == '0')
                {
                    if (xor_result[(count * 6) + 3] == '0')
                    {
                        if (xor_result[(count * 6) + 4] == '0')
                            y = 8;
                        else
                            y = 9;
                    }
                    else
                    {
                        if (xor_result[(count * 6) + 4] == '0')
                            y = 10;
                        else
                            y = 11;
                    }
                }
                else
                {
                    if (xor_result[(count * 6) + 3] == '0')
                    {
                        if (xor_result[(count * 6) + 4] == '0')
                            y = 12;
                        else
                            y = 13;
                    }
                    else
                    {
                        if (xor_result[(count * 6) + 4] == '0')
                            y = 14;
                        else
                            y = 15;
                    }
                }
            }

            printf("x = %d --- y = %d\n", x, y);
            // printf("s_boxes[count][(16 * x) + y] = %d\n", s_boxes[count][(16 * x) + y]);
            sboxes_tobinary(s_boxes[count][(16 * x) + y], &s_boxes_result[count * 4]);
            // print_binary_str(&s_boxes_result[0], "s_boxes_result", 32);
            


        }
        print_binary_str(&s_boxes_result[0], "s_boxes_result", 32);

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

        // ------------------------- XOR


        bzero(&xor_result_second[0], 48);

        xor_bits(&p_box_result[0], &pt_a[0], &xor_result_second[0], 32);


        char tmp[32];
        bzero(&tmp[0], 32);

        if (round != 15)
        {
            printf("SWAP!\n");
            strncpy(&tmp[0], &xor_result_second[0], 32);
            strncpy(&pt_a[0], &pt_b[0], 32);
            strncpy(&pt_b[0], &xor_result_second[0], 32);
        }
    }

    print_binary_str(&pt_a[0], "pt_a", 32);
    print_binary_str(&pt_b[0], "pt_b", 32);

    char final_result[64];
    bzero(&final_result[0], 64);

    strncpy(&final_result[0], &xor_result_second[0], 32);
    strncpy(&final_result[32], &pt_b[0], 32);

    int final_perm[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
                           39, 7, 47, 15, 55, 23, 63, 31,
                           38, 6, 46, 14, 54, 22, 62, 30,
                           37, 5, 45, 13, 53, 21, 61, 29,
                           36, 4, 44, 12, 52, 20, 60, 28,
                           35, 3, 43, 11, 51, 19, 59, 27,
                           34, 2, 42, 10, 50, 18, 58, 26,
                           33, 1, 41, 9, 49, 17, 57, 25 };


    char final_permutation[64];
    bzero(&final_permutation[0], 64);

    permute(&final_result[0], &final_permutation[0], &final_perm[0], 64);

    print_binary_str(&final_permutation[0], "final_permutation", 64);
    
    char res[9];
    bzero(&res[0], 9);

    int final_counter = 0;

    for (int bytes = 0; bytes < 8; bytes++)
    {
        for (int bits = 0; bits < 8; bits++)
        {
            // printf("final_permutation[final_counter]- 48 = %d\n", final_permutation[final_counter] - 48);
            res[bytes] = res[bytes] | (final_permutation[final_counter] - 48);
            // printf("res[bytes] = %c\n", res[bytes]);
            if (bits != 7)
                res[bytes] = res[bytes] << 1;
            final_counter++;
        }
    }

    write(1, "\0", 1);
    printf("res =\n");
    write(1, res, 8);
    printf("\n");
    for (int count = 0; count < 8; count++)
    {
        printf("res[%d] = %d  ---- %c\n", count, (int8_t)res[count], res[count]);
    }
}