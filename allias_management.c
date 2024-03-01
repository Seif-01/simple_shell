#include "shell.h"

/**
 * print_alias - add, remove, or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if success, or other number if it's declared in the arguments
 */
int print_alias(data_of_program *data, char *alias)
{
    int c, j, alias_length;
    char buffer[250] = {'\0'};

    if (data->alias_list)
    {
        alias_length = str_length(alias);
        for (c = 0; data->alias_list[c]; c++)
        {
            if (!alias || (str_compare(data->alias_list[c], alias, alias_length)
                            && data->alias_list[c][alias_length] == '='))
            {
                for (j = 0; data->alias_list[c][j]; j++)
                {
                    buffer[j] = data->alias_list[c][j];
                    if (data->alias_list[c][j] == '=')
                        break;
                }
                buffer[j + 1] = '\0';
                buffer_add(buffer, "'"); // Add single quote
                buffer_add(buffer, data->alias_list[c] + j + 1);
                buffer_add(buffer, "'\n");
                _print(buffer);
            }
        }
    }

    return (0);
}

/**
 * get_alias - add, remove, or show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if success, or other number if it's declared in the arguments
 */
char *get_alias(data_of_program *data, char *name)
{
    int c, alias_length;

    /* validate the arguments */
    if (name == NULL || data->alias_list == NULL)
        return (NULL);

    alias_length = str_length(name);

    for (c = 0; data->alias_list[c]; c++)
    { /* Iterates through the environ and check for coincidence of the varname */
        if (str_compare(name, data->alias_list[c], alias_length) &&
            data->alias_list[c][alias_length] == '=')
        { /* returns the value of the key NAME=  when find it */
            return (data->alias_list[c] + alias_length + 1);
        }
    }
    /* returns NULL if did not find it */
    return (NULL);
}

/**
 * set_alias - add, or override alias
 * @alias_string: alias to be set in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if success, or other number if it's declared in the arguments
 */
int set_alias(char *alias_string, data_of_program *data)
{
    int c, j;
    char buffer[250] = {'0'}, *temp = NULL;

    /* validate the arguments */
    if (alias_string == NULL || data->alias_list == NULL)
        return (1);
    /* Iterates alias to find = char */
    for (c = 0; alias_string[c]; c++)
        if (alias_string[c] != '=')
            buffer[c] = alias_string[c];
        else
        { /* search if the value of the alias is another alias */
            temp = get_alias(data, alias_string + c + 1);
            break;
        }

    /* Iterates through the alias list and check for coincidence of the varname */
    for (j = 0; data->alias_list[j]; j++)
        if (str_compare(buffer, data->alias_list[j], c) &&
            data->alias_list[j][c] == '=')
        { /* if the alias already exists */
            free(data->alias_list[j]);
            break;
        }

    /* add the alias */
    if (temp)
    { /* if the alias already exists */
        buffer_add(buffer, "=");
        buffer_add(buffer, temp);
        data->alias_list[j] = str_duplicate(buffer);
    }
    else /* if the alias does not exist */
        data->alias_list[j] = str_duplicate(alias_string);
    return (0);
}
