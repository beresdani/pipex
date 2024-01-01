/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:18:20 by dberes            #+#    #+#             */
/*   Updated: 2024/01/01 12:45:59 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h> 
# include <stdio.h> 
# include <string.h> 
# include <stdlib.h>
# include <limits.h>
# include <ctype.h>
# include <stdarg.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <sys/types.h> 
# include <sys/wait.h>

typedef struct s_plist
{
	int					index;
	int					fd[2];
	pid_t				pid;
	struct s_plist		*next;
}	t_plist;

typedef struct s_data
{
	int		pipes;
	int		argc;
	char	*path;
	char	**env;
	char	**argv;
	char	**dirs;
}	t_data;

void	first_child_process(t_plist **lst, t_data *data, int ind);
void	multi_child_process(t_plist **lst, t_data *data, int ind);
void	last_child_process(t_plist **lst, t_data *data, int ind);
void	multi_parent_process(t_plist **lst, t_data *data, int ind);
void	child_process(int fd[2], t_data *data, int ind, int pid);
void	parent_process(int fd[2], t_data *data, int ind, int pid);
char	*get_path(char **env);
char	*get_dir(char *str, char **args, int pid);
void	free_array(char **arr);
int		single_pipe(char **argv, char **env);
int		multi_pipe(int pipes, char **argv, char **env, int argc);
void	add_pipe_node(t_plist **lst, t_plist *new);
int		list_size(t_plist **lst);
void	fd_closer(int end, t_plist **lst);
void	multi_parent(t_plist *lst);
void	child_processes(t_plist **lst, t_data *data, int ind);
void	wait_for_child(t_plist *lst);
void	free_list(t_plist *lst);
char	*get_dir_multi(char *str, char **args);
void	check_commands(t_data *data);
void	free_exit(char **args, t_data *data, int ex_code);
t_plist	*get_to_node(t_plist *node, int ind);
void	dirs_calloc(t_data *data);
void	free_handler(t_data *data, char **args, int *ex, int *args_freed);
void	free_handler2(char **args, int *ex, int *args_freed);

#endif
