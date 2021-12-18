/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:29:23 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/16 17:35:57 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include "includes/libft.h"

int	n_pipes(t_struct *c)
{
	if (!c)
		return (0);
	while (++c->i < c->n_p)
	{
		c->pipe = malloc(sizeof(int *) * (c->ac - 3));
		if (!c->n_p)
		{
			free_end(c);
			return (0);
		}
	}
	return (1);
}
/*
int	pipex(t_struct *c)
{
	
}
*/