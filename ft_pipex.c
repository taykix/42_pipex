/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:10:31 by tayki             #+#    #+#             */
/*   Updated: 2025/02/26 20:08:27 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	wait_for_child(pid_t pid, t_pipex *pipe, int argc)
{
	int	status;
	int	exit_code;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code != 0)
		{
			free_pipex(pipe, argc);
			exit(exit_code);
		}
	}
}

char	**get_next_script(int num, char **argv)
{
	char	**temp_script;
	char	**script;
	int		i;

	temp_script = ft_split(argv[num], ' ');
	script = handle_quotes_in_script(temp_script);
	free_script(temp_script);
	i = 0;
	while (script[i])
	{
		script[i] = erase_first_and_last_quote(script[i]);
		i++;
	}
	if (script == NULL || script[0] == NULL)
		handle_error(1, "Error: Invalid command in script");
	return (script);
}

t_pipex	*init_pipex(t_pipex *pipe, char **argv, char **envp, int argc)
{
	int		i;
	char	**all_paths;

	pipe->in_fd = -1;
	pipe->out_fd = -1;
	pipe->envp = envp;
	pipe->script = (char ***)malloc((argc - 3) * sizeof(char **));
	pipe->path = (char **)malloc((argc - 3) * sizeof(char *));
	all_paths = get_all_paths(envp);
	if (!pipe->script || !pipe->path)
		handle_error(1, "Memory allocation error\n");
	i = 0;
	while (i < argc - 3)
	{
		pipe->script[i] = get_next_script(i + 2, argv);
		if (pipe->script[i] == NULL || pipe->script[i][0] == NULL)
		{
			handle_error(1, "Error: Invalid command in script");
		}
		pipe->path[i] = get_accesible_path(pipe->script[i][0], all_paths);
		i++;
	}
	free_script(all_paths);
	return (pipe);
}

void	close_pipe_fds(t_pipex *pipe)
{
	if (pipe->fd[0] > 0)
		close(pipe->fd[0]);
	if (pipe->fd[1] > 0)
		close(pipe->fd[1]);
	if (pipe->in_fd > 0)
		close(pipe->in_fd);
	if (pipe->out_fd > 0)
		close(pipe->out_fd);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipe;
	int		pid;
	int		pid2;

	if (argc != 5)
		return (1);
	if (ft_strlen(argv[1]) == 0)
		handle_error(1, "Error: Invalid arguments\n");
	init_pipex(&pipe, argv, envp, argc);
	create_pipe(pipe.fd);
	pid = fork();
	if (pid < 0)
		handle_error(1, "Fork error\n");
	if (pid == 0)
		child_process(&pipe, 0, argv[1]);
	wait(NULL);
	pid2 = fork();
	if (pid2 < 0)
		handle_error(1, "Fork error\n");
	if (pid2 == 0)
		parent_process(&pipe, 1, argv[argc - 1]);
	close_pipe_fds(&pipe);
	wait_for_child(pid2, &pipe, argc);
	free_pipex(&pipe, argc);
	return (0);
}
