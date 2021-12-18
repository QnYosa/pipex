/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:03:53 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/16 16:46:58 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include "includes/libft.h"

char	*ft_strnstr(char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*s2 == '\0')
		return (s1);
	if (n == 0)
		return (NULL);
	while (s1[i] && i < n)
	{
		j = 0;
		while (s1[i + j] == s2[j] && i < n && s1[i + j])
		{
			if (s1[i + j] && s2[j + 1] == 0 && i + j < n)
				return (&s1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*find_path(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4))
			i++;
		else
			return (env[i] + 5);
	}
	return (NULL);
}

void	display_list(t_list *l)
{
	t_node	*i;
	int		j;

	if (!l)
		return ;
	i = l->head;
	while (i)
	{
		j = -1;
		printf("salut %s\n", i->content);
		printf("salut %d\n", i->index);
		while (i->cmd[++j])
			printf("salut- %s\n", i->cmd[j]);
		i = i->next;
	}
}

char	*good_path(t_struct *c, char **str)
{
	t_node	*i;

	i = c->l_pathes->head;
	if (!str || !c)
		return (NULL);
	while (i)
	{
		if (ft_strncmp(i->cmd[0], *str, ft_strlen(*str)))
		{
			printf("hola %s\n", *str);
			execve(i->content, &i->cmd[0], c->env);
			return (i->content);
		}
		i = i->next;
	}
	return (NULL);
}
