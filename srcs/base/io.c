#include "../../incs/base.h"

void    process_string(char *input)
{
    t_data  *new_data;

    create_data(&new_data);
    new_data->rc_size = strlen(input);
    if (!(new_data->input = (char *)malloc(new_data->rc_size)))
        fatal_error("string input memory allocation");
    bzero(new_data->input, new_data->rc_size);

    strncpy(new_data->input, input, new_data->rc_size);
    new_data->src_type = SRC_ARG;

    organize_data(new_data);
}

void    process_stdin(void)
{
    t_data  *new_data;

    create_data(&new_data);
    get_file_content(new_data, STDIN_FILENO);
    new_data->src_type = SRC_STDIN;

    new_data->next = data;
    data = new_data;
}

void    process_file(char *file_path, u_int8_t type)
{
    t_data  *new_data;
    int32_t fd;

    new_data = NULL;
    if (type == INPUT)
    {
        create_data(&new_data);
        if ((fd = get_file(new_data, file_path, INPUT)) != -1)
            get_file_content(new_data, fd);
        if (is_hash_algorithm())
            set_file_context(new_data, file_path);
        organize_data(new_data);
        args->i = TRUE;
    }
    else
    {
        args->output_fd = get_file(new_data, file_path, OUTPUT);
        args->o = TRUE;
    }
}