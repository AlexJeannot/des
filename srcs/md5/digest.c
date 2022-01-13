#include "../../incs/md5.h"

round_function r_func[4] = {&f, &g, &h, &i};

static void init_buffers(t_buffers *buffers)
{
    bzero(buffers, sizeof(t_buffers));

    buffers->a = 0x67452301;
    buffers->b = 0xefcdab89;
    buffers->c = 0x98badcfe;
    buffers->d = 0x10325476;
}

static void store_buffers(t_buffers *buffers, t_buffers *save_buffers)
{
    save_buffers->a = buffers->a;
    save_buffers->b = buffers->b;
    save_buffers->c = buffers->c;
    save_buffers->d = buffers->d;
}

static void swap_buffers(t_buffers *buffers)
{
    u_int32_t temp;
    
    temp = buffers->d;
    buffers->d = buffers->c;
    buffers->c = buffers->b;
    buffers->b = buffers->a;
    buffers->a = temp;
}

static void add_buffers(t_buffers *buffers, t_buffers *save_buffers)
{
    buffers->a += save_buffers->a;
    buffers->b += save_buffers->b;
    buffers->c += save_buffers->c;
    buffers->d += save_buffers->d;
}

static void process_round(t_buffers *buffers, u_int32_t block, u_int32_t round, u_int32_t count)
{
    buffers->a += r_func[round](buffers->b, buffers->c, buffers->d) + block + md5_computed_constants[count];
    buffers->a = (buffers->a << md5_constants[count]) | (buffers->a >> (32 - md5_constants[count]));
    buffers->a += buffers->b;

    swap_buffers(buffers);
}

void        process_msg_md5(t_message *msg)
{
    t_buffers   buffers;
    t_buffers   save_buffers;
    u_int32_t   blocks[16];
    u_int32_t   *ptr_block;
    u_int32_t   block_offset;
    u_int32_t   round;

    init_buffers(&buffers);
    while (msg->cc_size < msg->fc_size)
    {
        for (u_int32_t count = 0; count < 16; count++) {
            block_offset = msg->cc_size + (count * 4);
            ptr_block = (u_int32_t *)&msg->fmt_content[block_offset];
            blocks[count] = *ptr_block;
        }

        store_buffers(&buffers, &save_buffers);
        round = 0;
        for (u_int32_t count = 0; count < 64; count++) {
            if (count % 16 == 0 && count != 0)
                round += 1;
            process_round(&buffers, blocks[md5_blocks_constants[count]], round, count);
        }
        add_buffers(&buffers, &save_buffers);
        msg->cc_size += 64;
    }
    build_hash(msg, &buffers, 4, TRUE);
}