/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 09:57:57 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/21 13:41:20 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t a;
	size_t b;
	size_t i;

	a = 0;
	b = 0;
	i = 0;
	while (dest[a] != '\0' && a < size)
		a++;
	i = i + a;
	while (src[b])
		b++;
	i = i + b;
	if (a == size)
		return (i);
	b = 0;
	while (src[b] && a + b < size - 1)
	{
		dest[a + b] = src[b];
		b++;
	}
	dest[a + b] = '\0';
	return (i);
}
