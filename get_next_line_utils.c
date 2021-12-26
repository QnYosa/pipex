/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyoula <dyoula@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:25:22 by dyoula            #+#    #+#             */
/*   Updated: 2021/12/12 21:10:07 by dyoula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../includes/libft.h"

char	*ft_strdup_and_free(char *str)
{
	int		i;
	char	*n_str;

	i = 0;
	while (str[i])
		i++;
	n_str = malloc(sizeof(char) * (i + 1));
	if (!n_str)
		return (NULL);
	i = -1;
	while (str[++i])
		n_str[i] = str[i];
	n_str[i] = 0;
	free(str);
	return (n_str);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*n_str;

	i = 0;
	while (str[i])
		i++;
	n_str = malloc(sizeof(char) * (i + 1));
	if (!n_str)
		return (NULL);
	i = -1;
	while (str[++i])
		n_str[i] = str[i];
	n_str[i] = 0;
	return (n_str);
}

char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*n_str;

	i = 0;
	while (str[i])
		i++;
	if (i > n)
		i = n;
	n_str = malloc(sizeof(char) * (i + 1));
	if (!n_str)
		return (NULL);
	i = -1;
	while (str[++i] && i < n)
		n_str[i] = str[i];
	n_str[i] = 0;
	return (n_str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	str = NULL;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = 0;
	if (s1)
	{	
		while (s1[++i])
			str[i] = s1[i];
		free(s1);
	}
	while (s2[++j])
		str[i + j] = s2[j];
	return (str);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = -1;
	if (!str)
		return (NULL);
	while (str[++i])
		if ((char)c == str[i])
			return ((char *)&str[i]);
	if (c == 0)
		return ((char *)(str + i));
	return (NULL);
}
