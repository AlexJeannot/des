#include "../../incs/sha256.h"

void    sha256(t_message *msg)
{
    format_msg(msg, TRUE);
    process_msg_sha256(msg);
}