/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:37:10 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/21 14:37:52 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char				*d;
	const char			*s;
	unsigned long int	i;

	d = (char*)dest;
	s = (char*)src;
	i = 0;
	if ((src == NULL && dest == NULL) || src == dest)
		return (NULL);
	while (i < n)
	{
		*d++ = *s++;
		i++;
	}
	return (dest);
}
