/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:26:39 by aglorios          #+#    #+#             */
/*   Updated: 2020/01/09 09:41:15 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *p;

	if (nmemb == 0 && size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	p = malloc(nmemb * size);
	if (p == 0)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return (p);
}
