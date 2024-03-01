#include "shell.h"

/**
* _getline - read one line from the prompt.
* @data: struct for the program's data
*
* Return: reading counting bytes.
*/
int _getline(data_of_program *data)
{
    char buff[BUFFER_SIZE] = {'\0'};
    static char *array_commands[10] = {NULL};
    static char array_operators[10] = {'\0'};
    ssize_t bytes_read, c = 0;

    /* check if does not exist more commands in the array. */
    /* and checks the logical operators. */
    if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
        (array_operators[0] == '|' && errno == 0))
    {
        /* release the memory allocated in the array if it exists. */
        for (c = 0; array_commands[c]; c++)
        {
            free(array_commands[c]);
            array_commands[c] = NULL;
        }

        /* read from the file descriptor int to buff. */
        bytes_read = read(data->file_descriptor, &buff, BUFFER_READ_SIZE);
        if (bytes_read == 0)
            return (-1);

        /* split the lines for \n or ; */
        c = 0;
        do {
            array_commands[c] = str_duplicate(_strtok(c ? NULL : buff, "\n;"));
            /* checks and split for && and || operators. */
            c = check_logic_ops(array_commands, c, array_operators);
        } while (array_commands[c++]);
    }

    /* obtains next command (command 0) and remove it from the array. */
    data->input_line = array_commands[0];
    for (c = 0; array_commands[c]; c++)
    {
        array_commands[c] = array_commands[c + 1];
        array_operators[c] = array_operators[c + 1];
    }

    return (str_length(data->input_line));
}

/**
* check_logic_ops - checks and split for && and || operators
* @array_commands: array of the commands.
* @c: index in the array_commands to be checked
* @array_operators: array of the logical operators for each previous command
*
* Return: index of the last command in the array_commands.
*/
int check_logic_ops(char *array_commands[], int c, char array_operators[])
{
    char *temp = NULL;

    /* checks for the & char in the command line */
    for (int j = 0; array_commands[c] != NULL  && array_commands[c][j]; j++)
    {
        if (array_commands[c][j] == '&' && array_commands[c][j + 1] == '&')
        {
            /* split the line when chars && were found */
            temp = array_commands[c];
            array_commands[c][j] = '\0';
            array_commands[c] = str_duplicate(array_commands[c]);
            array_commands[c + 1] = str_duplicate(temp + j + 2);
            c++;
            array_operators[c] = '&';
            free(temp);
            j = 0;
        }
        if (array_commands[c][j] == '|' && array_commands[c][j + 1] == '|')
        {
            /* split the line when chars || were found */
            temp = array_commands[c];
            array_commands[c][j] = '\0';
            array_commands[c] = str_duplicate(array_commands[c]);
            array_commands[c + 1] = str_duplicate(temp + j + 2);
            c++;
            array_operators[c] = '|';
            free(temp);
            j = 0;
        }
    }
    return c;
}
