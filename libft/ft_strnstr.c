/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:10:36 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 19:13:07 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	a;
	size_t	b;
	char	*s;
	char	*t;

	a = 0;
	b = 0;
	s = (char*)str;
	t = (char*)to_find;
	if (t[a] == '\0')
		return (s);
	while (s[a] != '\0' && a < n)
	{
		b = 0;
		while (s[a + b] == t[b] && (a + b) < n)
		{
			b++;
			if (t[b] == '\0')
				return (&s[a]);
		}
		a++;
	}
	return (0);
}
