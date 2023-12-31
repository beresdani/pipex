#include "pipex.h"

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
		/*printf("%d\n", waitpid(node->pid, NULL, 0));*/
		/*if (waitpid(node->pid, NULL, 0) == -1)
    	{
        	perror("waitpid");
        	exit(EXIT_FAILURE);
    	}*/
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

	i = 2;
	ex = 0;
	while (i < data->argc - 1)
	{
		args = ft_split(data->argv[i], 32);
		if (args[0] == NULL)
		{
			ft_printf("bash: %s: command not found\n");
			free_array(args);
			ex = 1;
		}
		else if (data->path == NULL)
		{
			ft_printf("bash: %s: command not found\n", args[0]);
			free_array(args);
			ex = 2;
		}
		if (ex != 2)
		{
			directory = get_dir_multi(data->path, args);
			if (directory == NULL)
			{
				ft_printf("%s: command not found\n", args[0]);
				free_array(args);
				ex = 1;
			}
			data->dirs[i - 2] = directory;
		}
		if (ex == 0)
			free_array(args);
		i++;
	}
	if (ex != 0)
	{
			free_array(data->dirs);
			exit(EXIT_FAILURE);
	}
}

void	first_child_process(t_plist **lst, t_data *data, int ind)
{
	int		fd_inf;
	t_plist	*node;
	char	**args;

	node = *lst;
	args = ft_split(data->argv[ind + 2], 32);
	fd_inf = open("infile", O_RDONLY);
	if (fd_inf == -1)
	{
		perror("bash: infile");
		fd_closer(0, lst);
		exit(EXIT_FAILURE);
	}
	dup2(fd_inf, STDIN_FILENO);
	dup2(node->fd[1], STDOUT_FILENO);
	close(fd_inf);
	fd_closer(0, lst);
	if (execve(data->dirs[ind], args, data->env) == -1)
	{
		free_array(args);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	multi_child_process(t_plist **lst, t_data *data, int ind)
{
	t_plist	*node;
	int		i;
	char	**args;

	i = 0;
	node = *lst;
	while (i < ind)
	{
		node = node->next;
		i++;
	}
	dup2(node->fd[0], STDIN_FILENO);
	dup2(node->next->fd[1], STDOUT_FILENO);
	fd_closer(0, lst);
	args = ft_split(data->argv[ind + 3], 32);
	if (execve(data->dirs[ind + 1], args, data->env) == -1)
	{
		free_array(args);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	last_child_process(t_plist **lst, t_data *data, int ind)
{
	int		fd_outf;
	t_plist	*node;
	int		i;
	char	**args;

	i = 0;
	args = ft_split(data->argv[ind + 2], 32);
	node = *lst;
	while (i < ind -1)
	{
		node = node->next;
		i++;
	}
	fd_closer(1, lst);
	fd_outf = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_outf == -1)
	{
		perror("bash: outfile");
		close (node->fd[0]);
		exit(EXIT_FAILURE);
	}
	dup2(fd_outf, STDOUT_FILENO);
	dup2(node->fd[0], STDIN_FILENO);
	close (node->fd[0]);
	close(fd_outf);
	
	if (execve(data->dirs[ind], args, data->env) == -1)
	{
		free_array(args);
		perror("Could not execve");
		exit(EXIT_FAILURE);
	}
}