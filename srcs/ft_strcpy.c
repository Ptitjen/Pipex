/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:38:37 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/13 15:50:47 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i ++;
	return (i);
}

char	*ft_strcpy(char *dst, char *src)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_strlen(src);
	dst = malloc(sizeof(char) * (n + 1));
	while (i < n)
	{
		dst[i] = src[i];
		i ++;
	}			
	dst[i] = '\0';
	return (dst);
}
