#include "../../incs/base.h"

void binary_str_to_str(char *binary_str, char *str, u_int64_t binary_size)
{
    u_int64_t size;

    size = binary_size / 8;
    for (u_int64_t bytes = 0; bytes < size; bytes++)
    {
        for (int bits = 0; bits < 8; bits++)
        {
            str[bytes] = str[bytes] << 1;
            str[bytes] = str[bytes] | (binary_str[(bytes * 8) + bits] - 48);
        }
    }
}

void print_bin(char *content, u_int64_t size)
{
    for (u_int64_t bytes = 0; bytes < size; bytes++)
    {
        for (int64_t bits = 7; bits >= 0; bits--)
        {
            printf("%c", (((content[bytes] >> bits) & 1) + 48));

        }
        printf(" ");
        if (bytes + 1 == 8)
            printf("\n");
    }
}

u_int8_t is_last_block(u_int64_t total_block, u_int64_t current_block)
{
    if (total_block == (current_block + 1))
        return (TRUE);
    return (FALSE);
}

char get_hex_char(u_int8_t input)
{
        switch(input)
        {
            case 0:     return ('0'); break;
            case 1:     return ('1'); break;
            case 2:     return ('2'); break;
            case 3:     return ('3'); break;
            case 4:     return ('4'); break;
            case 5:     return ('5'); break;
            case 6:     return ('6'); break;
            case 7:     return ('7'); break;
            case 8:     return ('8'); break;
            case 9:     return ('9'); break;
            case 10:    return ('A'); break;
            case 11:    return ('B'); break;
            case 12:    return ('C'); break;
            case 13:    return ('D'); break;
            case 14:    return ('E'); break;
            case 15:    return ('F'); break;
        }
        return '0';
}

void str_to_hex(char *str, char *hex_str, u_int64_t size)
{
    u_int64_t hex_count = 0;

    for (u_int64_t count = 0; count < size; count++)
    {
        hex_str[hex_count++] = get_hex_char((str[count] & 0b11110000) >> 4);
        hex_str[hex_count++] = get_hex_char(str[count] & 0b00001111);
    }
}

void hex_to_str(char *hex_str, char *str, u_int64_t hex_size)
{
    char tmp[hex_size * 4];

    bzero(tmp, hex_size * 4);
    get_hex_binary(hex_str, tmp, hex_size);
    binary_str_to_str(tmp, str, hex_size * 4);
}