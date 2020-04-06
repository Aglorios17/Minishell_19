/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:31:46 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/16 17:22:29 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		a;
	char	*malabar;

	a = 0;
	malabar = malloc(sizeof(*malabar) * (ft_strlen(src) + 1));
	if (src == 0)
		return (0);
	if (malabar != NULL)
	{
		while (src[a] != '\0')
		{
			malabar[a] = src[a];
			a++;
		}
		malabar[a] = '\0';
		return (malabar);
	}
	return (NULL);
}
