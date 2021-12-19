/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:27:50 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/19 20:36:51 by dyoula           ###   ########.fr       */
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
