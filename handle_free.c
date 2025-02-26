/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:55:12 by tayki             #+#    #+#             */
/*   Updated: 2025/02/26 19:48:18 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	free_path_and_script(char *path, char **script)
{
	int	i;

	free(path);
	i = 0;
	while (script[i] != NULL)
	{
		free(script[i]);
		i++;
	}
	free(script);
}

void	free_script(char **script)
{
	int	i;

	i = 0;
	while (script[i] != NULL)
	{
		free(script[i]);
		i++;
	}
	free(script);
}

void	free_pipex(t_pipex *pipe, int argc)
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

void	handle_error(int errno, const char *errmsg)
{
	perror(errmsg);
	exit(errno);
}
