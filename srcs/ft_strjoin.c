/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:52:08 by jeulliot          #+#    #+#             */
/*   Updated: 2022/02/23 15:57:40 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

static size_t	ft_strlen1(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i ++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	lens1;
	size_t	tlen;
	char	*dest;

	i = 0;
	lens1 = ft_strlen1(s1);
	tlen = ft_strlen1(s1) + ft_strlen1(s2) + 1;
	dest = malloc(sizeof(char) * tlen);
	if (dest == NULL || s1 == NULL || s2 == NULL)
		return (NULL);
	while (i < lens1)
	{
		dest[i] = s1[i];
		i ++;
	}
	while (i < tlen - 1)
	{
		dest[i] = s2[i - lens1];
		i ++;
	}
	dest[i] = '\0';
	return (dest);
}
