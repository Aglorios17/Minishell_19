/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:06:59 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/30 13:15:17 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*sub;

	i = 0;
	if (s == 0)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	else if (start + len > ft_strlen(s))
		len = ft_strlen(s) + start;
	if ((sub = malloc(sizeof(char) * (len + 1))) != 0)
	{
		while (i < len)
		{
			sub[i] = s[start];
			i++;
			start++;
		}
		sub[i] = '\0';
		return (sub);
	}
	return (NULL);
}
