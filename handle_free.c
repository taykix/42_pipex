
#include "ft_pipex.h"

void	free_path_and_script(char* path, char** script)
{
	free(path);
	for (int i = 0; script[i] != NULL; i++)
	{
		free(script[i]);
	}
	free(script);
}

void	free_script(char** script)
{
	for (int i = 0; script[i] != NULL; i++)
	{
		free(script[i]);
	}
	free(script);
}

void	free_pipex(t_pipex* pipe, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 3)
	{
		free_path_and_script(pipe->path[i], pipe->script[i]);
		i++;
	}
	free(pipe->path);
	free(pipe->script);
}

void	handle_error(int errno, const char* errmsg)
{
	perror(errmsg);
	exit(errno);
}