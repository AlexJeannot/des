#include "../../incs/sha256.h"

static void init_buffers(t_buffers *buffers)
{
    bzero(buffers, sizeof(t_buffers));

    buffers->a = 0x6a09e667;
    buffers->b = 0xbb67ae85;
    buffers->c = 0x3c6ef372;
    buffers->d = 0xa54ff53a;
    buffers->e = 0x510e527f;
    buffers->f = 0x9b05688c;
    buffers->g = 0x1f83d9ab;
    buffers->h = 0x5be0cd19;
}

static void store_buffers(t_buffers *buffers, t_buffers *save_buffers)
{
    save_buffers->a = buffers->a;
    save_buffers->b = buffers->b;
    save_buffers->c = buffers->c;
    save_buffers->d = buffers->d;
    save_buffers->e = buffers->e;
    save_buffers->f = buffers->f;
    save_buffers->g = buffers->g;
    save_buffers->h = buffers->h;
}

static void add_buffers(t_buffers *buffers, t_buffers *save_buffers)
{
    buffers->a += save_buffers->a;
    buffers->b += save_buffers->b;
    buffers->c += save_buffers->c;
    buffers->d += save_buffers->d;
    buffers->e += save_buffers->e;
    buffers->f += save_buffers->f;
    buffers->g += save_buffers->g;
    buffers->h += save_buffers->h;
}

static void swap_buffers(t_buffers *buffers, u_int32_t t1, u_int32_t t2)
{   
    buffers->h = buffers->g;
    buffers->g = buffers->f;
    buffers->f = buffers->e;
    buffers->e = buffers->d + t1;
    buffers->d = buffers->c;
    buffers->c = buffers->b;
    buffers->b = buffers->a;
    buffers->a = t1 + t2;
}

static void process_round(t_buffers *buffers, u_int32_t block, u_int32_t count)
{
    u_int32_t t1;
    u_int32_t t2;

    t1 = buffers->h + bsig1(buffers->e) + ch(buffers->e, buffers->f, buffers->g) + sha256_computed_constants[count] + block;
    t2 = bsig0(buffers->a) + maj(buffers->a, buffers->b, buffers->c);

    swap_buffers(buffers, t1, t2);
}

void        process_msg_sha256(t_message *msg)
{
    t_buffers   buffers;
    t_buffers   save_buffers;
    u_int32_t   blocks[64];
    u_int32_t   *ptr_block;
    u_int32_t   block_offset;

    init_buffers(&buffers);
    while (msg->cc_size < msg->fc_size)
    {
        for (u_int32_t count = 0; count < 64; count++) {
            if (count < 16) {
                block_offset = msg->cc_size + (count * 4);
                ptr_block = (u_int32_t *)&msg->fmt_content[block_offset];
                blocks[count] = swap_uint_32(*ptr_block);
            }
            else
                blocks[count] = ssig1(blocks[count - 2]) + blocks[count - 7] + ssig0(blocks[count - 15]) + blocks[count - 16];
        }

        store_buffers(&buffers, &save_buffers);
        for (u_int32_t count = 0; count < 64; count++)
            process_round(&buffers, blocks[count], count);
        add_buffers(&buffers, &save_buffers);

        msg->cc_size += 64;
    }
    build_hash(msg, &buffers, 8, FALSE);
}