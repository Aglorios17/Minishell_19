/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:51:06 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/18 17:27:16 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;

	i = ft_strlen(s) + 1;
	if (s == 0)
		return (0);
	while (--i)
	{
		if (s[i] == (char)c)
			return ((char*)s + i);
	}
	if (s[i] == (char)c)
		return ((char*)s + i);
	return (NULL);
}
