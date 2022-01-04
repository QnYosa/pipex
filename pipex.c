/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:29:23 by dyoula            #+#    #+#             */
/*   Updated: 2022/01/04 23:26:54 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "includes/pipex.h"
#include "includes/libft.h"

void	close_all(t_struct *c)
{
	int	i;

	i = 0;
	while (i <= c->ac)
	{
		close(i);
		i++;
	}
}

void	close_mid(t_struct *c, int tmp)
{
	close(tmp);
	close(c->pipe[0]);
	close(c->pipe[1]);
	close(c->fd_out);
}

void	exec_close_i(t_struct *c, int i, int tmp)
{
	if (i == 0 && c->heredoc == 1)
		close_all(c);
	else if (i == 0 && c->heredoc == 0)
		close_all(c);
	else if (i == c->l_pathes->length - 1)
		close_mid(c, tmp);
	else
		close_mid(c, tmp);
	execve(return_content(c, i), return_cmd(c, i), c->env);
}

int	ifs_pipex(t_struct *c, int i, int tmp)
{
	if (i == 0 && c->heredoc == 1)
	{
		write(c->pipe[1], c->buf_hdc, ft_strlen(c->buf_hdc));
		if (dup2(c->pipe[1], 1) < 0)
			return (-1);
	}
	else if (i == 0 && c->heredoc == 0)
	{
		if (dup2(c->fd_in, 0) < 0 || dup2(c->pipe[1], 1) < 0)
			return (-1);
	}
	else if (i == c->l_pathes->length - 1)
	{
		if (dup2(c->fd_out, 1) < 0 || dup2(tmp, 0) < 0)
			return (-1);
	}
	else
	{	
		if (dup2(tmp, STDIN_FILENO) < 0 || dup2(c->pipe[1], STDOUT_FILENO) < 0)
			return (-1);
	}
	exec_close_i(c, i, tmp);
	return (0);
}

int	loop_pipex(t_struct *c, int i, int pid, int tmp)
{
	while (++i < c->l_pathes->length)
	{
		if (pipe(c->pipe) < 0)
		{
			close_all(c);
			return (-1);
		}
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			if (ifs_pipex(c, i, tmp) < -1)
				return (-1);
		}
		else 
		{
			waitpid(pid, NULL, 0);
			tmp = c->pipe[0];
			close(c->pipe[1]);
		}
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
	//display_list(c->l_pathes);
	loop_pipex(c, i, pid, tmp);
	close(c->fd_out);
	if (c->heredoc == 0)
		close(c->fd_in);
	free_end(c);
	return (0);
}
