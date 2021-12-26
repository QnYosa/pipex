/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriyoula <dimitriyoula@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:50:03 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/24 17:14:16 by dimitriyoul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
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
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
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
		i = i->next;
		free(del);
	}
	free(c);
}

void	free_end(t_struct *c)
{
	if (c->fd_out != -1)
		close(c->fd_out);
	if (c->fd_in != -1)
		close (c->fd_in);
	if (c->final_path != NULL)
		free(c->final_path);
	if (c->to_try != NULL)
		free_d_tab(c->to_try);
	if (c->l_pathes != NULL)
	{
		free_t_lists(c->l_pathes);
		c->l_pathes = NULL;
	}
	if (c->buf_hdc)
		free(c->buf_hdc);
	if (c)
		free(c);
	c = NULL;
}
