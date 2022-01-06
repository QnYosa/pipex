/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:27:50 by dyoula            #+#    #+#             */
/*   Updated: 2022/01/06 23:12:05 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../includes/libft.h"

void	add_index(t_list *l)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = l->head;
	while (tmp)
	{
		tmp->index = i;
		i++;
		tmp = tmp->next;
	}
}

int	split_cmd(t_struct *c)
{
	int		i;
	t_node	*tmp;

	if (!c->l_pathes)
		return (0);
	tmp = c->l_pathes->head;
	i = 1;
	if (c->heredoc == 1)
		i = 2;
	while (tmp)
	{
		tmp->cmd = ft_split(c->av[++i], ' ');
		if (!tmp->cmd)
		{
			free_t_lists(c->l_pathes);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

char	**return_cmd(t_struct *c, int n)
{
	int		i;
	t_node	*tmp;

	if (!c || n > c->l_pathes->length)
		return (NULL);
	tmp = c->l_pathes->head;
	i = 0;
	while (tmp)
	{
		if (i == n)
			return (tmp->cmd);
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

char	*return_content(t_struct *c, int n)
{
	int		i;
	t_node	*tmp;

	if (!c || n > c->l_pathes->length)
		return (NULL);
	tmp = c->l_pathes->head;
	i = 0;
	while (tmp)
	{
		if (i == n)
			return (tmp->content);
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}
