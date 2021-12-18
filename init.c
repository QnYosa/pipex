/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:48:28 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/15 23:36:18 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include "includes/libft.h"

t_struct	*init_struct(void)
{
	t_struct	*c;

	c = NULL;
	c = (t_struct *)malloc(sizeof(t_struct));
	if (!c)
		return (NULL);
	c->i = -1;
	c->ac = 0;
	c->n_p = -1;
	c->av = NULL;
	c->env = NULL;
	//c->n_fork = 0;
	//c->pipe = NULL;
	c->path = NULL;
	c->to_try = NULL;
	c->l_pathes = NULL;
	c->final_path = NULL;
	return (c);
}

void	set_struct(t_struct *c, int argc, char **argv, char **envi)
{
	if (!c || !argc || !argv || !envi)
		return ;
	c->ac = argc;
	c->av = argv;
	c->env = envi;
	c->final_path = NULL;
	c->path = find_path(envi);
	c->l_pathes = init_list();
}

t_list	*init_list(void)
{
	t_list	*list;

	list = NULL;
	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

t_list	*list_end(t_list *list, char *content)
{
	t_node	*node;

	if (!list || !content)
		return (NULL);
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	if (list->head == NULL)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
	list->length++;
	return (list);
}

	// execve(/bin/ls, {"ls", "-l"}, env);