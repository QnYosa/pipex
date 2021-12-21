/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:29:23 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/21 23:18:19 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "includes/pipex.h"
#include "includes/libft.h"

int	n_pipes(t_struct *c)
{
	if (!c)
		return (0);
	while (++c->i < c->n_p)
	{
		c->pipe = malloc(sizeof(int *) * (c->l_pathes->length - 1));
		if (!c->pipe)
		{
			free_end(c);
			return (0);
		}
	}
	return (1);
}

int	pipe_tab(t_struct *c)
{
	int	i;

	i = -1;
	while (++i < c->ac - 4)
	{
		if (pipe(c->pipe[i]) == -1)
		{
			//fonction qui close les pipes qui n'ont pas fail;
			return (-1);	
		}	
	}
	return (1);
}

int	loop_pipex(t_struct *c)
{
	int	i;
	int	pid;

	i = -1;
	while (++i < c->l_pathes->length)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
/*
|	fermer tous les fds sauf ceux que j'utilise 

	Si [ Premiere cmd ]
	|
	|	dup2(fd_in, stdin)
	|
	Sinon Si [ Derniere cmd ]
	|
	|	dup2(fd_out, stdout)
	|
	Sinon
	|
	|	dup2(pipe[i - 1][0], stdin)
	|	dup2(pipe[i][1], stdout)
	|
	FinSi

*/
			close(STDIN_FILENO);
			dup2(c->pipe[i][0], STDIN_FILENO);
			close(STDOUT_FILENO);
			dup2(c->pipe[i + 1][1], STDOUT_FILENO);
			execve(return_content(c, i), return_cmd(c, i), c->env);
		}
	}
	return (1);
}

int	pipex(t_struct *c)
{
	int	i;

	i = c->l_pathes->length - 1;
	// pipe = nb cmd - 1 donc i 
	printf("hola\n");
	printf("nombre de pipes : %d\n", c->l_pathes->length);
	if (!malloc_pipe(c))
		return (0);
	if (pipe_tab(c) == -1)
		return (1);
	// dup2(c->fd_in, STDIN_FILENO);
	loop_pipex(c);
	close(STDIN_FILENO);
	dup2(c->fd_in, STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(c->fd_out, STDOUT_FILENO);
	close(c->pipe[i][1]);
	execve(return_content(c, i), return_cmd(c, i), c->env);
	waitpid(-1, NULL, 0);
	return (0);
}
