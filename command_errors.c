/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:18:00 by dberes            #+#    #+#             */
/*   Updated: 2024/01/03 00:04:12 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_commands(char **args, t_data *data, int ind)
{
	char	*directory;

	directory = NULL;
	if (access(args[0], F_OK) == 0)
	{
		data->dirs[ind - 2] = ft_strdup(args[0]);
	}
	else
	{
		directory = get_dir(data->path, args, data);
		if (directory == NULL)
			free_exit_single(args, data, 3);
		data->dirs[ind -2] = ft_strdup(directory);
		free(directory);
	}
}

void	set_data(t_data *data, int pipes, char **argv, char **env)
{
	data->path = get_path(env);
	data->env = env;
	data->pipes = pipes;
	data->argv = argv;
	data->argc = 5;
}

char	*get_dir(char *str, char **args, t_data *data)
{
	char	**dirs;
	char	*dir;
	char	*cmd;
	int		i;

	dirs = ft_split(str, 58);
	if (!dirs)
		free_exit_malloc(args, data);
	i = 0;
	cmd = ft_strjoin("/", args[0]);
	if (!cmd)
	{
		free(cmd);
		free_array(dirs);
		free_exit_malloc(args, data);
	}
	while (dirs[i] != NULL)
	{
		dir = ft_strjoin(dirs[i], cmd);
		if (access(dir, F_OK) == 0)
		{
			free(cmd);
			free_array(dirs);
			return (dir);
		}
		free (dir);
		i++;
	}
	return (free(cmd), free_array(dirs), NULL);
}

void	free_exit_single(char **args, t_data *data, int ex_code)
{
	if (ex_code == 1)
	{
		free_array(data->dirs);
		free_array(args);
		perror("Could not execve");
		exit(EXIT_FAILURE);
	}
	else if (ex_code == 2)
	{
		if (args)
			free_array(args);
		if (data->dirs)
			free_array(data->dirs);
		exit(EXIT_FAILURE);
	}
	else if (ex_code == 3)
	{
		if (args[0] == NULL)
			ft_printf("pipex: : command not found\n");
		else
			ft_printf("pipex: %s:command not found\n", args[0]);
		if (args)
			free_array(args);
		exit(EXIT_FAILURE);
	}
}

void	free_exit_malloc(char **args, t_data *data)
{
	if (data && data->dirs)
		free_array(data->dirs);
	if (args)
		free_array(args);
	ft_printf("malloc failed\n");
	exit(EXIT_FAILURE);
}
