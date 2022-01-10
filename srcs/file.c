#include "../incs/des.h"

void    bytes_join(t_message *msg, char *buf, u_int64_t buf_length)
{
    char    *new_msg;

    if (!(new_msg = (char *)malloc(msg->rc_size + buf_length)))
        fatal_error(msg, "File bytes memory allocation");
    bzero(new_msg, (msg->rc_size + buf_length));

    memcpy(new_msg, msg->input, msg->rc_size);
    memcpy(&(new_msg[msg->rc_size]), buf, buf_length);

    if (msg->input)
        free(msg->input);
    msg->input = new_msg;
    msg->rc_size += buf_length;
}

int32_t     get_file(t_message *msg, char *path, u_int8_t type)
{
    int32_t fd;

    if (type == INPUT)
    {
        if ((fd = open(path, O_RDONLY)) == -1)
            fatal_error(msg, "file opening");
    }
    else
    {
        if ((fd = open(path, O_WRONLY | O_CREAT, 0644)) == -1)
            fatal_error(msg, "file opening");
    }
    return (fd);
}

void get_file_content(t_message *msg, int32_t fd)
{
    ssize_t     ret;
    char        buf[65535];

    bzero(&buf[0], 65535);
    while ((ret = read(fd, buf, 65534)) > 0) {
        buf[ret] = '\0';
        bytes_join(msg, &buf[0], ret);
        bzero(&buf[0], 65535);
    }
    if (ret == -1)
        fatal_error(msg, "file reading");
}

void get_content(t_message *msg, t_args *args)
{
    if (args->i == FALSE)
        get_file_content(msg, STDIN_FILENO);
    else
        get_file_content(msg, get_file(msg, args->input_path, INPUT));
}

void add_output_fd(t_args *args, t_message *msg)
{
    if (args->o == TRUE)
        msg->output_fd = get_file(msg, args->output_path, OUTPUT);
    else
        msg->output_fd = 1;
}