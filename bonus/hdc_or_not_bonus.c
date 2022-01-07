/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdc_or_not_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:28:28 by dyoula            #+#    #+#             */
/*   Updated: 2022/01/07 21:53:59 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../includes/libft.h"

int	no_heredoc(t_struct *c, int argc, char **argv)
{
	int			i;

	i = 1;
	while (++i < argc - 1)
	{
		if (cmd_is_path(argv[i], c))
		{
			if (!list_end(c->l_pathes, c->av[i]))
				return (0);
			free(c->final_path);
		}
		else
		{
			if (!get_f_path(c, argv[i]))
			{
				perror("Not a command\n");
				return (0);
			}			
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
			if (ft_strncmp(txt, c->av[2], ft_strlen(txt) - 1) == 0)
			{
				free(txt);
				return (1);
			}
			c->buf_hdc = ft_strjoin(c->buf_hdc, txt);
			if (!c->buf_hdc)
				return (0);
			free(txt);
			txt = ft_strdup("");
			if (!txt)
				return (0);
		}
	}
	free(txt);
	return (0);
}

int	heredoc_parser(t_struct *c)
{
	int			i;

	i = 2;
	while (++i < c->ac - 1)
	{
		if (cmd_is_path(c->av[i], c))
		{
			if (!list_end(c->l_pathes, c->av[i]))
			{
				free_end(c);
				return (0);
			}
		}
		else
		{
			if (!get_f_path(c, c->av[i]))
			{
				perror("not a command");
				return (0);
			}
		}
	}
	return (1);
}

int	heredoc_here(t_struct *c)
{
	read_heredoc(c);
	if (!heredoc_parser(c))
		return (0);
	return (1);
}

int	choose_parser(t_struct *c, int argc, char **argv)
{
	if (c->heredoc == 1)
		return (heredoc_here(c));
	else
		return (no_heredoc(c, argc, argv));
}
