/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:51:56 by dberes            #+#    #+#             */
/*   Updated: 2024/01/03 00:00:33 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_exit(char **args, t_data *data, int ex_code)
{
	if (ex_code == 1)
	{
		free_array(data->dirs);
		free_array(args);
		perror("Could not execve");
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

void	free_list(t_plist *lst)
{
	t_plist	*current;
	t_plist	*next;

	current = lst;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	wait_for_child(t_plist *lst)
{
	t_plist	*node;

	node = lst;
	while (node->next != NULL)
	{
		waitpid(node->pid, NULL, 0);
		node = node->next;
	}
}

char	*get_dir_multi(char *str, char **args, t_data *data)
{
	char	**dirs;
	char	*dir;
	char	*cmd;
	int		i;

	dirs = ft_split(str, 58);
	if (!dirs)
		free_exit(args, data, 4);
	i = 0;
	cmd = ft_strjoin("/", args[0]);
	if (!cmd)
	{
		free(cmd);
		free_array(dirs);
		free_exit(args, data, 4);
	}
	while (dirs[i] != NULL)
	{
		dir = ft_strjoin(dirs[i], cmd);
		if (!dirs)
			free_exit(dirs, NULL, 4);
		if (access(dir, F_OK) == 0)
		{
			free(cmd);
			free_array(dirs);
			return (dir);
		}
		free (dir);
		i++;
	}
	free(cmd);
	free_array(dirs);
	return (NULL);
}
