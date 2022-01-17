#include "../../incs/des.h"

u_int8_t    is_option(char *input)
{
    if (input && input[0] == '-')
        return (TRUE);
    return (FALSE);
}

void allocate_args(void)
{
    if (!(args = (t_args *)malloc(sizeof(t_args))))
        fatal_error("argument structure memory allocation");
    bzero(args, sizeof(t_args));
}

void allocate_key(void)
{
    if (!(key = (t_key *)malloc(sizeof(t_key))))
        fatal_error("argument structure memory allocation");
    bzero(key, sizeof(t_key));
}

void process_string(char *input)
{
    t_data   *new_data;

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
    t_data   *new_data;

    create_data(&new_data);
    get_file_content(new_data, STDIN_FILENO);
    new_data->src_type = SRC_STDIN;

    new_data->next = data;
    data = new_data;
}

void process_io(char *file_path, u_int8_t type)
{
    t_data *new_data;
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

void get_key(char *key)
{
    if (!(is_hexadecimal(key)))
        args_error("Not a hexadecimal key provided", NULL);

    if (!key)
        allocate_key();

    if (strlen(key) > 16)
        printf("Hexadecimal key is too long, ignoring excess\n");
    else if (strlen(key) < 16)
        printf("Hexadecimal key is too short, padding with zero bytes to length\n");

    strncpy(args->key, key, 16);
    args->k = TRUE;
}

void get_password(char *password)
{
    if (!key)
        allocate_key();

    key->password_length = (strlen(password) < 127) ? strlen(password) : 127;

    if (key->password_length > 127)
        printf("Password is too long (> 127 characters), ignoring excess\n");
    else if (key->password_length < 32)
        printf("Password is too short, padding with zero bytes to length\n");

    if (!(key->password = (char *)malloc(key->password_length)))
        fatal_error("string input memory allocation");
    bzero(key->password, key->password_length);
    strncpy(key->password, password, 127);

    args->p = TRUE;
}

void get_salt(char *salt)
{
    if (!(is_hexadecimal(salt)))
        args_error("Not a hexadecimal salt provided", NULL);

    if (!key)
        allocate_key();

    if (strlen(salt) > 16)
        printf("Password is too long, ignoring excess\n");
    else if (strlen(salt) < 16)
        printf("Password is too short, padding with zero bytes to length\n");

    strncpy(key->salt, salt, 16);
    args->s = TRUE;
}


void    get_algorithm(char *input)
{
    if (!input)
        args_error("No algorithm provided", NULL);

    if (strncmp(input, "des", 3) == 0)
        args->algorithm = ALGO_DES;
    else if (strncmp(input, "base64", 6) == 0)
        args->algorithm = ALGO_BASE64;
    else if (strncmp(input, "md5", 3) == 0)
        args->algorithm = ALGO_MD5;
    else if (strncmp(input, "sha256", 6) == 0)
        args->algorithm = ALGO_SHA256;
    else
        args_error("Wrong algorithm provided", input);
}

void        parse_args(char **list_args, int32_t nb_args)
{
    int32_t index_args;

    if (nb_args == 0)
        args_error("No arguments provided", NULL);

    index_args = 0;
    get_algorithm(list_args[index_args]);
    for (index_args = 1; index_args < nb_args ; index_args++)
    {
        if (is_option(list_args[index_args]))
            index_args += parse_options(list_args[index_args], list_args[index_args + 1], (nb_args - index_args));
        else if (is_hash_algorithm())
            break;
        else
            args_error("Wrong option", list_args[index_args]);
    }
    if (is_hash_algorithm())
    {
        for (; index_args < nb_args; index_args++)
                process_io(list_args[index_args], INPUT);
    }
    if (is_stdin_process())
        process_stdin();
}

void format_args(void)
{
    if (!(args->process_type))
        args->process_type = EN;

}

void        process_args(char **list_args, int32_t nb_args)
{
    allocate_args();
    parse_args(list_args, nb_args);
    format_args();
}