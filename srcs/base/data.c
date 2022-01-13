#include "../../incs/des.h"

void create_data(t_data **new_data)
{
    if (!(*new_data = (t_data *)malloc(sizeof(t_data))))
        fatal_error("data structure memory allocation");
    bzero(*new_data, sizeof(t_data));
}

void organize_data(t_data *new_data)
{
    t_data *tmp_data;

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