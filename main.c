/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:47:28 by dyoula            #+#    #+#             */
/*   Updated: 2022/01/02 20:57:14 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include "includes/libft.h"

int	check_files(t_struct *c)
{
	int	ret;

	if (c->heredoc == 0)
	{
		c->fd_in = open(c->av[1], O_RDONLY);
		if (c->fd_in == -1)
		{
			ret = c->fd_in;
			free_end(c);
			return (ret);
		}
	}
	c->fd_out = open(c->av[c->ac - 1], \
	O_WRONLY | O_CREAT, 0777);
	if (c->fd_out == -1)
	{
		free_end(c);
		return (c->fd_out);
	}
	return (1);
}

int	check_argv(char **argv, t_struct *c)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (!ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")))
		{
			c->heredoc = 1;
			return (1);
		}
	}
	c->heredoc = 0;
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_struct	*c;

	if (!env || argc < 5)
		return (0);
	c = init_struct();
	if (!c)
		return (0);
	check_argv(argv, c);
	set_struct(c, argc, argv, env);
	if (check_files(c) == -1)
		return (-1);
	if (c->heredoc == 1 && argc < 6)
	{
		free_end(c);
		return (0);
	}
	if (choose_parser(c, argc, argv) <= 0)
	{
		free_end(c);
		return (0);
	}
	if (!split_cmd(c))
	{
		free_end(c);
		return (0);
	}
	add_index(c->l_pathes);
	return (pipex(c));
}
