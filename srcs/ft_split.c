/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:19:48 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/13 15:54:24 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (*str)
		while (str[i] != '\0')
			i ++;
	return (i);
}

static size_t	ft_nb_slot(const char *str, char c)
{
	size_t	nb_str;
	size_t	k;

	k = 0;
	nb_str = 0;
	while (*str)
	{
		if (*str != c && k == 0)
		{
			k = 1;
			nb_str ++;
		}
		else if (*str == c)
			k = 0;
		str ++;
	}
	return (nb_str);
}

static char	*ft_strncpy(const char *src, size_t index, size_t end)
{
	size_t	i;
	char	*dest;

	dest = malloc(sizeof(char) * (end - index + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (index < end)
	{
		dest[i] = src[index];
		i++;
		index ++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	nb_str;
	size_t	i;
	int		k;

	i = -1;
	nb_str = 0;
	k = -1;
	if (s == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_nb_slot(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && k == -1)
			k = i;
		else if ((s[i] == c || i == ft_strlen(s)) && k != -1)
		{
			tab[nb_str++] = ft_strncpy(s, k, i);
			k = -1;
		}
	}
	tab[nb_str] = 0;
	return (tab);
}
