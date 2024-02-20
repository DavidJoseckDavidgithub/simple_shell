_SIMPLE SHELL PROJECT_
___________________________________________________________________

__AUTHOR: JOSECK DAVID__

tseps involved in creating a simple shell:
* Write a script file with a .sh extension and use the stdio.h library for input and output functions.
* Give executable permission to the file using chmod +x command in the terminal.
* Parse the user input by using `strsep` function to nbrake into words and strings, and check for special characters like pipes, redirections....
* User if the user input is a built-in command, such as `cd`, `exit` `help`... if so, execute it using the appropriate functions, such as`chdir` `exit`, `printf`, ...
* If the user input is not a built-in command, execute it as a system command by forking a child process and calling `execvp` function, which searches for the command in the system path and executes it with the given arguments.