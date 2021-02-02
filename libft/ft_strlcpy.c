/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 11:53:54 by aglorios          #+#    #+#             */
/*   Updated: 2019/11/18 17:23:38 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	if (dest == 0 || src == 0)
		return (0);
	while (src[a] != '\0')
		a++;
	if (size == 0)
		return (a);
	while (b + 1 < size && src[b] != '\0')
	{
		dest[b] = src[b];
		b++;
	}
	dest[b] = '\0';
	return (a);
}
