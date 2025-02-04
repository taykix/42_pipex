
#include "ft_pipex.h"

char	**get_next_script(int num, char **argv)
{
	char	**script;
	if (!argv[num])  // argv[num] NULL mı kontrol edelim.
		handle_error(3, "Error: get_next_script received NULL argument");
	printf("HERE %s num : \n", argv[num]);
	script = ft_split(argv[num], ' ');
	if (script == NULL)
		handle_error(3, "Error: get_next_script returned NULL");
	return (script);
}

t_pipex	*init_pipex(t_pipex *pipe, char **argv, int argc)
{
	int	i;
	char ** temp_argv = argv;
	pipe->is_invalid_infile = 0;
	pipe->script = (char ***)malloc((argc - 3) * sizeof(char **));
	pipe->path = (char **)malloc((argc - 3) * sizeof(char *));
	pipe->in_fd = open_file(temp_argv[1], 0);
	pipe->out_fd = open_file(temp_argv[argc - 1], 1);
	return pipe;
}

int	main(int argc, char *argv[], char *env[])
{
	
}