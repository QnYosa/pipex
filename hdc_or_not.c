/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdc_or_not.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:28:28 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/29 19:16:03 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include "includes/libft.h"

int	no_heredoc(t_struct *c, int argc, char **argv)
{
	int			i;

	i = 1;
	while (++i < argc - 1)
	{
		if (!get_f_path(c, argv[i]))
		{
			free_end(c);
			perror("JE vous emmerde et je rentre a ma maison\n");
			return (0);
		}
	}
	return (1);
}

int	read_heredoc(t_struct *c)
{
	char		buf[2];
	char		*txt;

	c->buf_hdc = ft_strdup("");
	txt = ft_strdup("");
	if (!txt || !c->buf_hdc)
		return (0);
	while (read(0, buf, 1) > 0)
	{
		buf[1] = 0;
		txt = ft_strjoin(txt, buf);
		if (strchr(txt, '\n'))
		{
			// printf("return = %d", ft_strncmp(txt, c->av[2], ft_strlen(txt) - 1) == 0);
			if (ft_strncmp(txt, c->av[2], ft_strlen(txt) - 1) == 0)
			{
				free(txt);
				return (0);
			}
			c->buf_hdc = ft_strjoin(c->buf_hdc, txt);
			free(txt);
			txt = ft_strdup("");
			if (!txt)
				return (0);
		}
	}
	return (0);
}

int	heredoc_parser(t_struct *c)
{
	int			i;

	i = 2;
	while (++i < c->ac - 1)
	{
		if (!get_f_path(c, c->av[i]))
		{
			free_end(c);
			perror("je vous emmerde et je rentre a ma maison");
			return (0);
		}
	}
	return (1);
}

int	heredoc_here(t_struct *c)
{
	read_heredoc(c);
	heredoc_parser(c);
	/* write(c->fd_in, c->buf_hdc, ft_strlen(c->buf_hdc)); */
	return (1);
}

int	choose_parser(t_struct *c, int argc, char **argv)
{
	if (c->heredoc == 1)
		return (heredoc_here(c));
	else
		return (no_heredoc(c, argc, argv));
}
