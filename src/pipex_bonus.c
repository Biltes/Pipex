/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:11:17 by migupere          #+#    #+#             */
/*   Updated: 2023/07/28 12:19:16 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_bonus(char *argv, char **envp)
{
	pid_t	process;
	int		fd[2];

	if (pipe(fd) == -1)
		exit_error();
	process = fork();
	if (process == -1)
		exit_error();
	if (process == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		run(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(process, NULL, 0);
	}
}

void	doc_append(char *limiter, int argc)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (argc < 6)
		bad_args();
	if (pipe(fd) == -1)
		exit_error();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line_simple(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int	i;
	int	filein;
	int	fileout;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			doc_append(argv[2], argc);
		}
		else
		{
			i = 2;
			fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			filein = open(argv[1], O_RDONLY, 0777);
			dup2(filein, STDIN_FILENO);
		}
		while (i++ < argc - 2)
			child_process_bonus(argv[i], envp);
		dup2(fileout, STDOUT_FILENO);
		run(argv[argc - 2], envp);
	}
	bad_args();
}
