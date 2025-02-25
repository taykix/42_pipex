/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:55:08 by tayki             #+#    #+#             */
/*   Updated: 2025/02/25 19:53:53 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char	**get_all_paths(char **envp)
{
	char	**all_paths;
	char	*temp;
	char	*path;
	int		i;

	path = find_path(envp);
	if (!path)
		handle_error(127, "pipex: command not found\n");
	all_paths = ft_split(path, ':');
	i = 0;
	while (all_paths[i])
	{
		temp = ft_strjoin(all_paths[i], "/");
		free(all_paths[i]);
		all_paths[i] = temp;
		i++;
	}
	return (all_paths);
}

char	*get_accesible_path(char *cmd, char **paths)
{
	char	**all_paths;
	char	*path_with_cmd;
	int		i;

	all_paths = paths;
	i = 0;
	while (all_paths[i])
	{
		path_with_cmd = ft_strjoin(all_paths[i], cmd);
		if (access(path_with_cmd, F_OK) == 0)
		{
			return (path_with_cmd);
		}
		else
			free(path_with_cmd);
		i++;
	}
	return (0);
}
