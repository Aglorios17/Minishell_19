/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:13:12 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 15:54:51 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_intlen(int n)
{
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char		*ft_spec(int n)
{
	char *spec;

	if (n == 0)
		spec = ft_strdup("0");
	else
		spec = ft_strdup("-2147483648");
	return (spec);
}

char			*ft_itoa(int n)
{
	char		*s;
	size_t		len;
	long int	a;

	a = n;
	if (a == -2147483648 || a == 0)
		return (ft_spec(n));
	len = ft_intlen(a) + 1;
	if (!(s = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	if (a == 0)
		return ("0");
	if (a < 0)
	{
		s[0] = '-';
		a = -a;
	}
	s[len - 1] = '\0';
	while (a)
	{
		len--;
		s[len - 1] = (a % 10) + '0';
		a /= 10;
	}
	return (s);
}
