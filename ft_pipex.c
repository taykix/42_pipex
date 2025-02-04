
#include "ft_pipex.h"

char	**get_next_script(int num, char **argv)
{
	char	**script;

	script = ft_split(argv[num], ' ');
	if (script == NULL)
		handle_error(3, "Error: get_next_script returned NULL");
	return (script);
}

void handle_error(int errno, const char *errmsg)
{
    perror(errmsg);
    exit(errno);
}

t_pipex	*init_pipex(t_pipex *pipe, char **argv, int argc)
{
	int	i;

	pipe->in_fd = open_file(argv[1], 0);
	pipe->out_fd = open_file(argv[argc - 1], 1);
	pipe->is_invalid_infile = 0;
	pipe->script = (char ***)malloc((argc - 2) * sizeof(char **));
	pipe->path = (char **)malloc((argc - 2) * sizeof(char *));
	if (!pipe->script || !pipe->path)
		handle_error(1, "Memory allocation error\n");
	i = 0;
	while (i < argc - 2)
	{
		pipe->script[i] = get_next_script(i, argv);
		pipe->path[i] = ft_strjoin("/bin/", pipe->script[i][0]);
	}
}

void free_path_and_script(char *path, char **script)
{
    free(path);
    for (int i = 0; script[i] != NULL; i++) {
        free(script[i]);
    }
    free(script);
}


int	open_file(const char *filename, int in_out)
{
	int	fd;

	if (in_out == 0)
		fd = open(filename, O_RDONLY);
	else if (in_out == 1)
		fd = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		handle_error(1, "File open error");
	return (fd);
}

void	free_pipex(t_pipex *pipe, int argc)
{
    int i = 0;
	for (int i = 0; i < argc - 2; i++)
	{
		free_path_and_script(pipe->path[i], pipe->script[i]);
	}
	free(pipe->path);
	free(pipe->script);
}

int	child_process(t_pipex *pipe, int i)
{
	dup2(pipe->in_fd, STDIN_FILENO);
	dup2(pipe->fd[1], STDOUT_FILENO);
	close(pipe->in_fd);
	close(pipe->fd[1]);
	execute_command(pipe->path[i], pipe->script[i]);
}

void create_pipe(int fd[2])
{
    if (pipe(fd) == -1)
        handle_error(2, "Pipe error");
}

int	parent_process(t_pipex *pipe, int i)
{
	dup2(pipe->fd[0], STDIN_FILENO);
	dup2(pipe->out_fd, STDOUT_FILENO);
	close(pipe->fd[0]);
	close(pipe->out_fd);
	execute_command(pipe->path[i], pipe->script[i]);
}

void execute_command(const char *path, char **args)
{
    execve(path, args, NULL);
    perror("Error executing command");
    exit(1);
}

int	main(int argc, char *argv[], char *env[])
{
	if (argc < 4)
		handle_error(1, "You need to give at least 4 args.\n");

	t_pipex *pipe;
	pipe = init_pipex(pipe, argv, argc);

	int i;

    create_pipe(pipe->fd);
    int pid = fork();
    if (pid < 0)
        handle_error(3, "Fork error\n");
    if (pid == 0)
        child_process(pipe, 0);
    wait(NULL);
    int pid2 = fork();
    if (pid2 < 0)
        handle_error(3, "Fork error\n");
    if (pid2 == 0)
        parent_process(pipe, 1);
    wait(NULL);
    close(pipe->fd[0]);
    close(pipe->fd[1]);
	close(pipe->in_fd);
    close(pipe->out_fd);

	for (int i = 2; i < argc - 1; i++)
	{
		wait(NULL);
	}
    free_pipex(pipe, argc);
	return (0);
}