/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:29:23 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/20 22:57:35 by dyoula           ###   ########.fr       */
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

int	pipex(t_struct *c)
{
	int	pid;

	// creation du tableau de pipe.
	printf("hola\n");
	printf("nombre de pipes : %d\n", c->l_pathes->length);
	if (!malloc_pipe(c))
		return (0);
	if (pipe(c->pipe[0]) == -1)
	{
		printf("pipe failed\n");
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		int x;

		x = 24;
		//dup2();
		close(c->pipe[0][1]);
		printf("Salut\n");
	}
	else
	{
		//dup2();
		close(c->pipe[0][0]);
		printf("priviet\n");
	}
	return (0);
}
