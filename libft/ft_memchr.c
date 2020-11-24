/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:03:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/21 12:52:57 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t	a;
	char	*s;

	s = (char *)str;
	a = 0;
	while (n != 0 && a < n)
	{
		if (s[a] == c)
			return (&s[a]);
		a++;
	}
	return (0);
}
