/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:28:28 by dyoula            #+#    #+#             */
/*   Updated: 2022/01/06 22:29:55 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include "includes/libft.h"

int	path(t_struct *c, int argc, char **argv)
{
	int			i;

	i = 1;
	while (++i < argc - 1)
	{
		if (cmd_is_path(argv[i], c))
		{
			if (!list_end(c->l_pathes, c->av[i]))
				return (0);
		}
		else
		{
			if (!get_f_path(c, argv[i]))
			{
				perror("JE vous emmerde et je rentre a ma maison\n");
				return (0);
			}			
		}
	}
	return (1);
}

int	choose_parser(t_struct *c, int argc, char **argv)
{
	return (path(c, argc, argv));
}
