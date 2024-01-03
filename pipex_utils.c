#include "pipex.h"

void	set_data(t_data *data, int pipes, char **argv, char **env)
{
	data->path = get_path(env);
	data->env = env;
	data->pipes = pipes;
	data->argv = argv;
	data->argc = 5;
}

void	dirs_calloc(t_data *data)
{
	data->dirs = (char **)ft_calloc(sizeof(char *), (data->argc - 2));
	if (data->dirs == NULL)
	{
		ft_printf("malloc failed");
		exit(EXIT_FAILURE);
	}
}
