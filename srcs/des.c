#include "../incs/des.h"

// char *


void print_binary_str(char *str, char *type, int size)
{
    printf("%s = ", type);
    fflush(stdout);
    write(1, str, size);
    printf("\n");
}


void permute(char *bin, char *per_bin, const int *array, int size)
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

void xor_bits_string(char *pt_a, char *pt_b, char *result, int size)
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
    // hexadecimal_to_binary(pt, &bin_pt[0]);


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


    char *key = "AABBCCDDEEFF1122";
    // char *key = "133457799BBCDFF1";

    t_keys keys;

    bzero(&keys, sizeof(t_keys));
    keys.origin_key = key;

    create_all_round_keys(&keys);


    t_block block;
    bzero(&block, sizeof(t_block));

    strncpy(&block.left[0], &per_bin_pt[0], 32);
    strncpy(&block.right[0], &per_bin_pt[32], 32);

    for (u_int8_t round = 0; round < 16; round++)
        execute_round(&block, &keys, round);


    print_binary_str(&block.right[0], "pt_a", 32);
    print_binary_str(&block.left[0], "pt_b", 32);

    char final_result[64];
    bzero(&final_result[0], 64);

    strncpy(&final_result[0], &block.left[0], 32);
    strncpy(&final_result[32], &block.right[0], 32);

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