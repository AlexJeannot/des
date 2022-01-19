#include "../../incs/base.h"

void prepare_hmac_sha256(void)
{
    char opad[64];
    char ipad[64];

    memset(opad, 0x5c, 64);
    memset(ipad, 0x36, 64);

    bzero(key->dkey.fmt_password, 64);
    if (key->dkey.password_length <= 64)
        strncpy(key->dkey.fmt_password, key->dkey.password, 64);
    else
    {
        t_data key_data;
        bzero(&key_data, sizeof(t_data));

        key_data.input = key->dkey.password;
        key_data.rc_size = key->dkey.password_length;
        bzero(key->dkey.hash_result, 64);
        bzero(key->dkey.fmt_password, 64);
        sha256(&key_data, key->dkey.hash_result);
        hex_to_str(key->dkey.hash_result, key->dkey.fmt_password, 64);
    }


    //PAD
    for (u_int8_t count = 0; count < 64; count++)
        key->dkey.i_key_pad[count] = (key->dkey.fmt_password[count] ^ ipad[count]);

    for (u_int8_t count = 0; count < 64; count++)
        key->dkey.o_key_pad[count] = (key->dkey.fmt_password[count] ^ opad[count]);
}

void hmac_sha256(char *round_key, char *message, u_int8_t msg_length)
{
    t_data first_pass_data;
    t_data second_pass_data;

    char first_pass_input[64 + msg_length];
    char first_pass_result[32];
    char second_pass_input[96];
    char second_pass_result[32];

    bzero(&first_pass_data, sizeof(t_data));
    bzero(&second_pass_data, sizeof(t_data));

    // FIRST PASS
    bzero(first_pass_input, 64 + msg_length);
    bzero(key->dkey.hash_result, 64);
    memcpy(&first_pass_input[0], &key->dkey.i_key_pad, 64);
    memcpy(&first_pass_input[64], message, msg_length);

    first_pass_data.input = first_pass_input;
    first_pass_data.rc_size = 64 + msg_length;
    sha256(&first_pass_data, key->dkey.hash_result);
    hex_to_str(key->dkey.hash_result, first_pass_result, 64);


    // SECOND PASS
    bzero(second_pass_input, 96);
    bzero(key->dkey.hash_result, 64);

    memcpy(&second_pass_input[0], &key->dkey.o_key_pad, 64);
    memcpy(&second_pass_input[64], first_pass_result, 32);

    second_pass_data.input = second_pass_input;
    second_pass_data.rc_size = 96;
    sha256(&second_pass_data, key->dkey.hash_result);
    hex_to_str(key->dkey.hash_result, second_pass_result, 64);

    memcpy(&round_key[0], &second_pass_result[0], 32);
}

void func(char *partial_derived_key, u_int64_t round)
{
    char round_key[32];
    bzero(round_key, 32);

    char first_msg[12];
    bzero(first_msg, 12);
    hex_to_str(key->dkey.salt, first_msg, 16);
    printf("first_msg = %s\n", first_msg);
    first_msg[11] = 0b00000001;
    for (u_int64_t count = 0; count < round; count++)
    {
        if (count == 0)
            hmac_sha256(round_key, first_msg, 12);
        else
            hmac_sha256(round_key, round_key, 32);
        
        for (int key_count = 0; key_count < 32; key_count++)
            partial_derived_key[key_count] = partial_derived_key[key_count] ^ round_key[key_count];
    }
}



void pbkdf2(int dkey_length, int hash_length)
{
    int round = 1000;
    int dk_count = 0;
    int l = (dkey_length % hash_length == 0) ? dkey_length / hash_length : (dkey_length / hash_length) + 1;
    char partial_derived_key[hash_length];
    char complete_derived_key[hash_length * l];
    char derived_key[dkey_length];

    prepare_hmac_sha256();

    bzero(partial_derived_key, hash_length);
    bzero(complete_derived_key, hash_length * l);
    bzero(derived_key, dkey_length);
    for (int count  = 0; count < l; count++)
    {
        func(partial_derived_key, round);
        for (int count2 = 0; count2 < hash_length; count2++)
            memset(&complete_derived_key[dk_count++], partial_derived_key[count2], 1);
    }

    
    char result[64];

    bzero(result, 64);
    str_to_hex(complete_derived_key, result, 32);
    write(1, result, 64);
    write(1, "\n", 1);
}