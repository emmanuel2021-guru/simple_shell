#include "main.h"

/**
 * main - starts a simple shell
 * @argc: number of command line arguments
 * @argv: pointer to the array of arguments
 * @env: pointer to an array of environment variables
 *
 * Return: Always 0
 */
int main(int __attribute__((unused)) argc, char **argv, char **env)
{
	int program, status;
	char *buf, *av[] = {NULL};
	ssize_t nread = 0;
	size_t n = 0;
	pid_t child;

	while (nread != EOF)
	{
		int i = 1;
		printf("#cisfun$ ");
		nread = getline(&buf, &n, stdin);
		buf = strtok(buf, " \t\r\n\v\f");
		av[0] = buf;
		while (buf != NULL)
		{
			buf = strtok(NULL, " \t\r\n\v\f");
			av[i] = buf;
			i++;
		}
		av[i] = NULL;
		child = fork();
		if (child == 0)
		{
			program = execve(av[0], av, env);
			if (program == -1 && nread != EOF && av[0] != NULL)
			{
				perror(argv[0]);
			}
			exit(EXIT_SUCCESS);
		}
		else
			wait(&status);
		for (;i >= 0; i--)
			av[i] = NULL;
	}

	free(buf);

	return (0);
}
