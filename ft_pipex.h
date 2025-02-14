/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayki <tayki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:30:27 by tayki             #+#    #+#             */
/*   Updated: 2025/02/14 17:30:30 by tayki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include "ft_printf/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		fd[2];
	int		in_fd;
	int		out_fd;
	int		is_invalid_infile;
	char	***script;
	char	**path;
}			t_pipex;

int			open_file(const char *filename, int in_out);
void		execute_command(const char *path, char **args);
char		**get_next_script(int num, char **argv);
int			parent_process(t_pipex *pipe, int i);
int			child_process(t_pipex *pipe, int i);
void		create_pipe(int fd[2]);
void		free_pipex(t_pipex *pipe, int argc);
void		free_path_and_script(char *path, char **script);
void		free_script(char **script);
void		handle_error(int errno, const char *errmsg);

char		**get_all_paths(char **envp);
char		*get_accesible_path(char *cmd, char **paths);
char		*find_path(char **envp);

int			ft_countstring(char **script_array);
char		*str_join_with_free(char *new_script, char *script);
int			is_two_quotes(char *str);
char		**handle_quotes_in_script(char **script);
char		*erase_first_and_last_quote(char *str);

#endif