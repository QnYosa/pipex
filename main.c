/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:47:28 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/26 19:55:48 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include "includes/libft.h"

// // env permet de recuperer path poour executer la commande
// //int			path_okay();
int	check_files(t_struct *c)
{
	if (c->heredoc == 0)
	{
		c->fd_in = open(c->av[1], O_RDONLY);
		if (c->fd_in == -1)
		{
			free_end(c);
			return (c->fd_in);
		}
	}
	c->fd_out = open(c->av[c->ac - 1], \
	O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR); // 0644
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

int	read_heredoc(t_struct *c)
{
	char		buf[2];
	char		*txt;

	txt = ft_strdup("");
	if (!txt)
		return (0);
	while (read(0, buf, 1) > 0)
	{
		buf[1] = 0;
		txt = ft_strjoin(txt, buf);
		if (!strchr(txt, '\n'))
		{
			if (!ft_strncmp(txt, c->av[2], ft_strlen(c->av[2])))
			{
				printf("%s\n", txt);
				break ;
			}
		}
		else
		{
			free(txt);
			txt = ft_strdup("");
		}
	}
	c->buf_hdc = txt;
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
	if (!choose_parser(c, argc, argv))
		return (0);
	if (choose_parser(c, argc, argv) <= 0)
		return (0);
	return (0);
	split_cmd(c); // to secure 
	add_index(c->l_pathes);
	return (pipex(c));
}
