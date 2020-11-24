/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:43:15 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 15:44:53 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check(char c, char const *set)
{
	int	a;

	a = 0;
	while (set[a] != '\0')
	{
		if (set[a] == c)
		{
			return (1);
		}
		a++;
	}
	return (0);
}

static int		trimdebut(char const *s1, char const *set)
{
	int	a;
	int	suppdebut;

	a = 0;
	suppdebut = 0;
	while (s1[a] != '\0')
	{
		if (check(s1[a], set) == 1)
		{
			suppdebut++;
			a++;
		}
		else
			return (suppdebut);
	}
	return (suppdebut);
}

static int		trimfin(char const *s1, char const *set)
{
	int	a;
	int	b;
	int suppfin;

	b = 0;
	while (s1[b] != '\0')
		b++;
	a = b - 1;
	suppfin = 0;
	while (a > 0)
	{
		if (check(s1[a], set) == 1)
		{
			suppfin++;
			a--;
		}
		else
			return (suppfin);
	}
	return (suppfin);
}

static char		*sizeneg(void)
{
	char	*str;

	str = malloc((1) * sizeof(*str));
	if (str == NULL)
		return (0);
	str[0] = '\0';
	return (str);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		a;
	int		b;
	int		debut;
	int		size;
	char	*str;

	a = 0;
	b = 0;
	if (s1 == NULL || set == NULL)
		return (ft_vide());
	debut = trimdebut(s1, set);
	b = ft_strlen(s1);
	size = b - debut - trimfin(s1, set);
	if (size < 0)
		return (sizeneg());
	if (!(str = malloc((size + 1) * sizeof(*str))))
		return (0);
	while (size-- > 0)
	{
		str[a] = s1[debut];
		a++;
		debut++;
	}
	str[a] = '\0';
	return (str);
}
