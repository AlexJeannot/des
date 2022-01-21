#include "../../incs/base.h"

void    bin_str_to_str(char *binary_str, char *str, u_int64_t binary_size)
{
    u_int64_t   size;

    size = binary_size / 8;
    for (u_int64_t bytes = 0; bytes < size; bytes++)
    {
        for (u_int8_t bits = 0; bits < 8; bits++)
        {
            str[bytes] = str[bytes] << 1;
            str[bytes] = str[bytes] | (binary_str[(bytes * 8) + bits] - 48);
        }
    }
}

void    str_to_bin_str(char *input, char *output, u_int64_t input_size, u_int64_t output_size)
{
    u_int8_t    count;

    count = 0;
    for (u_int64_t bytes = 0; bytes < output_size; bytes++)
    {
        if (input_size == 0)
        {
            add_padding(&output[count], bytes, output_size);
            return ;
        }

        for (int8_t bits = 7; bits >= 0; bits--)
        {
            if (((input[bytes] >> bits) & 1) == 0)
                output[count] = '0';
            else if (((input[bytes] >> bits) & 1) == 1)
                output[count] = '1';
            count++;
        }
        if (input_size > 0)
            input_size--;
    }
}

char    get_hex_char(u_int8_t input)
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

void    str_to_hex_str(char *str, char *hex_str, u_int64_t size)
{
    u_int64_t   hex_count;

    hex_count = 0;
    for (u_int64_t count = 0; count < size; count++)
    {
        hex_str[hex_count++] = get_hex_char((str[count] & 0b11110000) >> 4);
        hex_str[hex_count++] = get_hex_char(str[count] & 0b00001111);
    }
}

void    hex_str_to_str(char *hex_str, char *str, u_int64_t hex_size)
{
    char    tmp[hex_size * 4];

    bzero(tmp, hex_size * 4);
    hex_str_to_bin_str(hex_str, tmp, hex_size);
    bin_str_to_str(tmp, str, hex_size * 4);
}

void    hex_str_to_bin_str(char *input, char *output, u_int64_t input_size)
{
    for (u_int64_t count = 0; count < input_size; count++)
    {
        switch(input[count])
        {
            case '0':   strcat(&output[0], "0000"); break;
            case '1':   strcat(&output[0], "0001"); break;
            case '2':   strcat(&output[0], "0010"); break;
            case '3':   strcat(&output[0], "0011"); break;
            case '4':   strcat(&output[0], "0100"); break;
            case '5':   strcat(&output[0], "0101"); break;
            case '6':   strcat(&output[0], "0110"); break;
            case '7':   strcat(&output[0], "0111"); break;
            case '8':   strcat(&output[0], "1000"); break;
            case '9':   strcat(&output[0], "1001"); break;
            case 'A':   strcat(&output[0], "1010"); break;
            case 'a':   strcat(&output[0], "1010"); break;
            case 'B':   strcat(&output[0], "1011"); break;
            case 'b':   strcat(&output[0], "1011"); break;
            case 'C':   strcat(&output[0], "1100"); break;
            case 'c':   strcat(&output[0], "1100"); break;
            case 'D':   strcat(&output[0], "1101"); break;
            case 'd':   strcat(&output[0], "1101"); break;
            case 'E':   strcat(&output[0], "1110"); break;
            case 'e':   strcat(&output[0], "1110"); break;
            case 'F':   strcat(&output[0], "1111"); break;
            case 'f':   strcat(&output[0], "1111"); break;
        }
    }
}