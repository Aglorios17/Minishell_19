/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverhelp <marvin@42.ff>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 19:35:22 by gverhelp          #+#    #+#             */
/*   Updated: 2020/12/02 19:35:30 by gverhelp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charjoin(char const *s1, char c)
{
	int		size;
	int		a;
	char	*str;

	a = 0;
	if (s1 == NULL)
		return (NULL);
	size = ft_strlen((char*)s1);
	str = malloc((size + 2) * sizeof(*str));
	if (str == NULL)
		return (NULL);
	while (s1[a] != '\0')
	{
		str[a] = s1[a];
		a++;
	}
	str[a] = c;
	str[a + 1] = '\0';
	return (str);
}
