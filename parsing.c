/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:55:38 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/15 19:32:14 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include "includes/libft.h"

void	add_slash(char **to_try)
{
	int	i;

	i = -1;
	while (to_try[++i])
		to_try[i] = ft_strjoin(to_try[i], "/");
}

void	add_cmd(char **to_try, char *cmd)
{
	int	i;

	i = -1;
	while (to_try[++i])
		to_try[i] = ft_strjoin(to_try[i], cmd);
}

int	get_f_path(t_struct *c, char *tab)
{
	int	i;

	i = -1;
	c->to_try = ft_split(c->path, ':');
	add_slash(c->to_try);
	add_cmd(c->to_try, tab);
	while (c->to_try[++i])
	{
		if (access(c->to_try[i], F_OK) == 0)
		{
			c->final_path = ft_strdup(c->to_try[i]);
			list_end(c->l_pathes, c->final_path);
			c->n_p++;
			free_d_tab(c->to_try);
			c->to_try = NULL;
			return (1);
		}
	}
	return (0);
}
