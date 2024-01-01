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

void	check_commands(t_data *data)
{
	int		i;
	char	**args;
	char	*directory;
	int		ex;
	int		args_freed;

	i = 2;
	ex = 0;
	while (i < data->argc - 1)
	{
		args_freed = 0;
		args = ft_split(data->argv[i], 32);
		free_handler(data, args, &ex, &args_freed);
		directory = get_dir_multi(data->path, args);
		if (directory == NULL)
			free_handler2(args, &ex, &args_freed);
		if (ex != 1)
			data->dirs[i - 2] = directory;
		if (args_freed == 0)
			free_array(args);
		i++;
	}
	if (ex != 0)
	{
		free(directory);
		free_array(data->dirs);
		exit(EXIT_FAILURE);
	}
}

void	free_handler(t_data *data, char **args, int *ex, int *args_freed)
{
	if (args[0] == NULL)
	{
		ft_printf("bash: %s: command not found\n");
		free_array(args);
		*args_freed = 1;
		*ex = 1;
	}
	else if (data->path == NULL)
	{
		ft_printf("bash: %s: command not found\n", args[0]);
		free_array(args);
		*args_freed = 1;
		*ex = 2;
	}
}

void	free_handler2(char **args, int *ex, int *args_freed)
{
	if (*ex != 2)
	{
		{
			ft_printf("%s: command not found\n", args[0]);
			free_array(args);
			*args_freed = 1;
			*ex = 1;
		}
	}
}
