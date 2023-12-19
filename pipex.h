/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:18:20 by dberes            #+#    #+#             */
/*   Updated: 2023/12/19 15:06:49 by dberes           ###   ########.fr       */
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
    int             index;
	int             fd[2];
    pid_t           pid;
    struct s_plist   *next;
}	t_plist;

typedef struct s_data
{
    int     pipes;
    char    *path;
    char    **env;
    char    **argv;
}   t_data;


void	first_child_process(char **argv, t_plist **lst, char *path, char **envp, int ind);
void	multi_child_process(char **argv, t_plist **lst, char *path, char **envp, int ind);
void	multi_parent_process(char **argv, t_plist **lst, char *path, char **envp, int ind);
void	child_process(char **argv, int fd[2], char *path, char **envp, int ind);
void	parent_process(char **argv, int fd[2], char *path, char **envp, int ind);
char	*get_path(char **env);
char	*get_dir(char *str, char *cmd);
void	free_array(char **arr);
int		single_pipe(char **argv, char **env);
int		multi_pipe(int pipes, char **argv, char **env);
void	add_pipe_node(t_plist **lst, t_plist *new);
int     list_size(t_plist **lst);
void	fd_closer(int end, t_plist **lst);
void	multi_parent(t_plist **lst, int pipes, int i);
void	child_processes(char **argv, t_plist **lst, t_data *data, int ind);

#endif
