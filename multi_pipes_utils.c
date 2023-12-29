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
	int		i;
	t_plist	*node;

	i = 0;
	node = lst;
	while (node != NULL)
	{	
		waitpid(node->pid, NULL, 0);
		node = node->next;
		i++;
	}
}


void	first_child_process(t_plist **lst, t_data *data, int ind)
{
	char	**args1;
	char	*directory;
	int		fd_inf;
	t_plist	*node;

	node = *lst;
	args1 = ft_split(data->argv[ind + 2], 32);
	directory = get_dir(data->path, args1, *lst);
	fd_inf = open("infile", O_RDONLY);
	if (fd_inf == -1)
	{
		fd_closer(0, lst);
		free_array(args1);
		free(args1);
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd_inf, STDIN_FILENO);
	dup2(node->fd[1], STDOUT_FILENO);
	close(fd_inf);
	fd_closer(0, lst);
	if (execve(directory, args1, data->env) == -1)
	{
		free_array(args1);
		free(args1);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	multi_child_process(t_plist **lst, t_data *data, int ind)
{
	char	**args1;
	char	*directory;
	t_plist	*node;
	int		i;

	i = 0;
	node = *lst;
	while (i < ind)
	{
		node = node->next;
		i++;
	}
	args1 = ft_split(data->argv[ind + 3], 32);
	directory = get_dir(data->path, args1, *lst);
	dup2(node->fd[0], STDIN_FILENO);
	dup2(node->next->fd[1], STDOUT_FILENO);
	fd_closer(0, lst);
	if (execve(directory, args1, data->env) == -1)
	{
		free_array(args1);
		free(args1);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	last_child_process(t_plist **lst, t_data *data, int ind)
{
	int		fd_outf;
	char	**args2;
	char	*directory2;
	t_plist	*node;
	int		i;

	i = 0;
	node = *lst;
	while (i < ind -1)
	{
		node = node->next;
		i++;
	}
	fd_closer(1, lst);
	args2 = ft_split(data->argv[ind + 2], 32);
	directory2 = get_dir(data->path, args2, *lst);
	fd_outf = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_outf == -1)
	{
		close (node->fd[0]);
		free_array(args2);
		free(args2);
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd_outf, STDOUT_FILENO);
	dup2(node->fd[0], STDIN_FILENO);
	close (node->fd[0]);
	close(fd_outf);
	
	if (execve(directory2, args2, data->env) == -1)
	{
		free_array(args2);
		perror("Could not execve");
		exit(EXIT_FAILURE);
	}
}