#include "../../incs/des.h"

void add_padding(char *output, u_int64_t bytes, u_int64_t size)
{
    u_int8_t count;
    u_int8_t padding_value;

    count = 0;
    padding_value = size - bytes;
    for (; bytes < size; bytes++)
    {
        for (int8_t bits = 7; bits >= 0; bits--)
        {
            if (((padding_value >> bits) & 1) == 0)
                output[count] = '0';
            else if (((padding_value >> bits) & 1) == 1)
                output[count] = '1';
            count++;
        }
    }
}

void get_string_binary(char *input, char *output, u_int64_t input_size, u_int64_t output_size)
{
    u_int8_t count;

    count = 0;
    for (u_int64_t bytes = 0; bytes < output_size; bytes++)
    {
        if (input_size == 0)
        {
            add_padding(&output[count], bytes, output_size);
            return ;
        }

        for (int bits = 7; bits >= 0; bits--)
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

void get_hex_binary(char *input, char *output)
{
    u_int64_t size;
    
    size = (input && output) ? strlen(input) : 0;
    for (u_int64_t count = 0; count < size; count++)
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

void get_sbox_binary(u_int8_t input, char *output)
{
    u_int8_t count;

    count = 0;
    for (int8_t bits = 3; bits >= 0; bits--)
    {
        if (((input >> bits) & 1) == 0)
            output[count] = '0';
        else if (((input >> bits) & 1) == 1)
            output[count] = '1';
        count++;
    }
}