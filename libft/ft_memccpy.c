/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:46:41 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/21 12:52:26 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char*)src;
	while (n != 0)
	{
		*(unsigned char*)dest++ = *(unsigned char*)src++;
		if (*(unsigned char*)src == (unsigned char)c)
		{
			*(unsigned char*)dest++ = *(unsigned char*)src++;
			return (dest);
		}
		n--;
		str++;
	}
	return (0);
}
