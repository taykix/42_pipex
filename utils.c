/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:54:51 by tayki             #+#    #+#             */
/*   Updated: 2025/02/26 20:12:09 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
#include <errno.h>

void	execute_command(const char *path, char **args, char **envp)
{
	if (!path || access(path, F_OK) == -1)
	{
		handle_error(127, "pipex");
	}
	else if (access(path, X_OK) == -1)
	{
		handle_error(126, "Error: Command cannot be executed\n");
	}
	else
	{
		if (execve(path, args, envp) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
}

int	child_process(t_pipex *pipe, int i, char *argv)
{
	pipe->in_fd = open_file(argv, 0);
	close(pipe->fd[0]);
	dup2(pipe->in_fd, STDIN_FILENO);
	dup2(pipe->fd[1], STDOUT_FILENO);
	close(pipe->in_fd);
	close(pipe->fd[1]);
	execute_command(pipe->path[i], pipe->script[i], pipe->envp);
	return (-1);
}

void	create_pipe(int fd[2])
{
	if (pipe(fd) == -1)
		handle_error(1, "Pipe error");
}

int	parent_process(t_pipex *pipe, int i, char *argv)
{
	pipe->out_fd = open_file(argv, 1);
	close(pipe->fd[1]);
	dup2(pipe->fd[0], STDIN_FILENO);
	dup2(pipe->out_fd, STDOUT_FILENO);
	close(pipe->fd[0]);
	close(pipe->out_fd);
	execute_command(pipe->path[i], pipe->script[i], pipe->envp);
	return (-1);
}

int	open_file(const char *filename, int in_out)
{
	int	fd;

	if (in_out == 0)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			if (access(filename, F_OK) == -1)
				handle_error(1, "pipex");
			else if (access(filename, R_OK) == -1)
				handle_error(1, "pipex");
		}
	}
	else if (in_out == 1)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			if (access(filename, F_OK) != -1 && access(filename, W_OK) == -1)
				handle_error(1, "pipex");
		}
	}
	return (fd);
}
