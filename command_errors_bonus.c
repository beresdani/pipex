/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_errors_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 11:21:06 by dberes            #+#    #+#             */
/*   Updated: 2024/01/03 00:05:43 by dberes           ###   ########.fr       */
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
		if (!args)
			free_exit(args, data, 4);
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
		if (!args)
			free_exit(args, data, 4);
		if (args[0] != NULL)
		{
			if (access(args[0], F_OK) == 0)
			{
				data->dirs[i - 2] = ft_strdup(args[0]);
			}
			else
			{
				directory = get_dir_multi(data->path, args, data);
				if (directory == NULL)
				{
					ft_printf("pipex: %s: command not found\n", args[0]);
					*ex = 1;
				}
				else if (*ex == 0)
					data->dirs[i - 2] = ft_strdup(directory);
				free(directory);
			}
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

void	file_create(t_data *data)
{
	int	fd_outf;

	fd_outf = open(data->argv[data->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_outf == -1)
	{
		perror("pipex: failed to open outfile");
		close(fd_outf);
		exit(EXIT_FAILURE);
	}
	close(fd_outf);
}
