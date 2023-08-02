/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:11:35 by migupere          #+#    #+#             */
/*   Updated: 2023/08/01 12:25:20 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_here_doc(char *eof)
{
	char	*line;
	int		fd_here_doc;

	fd_here_doc = open("here_doc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	ft_printf("> ");
	line = get_next_line(0);
	while (line && (ft_strncmp(line, eof, ft_strlen(eof))
			|| ft_strclen(line, '\n') != ft_strlen(eof)))
	{
		ft_putstr_fd(line, fd_here_doc);
		free(line);
		ft_printf("> ");
		line = get_next_line(0);
	}
	free(line);
	close(fd_here_doc);
}
