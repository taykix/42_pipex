
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

void		handle_error(int errno, const char *errmsg);
int			open_file(const char *filename, int in_out);
void		execute_command(const char *path, char **args);
char		**get_next_script(int num, char **argv);
int			parent_process(t_pipex *pipe, int i);
int			child_process(t_pipex *pipe, int i);
void		free_pipex(t_pipex *pipe, int argc);
void		create_pipe(int fd[2]);
void		free_path_and_script(char *path, char **script);
void		free_script(char** script);
char**		get_all_paths(char** envp);
char*		get_accesible_path(char* cmd, char** paths);

#endif