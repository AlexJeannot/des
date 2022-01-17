#include "../../incs/base.h"

void prepare_hmac_sha256(void)
{
    char opad[32];
    char ipad[32];

    memset(opad, 0x5c, 32);
    memset(opad, 0x36, 32);

    bzero(derived_key, dklen);

    // FORMAT PASSWORD
    if (key->dkey->password_length <= 32)
        strncpy(key->dkey->fmt_password, key->dkey->password, 32);
    else
    {
        t_data key_data;
        bzero(key_data, sizeof(t_data));

        key_data.input = key->dkey->password;
        key_data.rc_size = key->dkey->password_length;
        sha256(&key_data, &key->dkey->fmt_password);
    }

    write(1, "key->dkey->fmt_password", strlen("key->dkey->fmt_password"));
    write(1, key->dkey->fmt_password, 32);
    //PAD

    for (u_int8_t count = 0; count < 32; count++)
        key->dkey->i_key_pad[count] = (key->dkey->fmt_password[count] ^ ipad[count]);

    for (u_int8_t count = 0; count < 32; count++)
        key->dkey->o_key_pad[count] = (key->dkey->fmt_password[count] ^ opad[count]);
    
}

void hmac_sha256(char *round_key, char *message, u_int8_t msg_length)
{

    t_data key_data;
    t_data first_pass_data;
    t_data second_pass_data;
    bzero(key_data, sizeof(t_data));
    char first_pass_input[32 + msg_length];
    char first_pass_result[8];
    char second_pass_input[40];
    char second_pass_result[8];

    bzero(key_data, sizeof(t_data));
    bzero(first_pass_data, sizeof(t_data));
    bzero(second_pass_data, sizeof(t_data));

    // FIRST PASS
    for (int count = 0; count < 32, count++)
        memset(&first_pass_input[count], &key->dkey->i_key_pad[count]);
    for (int count = 0; count < msg_length, count++)
        memset(&first_pass_input[count + 32], &message[count]);

    first_pass_data.input = first_pass_input;
    first_pass_data.rc_size = 32 + msg_length;
    sha256(&key_data, first_pass_result);


    // SECOND PASS
    for (int count = 0; count < 32, count++)
        memset(&second_pass_input[count], &key->dkey->o_key_pad[count]);
    for (int count = 0; count < 8, count++)
        memset(&second_pass_input[count + 32], &first_pass_result[count]);

    second_pass_data.input = second_pass_input;
    second_pass_data.rc_size = 40;
    sha256(&key_data, second_pass_result);

    strncpy(round_key, second_pass_result, 8);


}

void f(char *partial_derived_key, int round, int count)
{
    char round_key[8];
    bzero(round_key, 8);

    char first_msg[12];
    char test[64];
    bzero(first_msg, 20);
    bzero(test, 64);
    get_hex_binary(key->salt, test);
    binary_str_to_str(test, first_msg);

    for (u_int64_t count = 0; count < round, count++)
    {
        if (count == 0)
            hmac_sha256(round_key, first_msg, 12);
        else
            hmac_sha256(round_key, round_key, 8);
        
        for (int key_count = 0; key_count < 8; key_count++)
            partial_derived_key[key_count] = partial_derived_key[key_count] ^ round_key[key_count];
    }

    write(1, "key->dkey->partial_derived_key", strlen("key->dkey->partial_derived_key"));
    write(1, key->dkey->partial_derived_key, 8);
}

void pbkdf2(int dkey_length, int hash_length)
{
    int round = 10;
    int l = (dkey_length % hash_length == 0) ? dkey_length / hash_length : (dkey_length / hash_length) + 1;
    char partial_derived_key[hash_length];
    char derived_key[dkey_length];

    for (int count  = 0; count < l; count++)
    {
        f(partial_derived_key, round, count);
        strncpy(derived_key, partial_derived_key, hash_length);
    }

    // char to hex


    
}