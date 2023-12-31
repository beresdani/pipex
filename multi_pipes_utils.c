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

char	*get_dir_multi(char *str, char **args)
{
	char	**dirs;
	char	*dir;
	char	*cmd;
	int		i;

	dirs = ft_split(str, 58);
	i = 0;
	cmd = ft_strjoin("/", args[0]);
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
	free(cmd);
	free_array(dirs);
	return (NULL);
}

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
		if (args[0] == NULL)
		{
			ft_printf("bash: %s: command not found\n");
			free_array(args);
			args_freed = 1;
			ex = 1;
		}
		else if (data->path == NULL)
		{
			ft_printf("bash: %s: command not found\n", args[0]);
			free_array(args);
			args_freed = 1;
			ex = 2;
		}
		if (ex != 2)
		{
			directory = get_dir_multi(data->path, args);
			if (directory == NULL)
			{
				ft_printf("%s: command not found\n", args[0]);
				free_array(args);
				args_freed = 1;
				ex = 1;
			}
			if (ex != 1)
				data->dirs[i - 2] = directory;
		}
		if (args_freed == 0)
		{
			free_array(args);
		}
		i++;
	}
	if (ex != 0)
	{
		free(directory);
		free_array(data->dirs);
		exit(EXIT_FAILURE);
	}
}
