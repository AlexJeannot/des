#include "../../incs/base.h"

void        prepare_hmac_sha256(void)
{
    t_data  key_data;
    char    opad[64];
    char    ipad[64];

    ft_bzero(&key_data, sizeof(t_data));
    ft_memset(opad, 0x5c, 64);
    ft_memset(ipad, 0x36, 64);

    if (key->dkey.password_length <= 64)
        ft_strncpy(key->dkey.fmt_password, key->dkey.password, 64);
    else
    {
        key_data.input = key->dkey.password;
        key_data.rc_size = key->dkey.password_length;
        ft_bzero(key->dkey.hash_result, 64);
        sha256(&key_data, key->dkey.hash_result);
        hex_str_to_str(key->dkey.hash_result, key->dkey.fmt_password, 64);
    }

    for (u_int8_t count = 0; count < 64; count++)
        key->dkey.i_key_pad[count] = (key->dkey.fmt_password[count] ^ ipad[count]);

    for (u_int8_t count = 0; count < 64; count++)
        key->dkey.o_key_pad[count] = (key->dkey.fmt_password[count] ^ opad[count]);
}

void        exec_sha256(char *message, char *output, u_int64_t message_size, u_int8_t type)
{
    t_data  exec_data;
    char    input[64 + message_size];

    ft_bzero(&exec_data, sizeof(t_data));
    ft_bzero(input, 64 + message_size);
    ft_bzero(output, 32);

    (type == HMAC_FIRST) ? ft_memcpy(&input[0], &key->dkey.i_key_pad, 64) : ft_memcpy(&input[0], &key->dkey.o_key_pad, 64);
    ft_memcpy(&input[64], message, message_size);

    exec_data.input = input;
    exec_data.rc_size = 64 + message_size;
    ft_bzero(key->dkey.hash_result, 64);
    sha256(&exec_data, key->dkey.hash_result);
    hex_str_to_str(key->dkey.hash_result, output, 64);
}

void        hmac_sha256(char *tmp_key, char *message, u_int8_t message_size)
{
    char first_result[32];

    exec_sha256(message, first_result, message_size, HMAC_FIRST);
    exec_sha256(first_result, tmp_key, 32, HMAC_SECOND);
}

void        set_first_message(char *first_message)
{
    ft_bzero(first_message, 12);
    hex_str_to_str(key->dkey.salt, first_message, 16);
    first_message[11] = 0b00000001;
}

static void f(char *partial_derived_key, u_int32_t hash_length, u_int64_t round)
{
    char tmp_key[32];
    char first_message[12];

    ft_bzero(tmp_key, 32);
    set_first_message(first_message);

    for (u_int64_t count = 0; count < round; count++)
    {
        (count == 0) ? hmac_sha256(tmp_key, first_message, 12) : hmac_sha256(tmp_key, tmp_key, 32);
        for (u_int32_t key_count = 0; key_count < hash_length; key_count++)
            partial_derived_key[key_count] ^= tmp_key[key_count];
    }
}

void        pbkdf2(u_int32_t dkey_length, u_int32_t hash_length, u_int64_t round)
{
    u_int64_t   hash_length_block = dkey_length / hash_length;
    hash_length_block += (dkey_length % hash_length == 0) ? 0 : 1;

    char        partial_derived_key[hash_length];
    char        complete_derived_key[hash_length * hash_length_block];
    u_int64_t   dkey_count;

    ft_bzero(partial_derived_key, hash_length);
    ft_bzero(complete_derived_key, hash_length * hash_length_block);
    dkey_count = 0;

    ft_putstr_fd("Creating key, please wait ...\n", 1);
    prepare_hmac_sha256();
    for (u_int64_t count  = 0; count < hash_length_block; count++)
    {
        f(partial_derived_key, hash_length, round);
        ft_memcpy(&complete_derived_key[dkey_count], partial_derived_key, 32);
        dkey_count += hash_length;
    }
    str_to_hex_str(complete_derived_key, key->key, 32);
}