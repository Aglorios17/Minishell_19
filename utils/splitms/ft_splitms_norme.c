/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverhelp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_malloc_tab2(char const *str, char c, int a)
{
	if (str[a] && (str[a] == '"' || str[a] == '\''))
	{
		a++;
		while (str[a] && str[a] != '"' && str[a] != '\'')
			a++;
	}
	a++;
	if (str[a] && str[a] == c && str[a - 1] == '\\')
		a++;
	return (a);
}

int	ft_malloc_tab(char const *str, char c)
{
	int	a;
	int	counter;

	a = 0;
	counter = 0;
	while (str[a])
	{
		while (str[a] && str[a] == ' ')
			a++;
		if (str[a] && str[a] != c)
			counter++;
		while (str[a] && str[a] != c)
			a = ft_malloc_tab2(str, c, a);
		if (!str[a])
			break ;
		a++;
	}
	return (counter);
}
