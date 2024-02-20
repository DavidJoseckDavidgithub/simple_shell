#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFSIZE 1024
#define DELIM " \t\n"
#define PROMPT "$ "

/**
 * main - a simple UNIX command line interpreter
 *
 * Return: 0 on success, 1 on error
 */

int main(void)
{
  char *line, *cmd, **args;
  int status, r;

  line = NULL;
  args = malloc(sizeof(char *) * BUFSIZE);
  if (args == NULL)
    {
      perror("malloc");
      return (1);
    }
  while (1)
    {
      printf(PROMPT);
      if (getline(&line, &BUFSIZE, stdin) == -1)
	{
	  if (feof(stdin))
	    {
	      printf("\n");
	      break;
	    }
	  else
	    {
	      perror("getline");
	      return (1);
	    }
	}
      cmd = strtok(line, DELIM);
      if (cmd == NULL || cmd[0] == '#')
	continue;
      r = 0;
      while (cmd != NULL)
	{
	  args[r] = cmd;
	  r++;
	  cmd = strtok(NULL, DELIM);
	}
      args[r] = NULL;
      status = execute(args);
      if (status == 0)
	break;
      if (status == -1)
	return (1);
    }
  free(line);
  free(args);
  return (0);
}

  /**
   * execute - executes a command with execve
   * args: a null-0terminated array of arguments
   *
   * Return: 1 on success, 0 on exit, -1 on error
   */

  int execute(char **args)
  {
    pid_t pid;
    int status;

    if (strcmp(args[0], "exit") == 0)
      return (0);

    pid = fork();
    if (pid == -1)
      {
	perror("fork");
	return (-1);
      }
    if (pid == 0)
      {
	if (execve(args[0], args, NULL) == -1)
	  {
	    perroe(args[0]);
	    exit(1);
	  }
      }
    else
      {
	wait(&status);
      }
    return (1);
  }
