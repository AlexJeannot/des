#include "../../incs/base64.h"

// void        clean_msg(t_message_base64 *msg)
// {
//     u_int8_t content_similar;

//     content_similar = (msg->raw_content == msg->fmt_content) ? TRUE : FALSE;
//     if (msg->raw_content)
//         free(msg->raw_content);
//     if (msg->fmt_content && !content_similar)
//         free(msg->fmt_content);
// }