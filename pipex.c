/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:29:23 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/26 17:17:40 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "includes/pipex.h"
#include "includes/libft.h"

int	ifs_pipex(t_struct *c, int i, int tmp)
{
	if (i == 0 && c->heredoc == 1)
	{
		if (dup2(c->pipe[1], STDOUT_FILENO) < 0)
			return (-1);
		close(c->pipe[0]);
		execve(return_content(c, i), return_cmd(c, i), c->env);
	}
	else if (i == 0)
	{
		if (dup2(c->fd_in, STDIN_FILENO) < 0 || \
		dup2(c->pipe[1], STDOUT_FILENO) < 0)
			return (-1);
		close(c->pipe[0]);
		execve(return_content(c, i), return_cmd(c, i), c->env);
	}
	else if (i == c->l_pathes->length - 1)
	{
		if (dup2(c->fd_out, STDOUT_FILENO) < 0 || \
		dup2(tmp, STDIN_FILENO) < 0)
			return (-1);
		execve(return_content(c, i), return_cmd(c, i), c->env);
	}
	else
	{
		if (dup2(tmp, STDIN_FILENO) > 0 || dup2(c->pipe[1], STDOUT_FILENO))
			return (-1);
		close(c->pipe[0]);
		execve(return_content(c, i), return_cmd(c, i), c->env);
	}
	return (0);
}

int	loop_pipex(t_struct *c, int i, int pid, int tmp)
{
	while (++i < c->l_pathes->length)
	{
		if (pipe(c->pipe) < 0)
			return (-1);
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			if (ifs_pipex(c, i, tmp) < -1)
				return (-1);
		waitpid(-1, NULL, 0);
		close(c->pipe[1]);
		tmp = c->pipe[0];
	}
	return (1);
}

int	pipex(t_struct *c)
{
	int	i;
	int	pid;
	int	tmp;

	i = -1;
	pid = 0;
	tmp = 0;
	loop_pipex(c, i, pid, tmp);
	free_end(c);
	return (0);
}

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
