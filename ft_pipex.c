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


int	ft_countstring(char ** script_array)
{
	int	count;

	count = 0;
	while (script_array[count])
	{
		count++;
	}
	return (count);
}

int is_two_quotes(char* str)
{
	int count;
	int i;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			count++;
		i++;
	}
	return (count % 2) == 0;
}

char* str_join_with_free(char* new_script, char* script)
{
	char* temp;
	char* joined;
	
	temp = ft_strjoin(" ", script);
	joined = ft_strjoin(new_script, temp);
	free(temp);
	free(new_script);

	return joined;
}

// "awk '{print avs $2}'"
char	**handle_quotes_in_script(char **script)
{
	int		i;
	int		j;
	char	**new_script;

	i = 0;
	j = 0;
	new_script = (char **)malloc(sizeof(char *) * (ft_countstring(script) + 1));
	while (script[i])
	{
		if (ft_strchr(script[i], '\'') && !is_two_quotes(script[i]))
		{
			new_script[j] = ft_strdup(script[i++]);
			while (script[i])
			{
				new_script[j] = str_join_with_free(new_script[j], script[i]);
				//new_script[j] = ft_strjoin(new_script[j], ft_strjoin(" ", script[i]));
				if (ft_strchr(script[i++], '\''))
					break ;
			}
		}
		else
			new_script[j] = ft_strdup(script[i++]);
		j++;
	}
	new_script[j] = NULL;
	return (new_script);
}

char* erase_first_and_last_quote(char* str)
{
	char* str_without_quotes;
	int i;
	int len = ft_strlen(str);

	if (str[0] == '\'' && str[len - 1] == '\'')
	{
		str_without_quotes = (char*)malloc(sizeof(char) * (len - 1));
		if (!str_without_quotes)
			return NULL;
		i = 1;
		while (i < len - 1)
		{
			str_without_quotes[i - 1] = str[i];
			i++;
		}
		str_without_quotes[i - 1] = '\0';
		free(str);
		return str_without_quotes;
	}
	return str;
}


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
		printf("i is : %d, pipe->script[i][0] is %s, pipe->path[i] is %s \n", i, pipe->script[i][0], pipe->path[i]);
		i++;
	}
	free_script(all_paths);
	return (pipe);
}

char* find_path(char** envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char** get_all_paths(char** envp)
{
	char** all_paths;
	char* temp;
	char* path;
	int i;
	path = find_path(envp);
	if (!path)
		handle_error(5, "There is no path!\n");
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

char* get_accesible_path(char * cmd, char ** paths)
{
	char** all_paths;
	char* path_with_cmd;
	int i;

	all_paths = paths;
	i = 0;

	while (all_paths[i])
	{
		path_with_cmd = ft_strjoin(all_paths[i], cmd);
		if (access(path_with_cmd, F_OK) == 0)
		{
			printf("Newer here ? \n");
			return (path_with_cmd);
		}
		else
			free(path_with_cmd);
		i++;
	}
	return 0;
}


int	main(int argc, char *argv[], char *envp[])
{
	/*
	char* path = find_path(envp);
	char** all_paths = get_all_paths(path);
	int i = argc;
	
	
	while (all_paths[i])
	{
		printf("%s\n", all_paths[i]);
		i++;
	}
	free_script(all_paths);
	*/
	
	t_pipex	pipe;
	int		pid;
	int		pid2;

	init_pipex(&pipe, argv, envp, argc);
	printf("ARE WE HERE MAN?\n");
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
