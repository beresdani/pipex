/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:18:20 by dberes            #+#    #+#             */
/*   Updated: 2023/12/15 16:37:27 by dberes           ###   ########.fr       */
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

typedef struct t_data
{
    int             pipes;
	int             (*fd)[2];
    pid_t           pid[];
}	s_data;

void	first_child_process(char **argv, s_data *data, char *path, char **envp, int ind);
void	multi_child_process(char **argv, s_data *data, char *path, char **envp, int ind);
void	multi_parent_process(char **argv, s_data *data, char *path, char **envp, int ind);
void	child_process(char **argv, int fd[2], char *path, char **envp, int ind);
void	parent_process(char **argv, int fd[2], char *path, char **envp, int ind);
char	*get_path(char **env);
char	*get_dir(char *str, char *cmd);
void	free_array(char **arr);
int		single_pipe(char **argv, char **env);
int		multi_pipe(int pipes, char **argv, char **env);

#endif
