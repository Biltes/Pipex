/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:03:05 by migupere          #+#    #+#             */
/*   Updated: 2023/07/28 11:32:40 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft_curr/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>

void	exit_error(void);
void	custom_error(char *header, char *msg);
char	*get_path(char *cmd, char *envp[]);
void	run(char *argv, char *envp[]);
void	child_process(char *argv[], char *envp[], int *fd);
void	parent_process(char *argv[], char *envp[], int *fd);
void	child_process_bonus(char *argv, char **envp);
void	doc_append(char *limiter, int argc);
void	bad_args(void);
int		get_next_line_simple(char **line);

#endif
