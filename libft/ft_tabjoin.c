/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverhelp <marvin@42.ff>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 19:35:22 by gverhelp          #+#    #+#             */
/*   Updated: 2020/12/02 19:35:30 by gverhelp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_counttab(char **tab, char **tab2)
{
	int a;
	int len;

	a = 0;
	len = 0;
	while (tab[a])
		a++;
	len += a;
	a = 0;
	while (tab2[a])
		a++;
	len += a;
	return (len);
}

char	**ft_tabjoin(char **tab, char **tab2)
{
	int		a;
	int		len;
	char	**total;

	a = 0;
	len = ft_counttab(tab, tab2);
	total = malloc((len + 1) * sizeof(char *));
	len = 0;
	while (tab[a])
	{
		total[len] = ft_strdup(tab[a]);
		a++;
		len++;
	}
	a = 0;
	while (tab2[a])
	{
		total[len] = ft_strdup(tab2[a]);
		a++;
		len++;
	}
	total[len] = NULL;
	return (total);
}
