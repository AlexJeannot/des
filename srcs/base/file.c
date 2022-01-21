#include "../../incs/base.h"

void        bytes_join(t_data *current_data, char *buf, u_int64_t buf_length)
{
    char    *new_content;

    if (!(new_content = (char *)malloc(current_data->rc_size + buf_length)))
        fatal_error("file bytes memory allocation");
    bzero(new_content, (current_data->rc_size + buf_length));

    memcpy(new_content, current_data->input, current_data->rc_size);
    memcpy(&(new_content[current_data->rc_size]), buf, buf_length);

    if (current_data->input)
        free(current_data->input);
    current_data->input = new_content;
    current_data->rc_size += buf_length;
}

int32_t     get_file(t_data *new_data, char *file_path, u_int8_t type)
{
    int32_t fd;

    if (type == INPUT)
    {
        if ((fd = open(file_path, O_RDONLY)) == -1)
        {
            if (is_hash_algorithm())
                new_data->nofile = TRUE;
            else
                fatal_error("input file opening");
        }
    }
    else
    {
        if ((fd = open(file_path, O_WRONLY | O_CREAT, 0644)) == -1)
            fatal_error("output file opening/creation");
    }
    
    return (fd);
}

void        get_file_content(t_data *current_data, int32_t fd)
{
    ssize_t     ret;
    char        buf[65535];

    bzero(&buf[0], 65535);
    while ((ret = read(fd, buf, 65534)) > 0) {
        buf[ret] = '\0';
        bytes_join(current_data, &buf[0], ret);
        bzero(&buf[0], 65535);
    }
    if (ret == -1)
        fatal_error("file reading");
}

void        set_file_context(t_data *new_data, char *file_path)
{
    new_data->src_type = SRC_FILE;
    
    if (!(new_data->src = (char *)malloc(strlen(file_path) + 1)))
        fatal_error("file source memory allocation");
    bzero(new_data->src, (strlen(file_path) + 1));

    strncpy(new_data->src, file_path, strlen(file_path));
}