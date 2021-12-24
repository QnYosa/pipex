/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriyoula <dimitriyoula@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:27:50 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/24 02:04:33 by dimitriyoul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include "includes/libft.h"

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

void	split_cmd(t_struct *c)
{
	int		i;
	t_node	*tmp;

	i = 1;
	tmp = c->l_pathes->head;
	while (tmp)
	{
		tmp->cmd = ft_split(c->av[++i], ' ');
		tmp = tmp->next;
	}
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
