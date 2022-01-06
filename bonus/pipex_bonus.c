/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:29:23 by dyoula            #+#    #+#             */
/*   Updated: 2022/01/06 23:11:54 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../includes/libft.h"

void	close_all(t_struct *c, int tmp)
{
	close(c->fd_in);
	close(c->fd_out);
	close(c->pipe[0]);
	close(c->pipe[1]);
	close(tmp);
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
	if (i == 0 && c->heredoc == 0)
		close_mid(c, tmp);
	else if (i == 0 && c->heredoc == 0)
		close_all(c, tmp);
	else if (i == c->l_pathes->length - 1)
		close_all(c, tmp);
	else
		close_all(c, tmp);
	execve(return_content(c, i), return_cmd(c, i), c->env);
	free_end(c);
	exit (127);
}

int	ifs_pipex(t_struct *c, int i, int tmp)
{
	if (i == 0 && c->heredoc == 1)
	{
		write(c->pipe[1], c->buf_hdc, ft_strlen(c->buf_hdc));
		if (dup2(c->pipe[1], 1) < 0 || dup2(c->pipe[0], 0) < 0)
			return (-1);
		close(c->pipe[0]);
		close(c->pipe[1]);
		close(tmp);
		execve(return_content(c, i), return_cmd(c, i), c->env);
		free_end(c);
		exit(127);
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
		free_end(c);
		exit(127);
	}
	else if (i == c->l_pathes->length - 1)
	{
		if (dup2(c->fd_out, STDOUT_FILENO) < 0 || \
		dup2(tmp, STDIN_FILENO) < 0)
			return (-1);
		close(c->fd_out);
		close(tmp);
		close(c->pipe[0]);
		close(c->pipe[1]);
		execve(return_content(c, i), return_cmd(c, i), c->env);
		free_end(c);
		exit(127);
	}
	else
	{
		if (dup2(tmp, STDIN_FILENO) < 0 || dup2(c->pipe[1], STDOUT_FILENO) < 0)
			return (-1);
		close(c->pipe[0]);
		close(c->pipe[1]);
		close(tmp);
		close(c->fd_out);
		execve(return_content(c, i), return_cmd(c, i), c->env);
		free_end(c);
		exit(127);
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
		if (i > 0)
			close(tmp);
		tmp = c->pipe[0];
		close(c->pipe[1]);
	}
	i = 0;
	while (i < c->l_pathes->length)
	{
		waitpid(0, NULL, 0);
		i++;
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
	//hdc_to_fd_in(c);
	loop_pipex(c, i, pid, tmp);
	close_all(c, tmp);
	free_end(c);
	return (0);
}
