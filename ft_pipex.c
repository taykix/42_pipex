/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:10:31 by tayki             #+#    #+#             */
/*   Updated: 2025/02/07 20:59:14 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"


char	**get_next_script(int num, char **argv)
{
	char** temp_script;
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
		handle_error(3, "Error: get_next_script returned NULL or empty");
	return (script);
}

t_pipex	*init_pipex(t_pipex *pipe, char **argv, char **envp, int argc)
{
	int	i;
	char** all_paths;

	pipe->in_fd = open_file(argv[1], 0);
	pipe->out_fd = open_file(argv[argc - 1], 1);
	pipe->is_invalid_infile = 0;
	pipe->script = (char ***)malloc((argc - 3) * sizeof(char **));
	pipe->path = (char**)malloc((argc - 3) * sizeof(char*));
	all_paths = get_all_paths(envp);
	if (!pipe->script || !pipe->path)
		handle_error(1, "Memory allocation error\n");
	i = 0;
	while (i < argc - 3)
	{
		pipe->script[i] = get_next_script(i + 2, argv);
		if (pipe->script[i] == NULL || pipe->script[i][0] == NULL)
			handle_error(3, "Error: Invalid command in script");
		pipe->path[i] = get_accesible_path(pipe->script[i][0], all_paths);
		i++;
	}
	free_script(all_paths);
	return (pipe);
}


int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipe;
	int		pid;
	int		pid2;

	init_pipex(&pipe, argv, envp, argc);
	create_pipe(pipe.fd);
	pid = fork();
	if (pid < 0)
		handle_error(3, "Fork error\n");
	if (pid == 0)
		child_process(&pipe, 0);
	wait(NULL);
	pid2 = fork();
	if (pid2 < 0)
		handle_error(3, "Fork error\n");
	if (pid2 == 0)
		parent_process(&pipe, 1);
	close(pipe.fd[0]);
	close(pipe.fd[1]);
	close(pipe.in_fd);
	close(pipe.out_fd);
	wait(NULL);
	free_pipex(&pipe, argc);
	return (0);
}
