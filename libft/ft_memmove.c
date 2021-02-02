/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:20:20 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/21 13:18:50 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	a;

	if ((char*)dest == 0 && (char*)src == 0)
		return (0);
	if ((char*)src < (char*)dest)
	{
		a = n;
		while (a > 0)
		{
			a--;
			*((char*)dest + a) = *((char*)src + a);
		}
	}
	else
	{
		a = 0;
		while (a < n)
		{
			*((char*)dest + a) = *((char*)src + a);
			a++;
		}
	}
	return (dest);
}
