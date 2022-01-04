/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:58:34 by dyoula            #+#    #+#             */
/*   Updated: 2022/01/04 17:53:15 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_node
{
	struct s_node	*next;
	char			*content;
	// char			*option;
	int				index;
	char			**cmd;
/* 		cmd[0] = command else option */
}	t_node;

typedef struct s_list
{
	struct s_node			*head;
	struct s_node			*tail;
	int						length;
}	t_list;

typedef struct s_struct
{
	int		i;
	int		ac;
	char	**av;
	char	*path;
	char	**env;
	int		pipe[2];
	char	**to_try;
	int		fd_in;
	int		fd_out;
	int		heredoc;
	char	*buf_hdc;
	char	*final_path;
	t_list	*l_pathes;
	char	**cmd;
}	t_struct;

/*		PARSING		*/
char		*find_path(char **env);
void		add_slash(char **to_try);
int			add_cmd(char **to_try, char *cmd);
int			get_f_path(t_struct *c, char *tab);
int			split_cmd(t_struct *c);
char		*good_path(t_struct *c, char **str);
int			choose_parser(t_struct *c, int argc, char **argv);
int			check_argv(char **argv, t_struct *c);
int			cmd_is_path(char *tab, t_struct *c);
char		*cut_path(char *str, char *no_space);

/*		FREE		*/
void		free_d_tab(char **tab);
void		free_end(t_struct *c);
void		free_t_lists(t_list *c);

/*		INIT		*/
void		add_index(t_list *l);
t_struct	*init_struct(void);
int			set_struct(t_struct *c, int argc, char **argv, char **envi);
t_list		*init_list(void);
t_list		*list_end(t_list *list, char *content);
//int			malloc_pipe(t_struct *c);

/*		DISPLAY		*/
void		display_list(t_list *l);

/*		EXEC		*/
int			pipex(t_struct *c);

/* 		LIST		*/
char		**return_cmd(t_struct *c, int n);
char		*return_content(t_struct *c, int n);

/*		FILES		*/
int			check_files(t_struct *c);
int			read_heredoc(t_struct *c);
char		*cut_delimiter(char *txt, char *del);

#endif