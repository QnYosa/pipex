/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:58:34 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/18 20:01:19 by dyoula           ###   ########.fr       */
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
# include "libft.h"

typedef struct s_node
{
	struct s_node	*next;
	char			*content;
	char			*option;
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
	int		n_p;
	char	**av;
	char	**cmd; // car admet des options
	char	*path;
	char	**env;
	// int	n_fork;
	int		**pipe; //toujours un de plus que de process
	char	**to_try;
	t_list	*f_pathes;
	char	*final_path;
	t_list	*l_pathes; // liste des cmd
}	t_struct;

/*		PARSING		*/
char		*find_path(char **env);
void		add_slash(char **to_try);
void		add_cmd(char **to_try, char *cmd);
int			get_f_path(t_struct *c, char *tab);
void		split_cmd(t_struct *c);
char		*good_path(t_struct *c, char **str);

/*		FREE		*/
void		free_d_tab(char **tab);
void		free_end(t_struct *c);

/*		INIT		*/
void		add_index(t_list *l);
void		set_struct(t_struct *c, int argc, char **argv, char **envi);
t_struct	*init_struct(void);
t_list		*init_list(void);
t_list		*list_end(t_list *list, char *content);

/*		DISPLAY		*/
void		display_list(t_list *l);

/*		EXEC		*/
#endif