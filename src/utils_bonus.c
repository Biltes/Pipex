/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:11:35 by migupere          #+#    #+#             */
/*   Updated: 2023/07/28 12:19:01 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	bad_args(void)
{
	ft_putstr_fd("Error: bad arguments\n", 2);
	ft_putstr_fd("Ex: ./pipex <file1> <cmd1>"
		" <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("	.pipex \"here_doc\""
		" <limiter> <cmd> <cmd1> <...> <file>\n", 1);
	exit(EXIT_FAILURE);
}

int	get_next_line_simple(char **line)
{
	char	*buffer;
	int		i;
	int		m;
	char	c;

	i = 0;
	m = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	m = read(0, &c, 1);
	while (m && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i++] = c;
		m = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (m);
}

