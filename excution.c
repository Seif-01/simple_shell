#include "shell.h"
/**
 * execute - execute a command with its entire path variables.
 * @data: a pointer to the program's data
 * Return: If success returns zero, otherwise, return -1.
 */
int execute(data_of_program *data)
{
	int ret_value = 0, status;
	pid_t pid;

	/* check for program in built-ins */
	ret_value = builtins_list(data);
	if (ret_value != -1) /* if program was found in built-ins */
		return (ret_value);

	/* check for program in file system */
	ret_value = find_program(data);
	if (ret_value)
	{ /* if program not found */
		return (ret_value);
	}
	else
	{ /* if program was found */
		pid = fork(); /* create a child process */
		if (pid == -1)
		{ /* if the fork call failed */
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{/* I am the child process, I execute the program*/
			ret_value = execve(data->tokens[0], data->tokens, data->env);
			if (ret_value == -1) /* if error when execve*/
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{/* I am the father, I wait and check the exit status of the child */
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
