#include "shell.h"

/**
 * builtins_list - search for match and execute the associate builtin
 * @data: struct for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int builtins_list(data_of_program *data)
{
	int index;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

	/* Walk through the structure */
	for (index = 0; options[index].builtin != NULL; index++)
	{
		/* If there is a match between the given command and a builtin, */
		if (str_compare(options[index].builtin, data->command_name, 0))
		{
			/* Execute the function, and return the return value of the function */
			return (options[index].function(data));
		}
		/* If there is no match return -1 */
	}
	return (-1);
}
