/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:30:28 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 17:31:30 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	j;
	char			*mapi;

	i = 0;
	j = 0;
	if (s == NULL || f == NULL)
		return (ft_protect());
	while (s[i] != '\0')
		i++;
	if ((mapi = malloc(sizeof(char) * (i + 1))) != NULL)
	{
		while (j < i)
		{
			mapi[j] = f(j, s[j]);
			j++;
		}
		mapi[i] = '\0';
		return (mapi);
	}
	return (NULL);
}
