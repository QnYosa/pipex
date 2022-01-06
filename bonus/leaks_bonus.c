/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:50:03 by dyoula            #+#    #+#             */
/*   Updated: 2022/01/06 22:59:57 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "includes/libft.h"

void	free_d_tab(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
	{
		if (tab[i])
			free(tab[i]);
	}
	free(tab);
	tab = NULL;
}

void	free_t_lists(t_list *c)
{
	t_node	*del;
	t_node	*i;

	if (!c)
		return ;
	i = c->head;
	while (i)
	{
		del = i;
		free_d_tab(del->cmd);
		free(del->content);
		i = i->next;
		free(del);
	}
	free(c);
}

void	free_end(t_struct *c)
{
	if (!c)
		return ;
	if (c->heredoc != 1 && c->fd_in != -1)
		close (c->fd_in);
	if (c->heredoc == 1 && c->buf_hdc)
		free(c->buf_hdc);
	if (c->l_pathes != NULL)
	{
		free_t_lists(c->l_pathes);
		c->l_pathes = NULL;
	}
	if (c)
		free(c);
	c = NULL;
}
