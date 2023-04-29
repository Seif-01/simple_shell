
README.md
This is a simple shell project that is an UNIX command line interpreter. It can run both in interactive and non-interactive mode.

Requirements
All the code files are written in C.
The code must be compiled with gcc 4.8.4 using the flags -Wall -Werror -Wextra and -pedantic.
The prototype of the function is int main(void).
The function prompt and the function getline cannot exceed 32 lines.
The function description is preceded by /** in the header file.
The code should use the Betty style.
Features
The shell can be used to run simple UNIX commands. Some of the features of this simple shell are:

Display a prompt and wait for the user to type a command. A command line always ends with a new line.
The prompt is displayed again each time a command has been executed.
The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
The command lines are made only of one word. No arguments will be passed to programs.
If an executable cannot be found, an error message is printed and the prompt is displayed again.
Handles the "end of file" condition (Ctrl+D).
Handles command lines with arguments.
Handles the PATH environment variable.
Fork is not called if the command does not exist.
Usage
Compile the code files using the following command:

Copy code
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
The compiled program can be run in interactive mode by typing the following command:

bash
Copy code
./hsh
The shell will display a prompt where you can type commands. Type 'exit' to exit the shell.

The program can also be run in non-interactive mode by piping commands into the shell as follows:

bash
Copy code
echo "/bin/ls" | ./hsh
This will execute the command /bin/ls.

Files
AUTHORS - list of contributors to this repository
man_1_simple_shell - manual page for the simple shell
shell.h - header file containing the function prototypes and struct declarations
shell.c - main file that runs the simple shell
prompt.c - file that displays the prompt
getline.c - file that reads input from the user
split_line.c - file that splits the input into tokens
execute.c - file that executes the command
find_path.c - file that searches for the command in the PATH environment variable
helper_functions.c - file that contains helper functions for executing commands
Bugs
No known bugs at this time.
