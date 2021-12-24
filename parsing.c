/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriyoula <dimitriyoula@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:55:38 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/23 19:13:50 by dimitriyoul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include "includes/libft.h"

void	add_slash(char **to_try)
{
	int	i;
	int end;

	i = -1;
	
	while (to_try[++i])
	{
		end = ft_strlen(to_try[i]);
		if (to_try[i][end - 1] != '/')
			to_try[i] = ft_strjoin(to_try[i], "/");	
	}
}

int	add_cmd(char **to_try, char *cmd)
{
	int		i;
	char	**av;

	av = ft_split(cmd, ' ');
	if (!av)
		return (0);
	i = -1;
	while (to_try[++i])
	{
		to_try[i] = ft_strjoin(to_try[i], av[0]); // a securiser
		if (!to_try[i])
			return (0);
	}
	free_d_tab(av);
	return (1);
}

int	cmd_is_path(char *tab, t_struct *c)
{
	if (access(tab, F_OK) == 0)
	{
		c->final_path = tab;
		return (0);
	}
	return (1);
}

int	check_errors(char *tab, t_struct *c)
{
	if (!cmd_is_path(tab, c))
		return (0);
	c->to_try = ft_split(c->path, ':');
	if (!c->to_try)
		return (0);
	if (tab[0] != '/')
		add_slash(c->to_try);
	if (!add_cmd(c->to_try, tab))
		return (0);
	return (1);
}

int	get_f_path(t_struct *c, char *tab)
{
	int	i;

	if (!check_errors(tab, c))
		return (0);
	i = -1;
	while (c->to_try[++i])
	{
		if (access(c->to_try[i], F_OK) == 0)
		{
			c->final_path = ft_strdup(c->to_try[i]);
			if (!c->final_path || !list_end(c->l_pathes, c->final_path))
				return (0);			
			free_d_tab(c->to_try);
			c->to_try = NULL;
			return (1);
		}
	}
	return (0);
}
