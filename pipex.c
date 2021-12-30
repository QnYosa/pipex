/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:29:23 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/30 18:51:39 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "includes/pipex.h"
#include "includes/libft.h"

int	ifs_pipex(t_struct *c, int i, int tmp)
{
	if (i == 0 && c->heredoc == 1)
	{
		dup2(c->pipe[1], 1);
		write(1, c->buf_hdc, ft_strlen(c->buf_hdc));
		close(c->pipe[0]);
		execve(return_content(c, i), return_cmd(c, i), c->env);
	}
	else if (i == 0 && c->heredoc == 0)
	{
		if (dup2(c->fd_in, STDIN_FILENO) < 0 || \
		dup2(c->pipe[1], STDOUT_FILENO) < 0)
			return (-1);
		close(c->fd_in);
		close(c->pipe[0]);
		close(c->pipe[1]);
		execve(return_content(c, i), return_cmd(c, i), c->env);
	}
	else if (i == c->l_pathes->length - 1)
	{
		if (dup2(c->fd_out, STDOUT_FILENO) < 0 || \
		dup2(tmp, STDIN_FILENO) < 0)
			return (-1);
		close(c->fd_out);
		close(tmp);
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
		waitpid(pid, NULL, 0);
		tmp = c->pipe[0];
		close(c->pipe[1]);
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
	close(c->fd_out);
	if (c->heredoc == 0)
		close(c->fd_in);
	free_end(c);
	return (0);
}
