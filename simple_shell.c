#include "main.h"

/**
 * simple_shell - starts a simple shell
 */
int main(int __attribute__((unused)) argc, char **argv, char **env)
{
	int program, status;
	char *buf, *av[] = {NULL, NULL};
	ssize_t nread = 0;
	size_t n = 0;
	pid_t child;

	while (nread != EOF)
	{
		printf("#cisfun$ ");
		nread = getline(&buf, &n, stdin);
		buf = strtok(buf, "\n");
		av[0] = buf;
		child = fork();
		if (child == 0)
		{
			program = execve(av[0], av, env);
			if (program == -1)
			{
				perror(argv[0]);
			}
			exit(EXIT_SUCCESS);
		}
		else
			wait(&status);
	}

	free(buf);

	return(0);
}
