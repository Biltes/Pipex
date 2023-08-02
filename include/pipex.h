/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:03:05 by migupere          #+#    #+#             */
/*   Updated: 2023/08/02 15:24:04 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft_curr/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>

void	ft_here_doc(char *eof);
void	check(int result, char *msg);
char	*get_path(char *cmd, char **envp);
void	exec_cmd(char *cmd, char **envp);
void	redirect(char *file, char *cmd, char **envp);
int		main (int argc, char **argv, char **envp);

#endif
