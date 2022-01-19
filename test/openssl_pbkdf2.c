#include <openssl/evp.h>
#include <openssl/sha.h>
// crypto.h used for the version
#include <openssl/crypto.h>

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

void PBKDF2_HMAC_SHA_256(const char* pass, const unsigned char* salt, int32_t iterations, uint32_t outputBytes)
 {
    //  unsigned int i;
    unsigned char digest[outputBytes];
    char hex_digest[outputBytes * 2];

    PKCS5_PBKDF2_HMAC(pass, strlen(pass), salt, 8, iterations, EVP_sha256(), outputBytes, digest);

    bzero(hex_digest, outputBytes * 2);
    str_to_hex((char *)digest, hex_digest, outputBytes);
    write(1, hex_digest, outputBytes * 2);
 }

int main(void)
{
     const unsigned char salt[8] = "AAAABBBB";
     const char password[8] = "password";
     int32_t round = 10000;

    PBKDF2_HMAC_SHA_256(password, salt, round, 8);  
}