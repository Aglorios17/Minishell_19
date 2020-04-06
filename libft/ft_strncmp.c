/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 12:28:50 by aglorios          #+#    #+#             */
/*   Updated: 2019/11/27 16:28:21 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;

	a = 0;
	while (s1[a] != '\0' && n > a &&
			(unsigned char)s1[a] == (unsigned char)s2[a])
		a++;
	if (n == a)
		return (0);
	return ((unsigned char)s1[a] - (unsigned char)s2[a]);
}
