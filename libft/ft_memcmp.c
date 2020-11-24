/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:00:56 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/21 12:54:33 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			a;
	unsigned char	*chaine1;
	unsigned char	*chaine2;

	a = 0;
	chaine1 = (unsigned char*)s1;
	chaine2 = (unsigned char*)s2;
	while (n != 0 && chaine1[a] == chaine2[a])
	{
		a++;
		n--;
	}
	if (n == 0)
		return (0);
	return (chaine1[a] - chaine2[a]);
}
