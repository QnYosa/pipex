/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdc_or_not.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:28:28 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/26 18:58:41 by dyoula           ###   ########.fr       */
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

int	heredoc_here(t_struct *c, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	read_heredoc(c);
	c->fd_in = open("infile", \
	O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (c->fd_in == -1)
	{
		free_end(c);
		return (c->fd_out);
	}
	write(c->fd_in, &c->buf_hdc, ft_strlen(c->buf_hdc));
	return (1);
}

int	choose_parser(t_struct *c, int argc, char **argv)
{
	if (c->heredoc == 0)
		return (no_heredoc(c, argc, argv));
	else
		return (heredoc_here(c, argc, argv));
}
