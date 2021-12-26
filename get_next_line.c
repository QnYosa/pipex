/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 13:04:28 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/12 21:08:32 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	free_after_newline(char *after_newline)
{
	if (after_newline)
		free(after_newline);
	return (-1);
}

int	inside_loop(char **line, char *after_newline)
{
	*line = ft_strdup(after_newline);
	free(after_newline);
	after_newline = NULL;
	return (0);
}

int	outside_loop(char **after_newline, char *tmp)
{
	tmp = ft_strdup(tmp);
	free(*after_newline);
	*after_newline = tmp;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char			buffer[BUFFER_SIZE + 1];
	int				i;
	char			*tmp;
	static char		*after_newline;
	int				ret;

	ret = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, "", 0) == -1)
		return (free_after_newline(after_newline));
	if (!after_newline)
		after_newline = ft_strdup("");
	while (!(ft_strchr(after_newline, '\n') && ret != 0))
	{
		ret = read(fd, &buffer, 1);
		buffer[ret] = '\0';
		if (ret == 0)
			return (inside_loop(line, after_newline));
		after_newline = ft_strjoin(after_newline, buffer);
	}
	i = 0;
	tmp = after_newline;
	while (tmp && *tmp++ != '\n')
		i++;
	*line = ft_strndup(after_newline, i);
	return (outside_loop(&after_newline, tmp));
}
