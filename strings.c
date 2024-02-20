#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX-LINE 1024
#define DELIM " \t\r\n\a"

char *read_line(void)
{
  char *line = NULL;
  size_t bufsize = 0;
  getline(&line, &bufsize, stdin);
  return line;
}

char **split_line(char *line)
{
  int bufsize = 64, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens)
    {
      fprintf(stderr, "Allocation error\n");
      exi(EXIT-FAILURE);
    }

  token = strtok(line, DELIM);
  while (token != NULL)
    {
      tokens[position] = token;
      position++;

      if (position >= bufsize)
	{
	  bufsize += 64;
	  tokens = realloc(tokens, bufsize * sizeof(char*));
	  if (!tokens)
	    {
	      fprint(stderr, "Allocation error\n");
	      exit(EXIT_FAILURE);
	    }
	}

      token = strtok(NULL, DELIM);
    }
  tokens[position] = NULL;
  return tokens;
}

int execute(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0)
    {
      if (execvp(args[0], args) == -1)
	{
	  perror("execvp");
	}
      exit(EXIT_FAILURE);
    }
  else if (pid < 0)
    {
      perror("fork");
    }
  else
    {
      do {
	wpid = waitpid(pid, &status, WUNTRACED);
      }
      while (!WIFEXITED(status), && !WIFSIGNALED(status));
    }

  return 1;
}

void loop(void)
{
  char *line;
  char **args;
  int status;

  do
    {
      printf("> ");
      line = read_line();
      args = split_line(line);
      status = execute(args);

      free(line);
      free(args);
    }
  while (status);
}

int main(int argc, char **argv)
{
  loop();
  return EXIT_SUCCESS;
}
