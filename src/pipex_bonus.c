/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:11:17 by migupere          #+#    #+#             */
/*   Updated: 2023/08/01 12:25:25 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check(int result, char *msg)
{
	if (result == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror(msg);
		exit(EXIT_FAILURE);
	}
}

char	*get_path(char *cmd, char **envp)
{
	char	*path;
	char	*aux;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (ft_strdup(cmd));
	envp[i] += 5;
	while (*envp[i])
	{
		path = ft_substr(envp[i], 0, ft_strclen(envp[i], ':'));
		aux = ft_strjoin(path, "/");
		free(path);
		path = ft_strjoin(aux, cmd);
		free(aux);
		if (!access(path, F_OK))
			return (path);
		free(path);
		envp[i] += ft_strclen(envp[i], ':')
			+ (ft_strclen(envp[i], ':') != ft_strlen(envp[i]));
	}
	return (ft_strdup(cmd));
}

void	exec_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (ft_strchr(args[0], '/'))
		path = ft_strdup(args[0]);
	else
		path = get_path(args[0], envp);
	execve(path, args, envp);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("pipex: %s: command not found\n", args[0]);
	ft_free_array(args);
	free(path);
	exit(127);
}

void	redirect(char *file, char *cmd, char **envp)
{
	pid_t	pid;
	int		fd[2];

	check(pipe(fd), "pipe");
	pid = fork();
	check(pid, "fork");
	if (pid)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		waitpid(pid, NULL, WNOHANG);
	}
	else
	{
		check(access(file, R_OK), file);
		dup2(fd[1], STDOUT_FILENO);
		exec_cmd(cmd, envp);
		close(fd[0]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	here_doc;
	int	fd_file[2];

	if (argc >= 6 || (argc == 5 && ft_strncmp(argv[1], "here_doc", 8)))
	{
		here_doc = (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 8));
		if (here_doc)
			ft_here_doc(argv[2]);
		fd_file[0] = open(argv[1], O_RDONLY, 0644);
		dup2(fd_file[0], STDIN_FILENO);
		i = 2 + here_doc;
		while (i < argc - 2)
			redirect(argv[1], argv[i++], envp);
		fd_file[1] = open(argv[argc - 1], O_RDWR | O_TRUNC * !here_doc
				| O_APPEND * here_doc | O_CREAT, 0644);
		check(fd_file[1], argv[argc - 1]);
		dup2(fd_file[1], STDOUT_FILENO);
		exec_cmd(argv[argc - 2], envp);
	}
	else
		ft_printf("Usage:./pipex file1/(here_doc LIMITER) cmd1 .. cmdx file2\n");
	return (1);
}
