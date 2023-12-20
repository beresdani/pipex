/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:03:36 by dberes            #+#    #+#             */
/*   Updated: 2023/12/18 16:13:10 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	list_size(t_data **lst)
{
	int		count;
	t_data	*ptr;

	count = 0;
	ptr = *lst;
	if (lst == NULL)
		return (0);
	while (ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

t_data	*list_last(t_data **lst)
{
	t_data	*ptr;

	if (lst == NULL)
		return (*lst);
	ptr = *lst;
	while (ptr != NULL)
	{
		if (ptr->next != NULL)
			ptr = ptr->next;
		else
			break ;
	}
	return (ptr);
}

void	add_pipe_node(t_data **lst, t_data *new)
{
	t_data	*ptr;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = list_last(lst);
	ptr->next = new;
}

char	*get_path(char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*get_dir(char *str, char *cmd)
{
	char	**dirs;
	char	*dir;
	int		i;

	dirs = ft_split(str, 58);
	i = 0;
	cmd = ft_strjoin("/", cmd);
	while (dirs[i] != NULL)
	{
		dir = ft_strjoin(dirs[i], cmd);
		if (access(dir, F_OK) == 0)
		{
			free_array(dirs);
			return (dir);
		}
		i++;
	}
	free_array(dirs);
	return (NULL);
}
