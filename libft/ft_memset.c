/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:22:36 by dyoula            #+#    #+#             */
/*   Updated: 2021/05/31 14:08:46 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = s;
	i = 0;
	if (n == 0)
		return (s);
	while (i <= n - 1)
	{
		p[i] = c;
		i++;
	}
	return (s);
}
