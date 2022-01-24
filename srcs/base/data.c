#include "../../incs/base.h"

void    clean_data(void)
{
    t_data  *tmp_data;

    while(data)
    {
        tmp_data = data;
        if (data->input)
            free(data->input);
        if (data->src)
            free(data->src);
        data = data->next;
        free(tmp_data);
    }
}

void    create_data(t_data **new_data)
{
    if (!(*new_data = (t_data *)malloc(sizeof(t_data))))
        fatal_error("data structure memory allocation");
    ft_bzero(*new_data, sizeof(t_data));
}

void    organize_data(t_data *new_data)
{
    t_data  *tmp_data;

    tmp_data = data;
    if (!data)
        data = new_data;
    else
    {
        while (tmp_data->next)
            tmp_data = tmp_data->next;
        tmp_data->next = new_data;
    }
}