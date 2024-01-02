/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 11:21:06 by dberes            #+#    #+#             */
/*   Updated: 2024/01/01 12:45:53 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	path_error(t_data *data)
{
	int		i;
	char	**args;

	i = 2;
	while (i < data->argc - 1)
	{
		args = ft_split(data->argv[i], 32);
		ft_printf("pipex: %s: command not found\n", args[0]);
		free_array(args);
		i++;
	}
	exit(EXIT_FAILURE);
}

void	check_args(t_data *data, int *ex)
{
	int		i;
	char	**args;

	i = 2;
	while (i < data->argc - 1)
	{
		args = ft_split(data->argv[i], 32);
		if (args[0] == NULL)
		{
			ft_printf("pipex: : command not found\n");
			*ex = 1;
		}
		free_array(args);
		i++;
	}
}

void	check_commands(t_data *data, int *ex)
{
	int		i;
	char	**args;
	char	*directory;

	i = 2;
	while (i < data->argc - 1)
	{
		directory = NULL;
		args = ft_split(data->argv[i], 32);
		if (args[0] != NULL)
		{
			directory = get_dir_multi(data->path, args);
			if (directory == NULL)
			{
				ft_printf("pipex: %s: command not found\n", args[0]);
				*ex = 1;
			}
			else if (*ex == 0)
				data->dirs[i - 2] = ft_strdup(directory);
			free(directory);
		}
		free_array(args);
		i++;
	}
	if (*ex == 1)
	{
		free_array(data->dirs);
		exit(EXIT_FAILURE);
	}
}

void	set_data(t_data *data, int pipes, char **argv, char **env)
{
	data->path = get_path(env);
	data->env = env;
	data->pipes = pipes;
	data->argv = argv;
}
