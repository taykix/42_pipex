
#include "ft_pipex.h"

char	**get_next_script(int num, char **argv)
{
	char	**script;

	script = ft_split(argv[num], ' ');
	if (script == NULL || script[0] == NULL)
		handle_error(3, "Error: get_next_script returned NULL or empty");
	return (script);
}

t_pipex	*init_pipex(t_pipex *pipe, char **argv, int argc)
{
	int	i;
	pipe->in_fd = open_file(argv[1], 0);
    pipe->out_fd = open_file(argv[argc - 1], 1);
	pipe->is_invalid_infile = 0;
	pipe->script = (char ***)malloc((argc - 3) * sizeof(char **));
	pipe->path = (char **)malloc((argc - 3) * sizeof(char *));
	if (!pipe->script || !pipe->path)
		handle_error(1, "Memory allocation error\n");
	i = 0;
	while (i < argc - 3)
	{
		pipe->script[i] = get_next_script(i + 2, argv);
		if (pipe->script[i] == NULL || pipe->script[i][0] == NULL)
		{
			pipe->path[i] = NULL;
			handle_error(3, "Error: Invalid command in script");
		}
		pipe->path[i] = ft_strjoin("/bin/", pipe->script[i][0]);
		if (!pipe->path[i])
		{
			handle_error(1, "Memory allocation failed for path");
		}
		i++;
	}
	return (pipe);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex pipe;

	init_pipex(&pipe, argv, argc);
	create_pipe(pipe.fd);
	int pid = fork();
	if (pid < 0)
        handle_error(3, "Fork error\n");
    if (pid == 0)
        child_process(&pipe, 0);
	wait(NULL);
	int pid2 = fork();
    if (pid2 < 0)
        handle_error(3, "Fork error\n");
    if (pid2 == 0)
        parent_process(&pipe, 1);
	
	close(pipe.fd[0]);
    close(pipe.fd[1]);
    close(pipe.in_fd);
    close(pipe.out_fd);

    for (int i = 2; i < argc - 1; i++)
    {
        wait(NULL);
    }
	
    free_pipex(&pipe, argc);
	return (0);
}