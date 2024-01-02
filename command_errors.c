/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:18:00 by dberes            #+#    #+#             */
/*   Updated: 2024/01/02 21:56:48 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void	path_error(t_data *data)
{
	int		i;
	char	**args;

	i = 2;
	args = ft_split(data->argv[2], 32);
	ft_printf("pipex: %s: command not found\n", args[0]);
	free_array(args);
	args = ft_split(data->argv[2], 32);
	ft_printf("pipex: %s: command not found\n", args[0]);
	free_array(args);
	exit(EXIT_FAILURE);
}

void	check_args(t_data *data, int *ex)
{
	int		i;
	char	**args;

	i = 2;
	while (i < 4)
	{
		args = ft_split(data->argv[i], 32);
		if (!args)
			free_exit_single(args, data, 4);
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
	int		abs;
	char	**args;
	char	*directory;

	i = 2;
	while (i < 4)
	{
		abs = 0;
		directory = NULL;
		args = ft_split(data->argv[i], 32);
		if (!args)
			free_exit_single(args, data, 4);
		if (args[0] != NULL)
		{
			if (access(args[0], F_OK) == 0)
			{
				data->dirs[i - 2] = ft_strdup(args[0]);
			}
			else
			{
				directory = get_dir(data->path, args, data);
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

void	file_create(t_data *data)
{
	int	fd_outf;
	
	fd_outf = open(data->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_outf == -1)
	{
		perror("pipex: failed to open outfile");
		close(fd_outf);
		exit(EXIT_FAILURE);
	}
	close(fd_outf);
}

char	*get_dir(char *str, char **args, t_data *data)
{
	char	**dirs;
	char	*dir;
	char	*cmd;
	int		i;

	dirs = ft_split(str, 58);
	if (!dirs)
		free_exit_single(args, data, 4);
	i = 0;
	cmd = ft_strjoin("/", args[0]);
	if (!cmd)
	{
		free(cmd);
		free_array(dirs);
		free_exit_single(args, data, 4);
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
		ft_printf("pipex: : command not found\n");
		if (args)
			free_array(args);
		exit(EXIT_FAILURE);
	}
	else if (ex_code == 3)
	{
		ft_printf("pipex: %s: command not found\n", args[0]);
		if (args)
			free_array(args);
		exit(EXIT_FAILURE);
	}
	else if (ex_code == 4)
	{
		if (data && data->dirs)
			free_array(data->dirs);
		if (args)
			free_array(args);
		ft_printf("malloc failed");
		exit(EXIT_FAILURE);
	}
}
