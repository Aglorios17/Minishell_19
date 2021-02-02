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

char	*ft_write2(const char *str, char c, char **tab)
{
	int		a;
	char	*dest;

	a = 0;
	while (str[a] && str[a] != c)
	{
		if (str[a] && (str[a] == '"' || str[a] == '\''))
		{
			a++;
			while (str[a] && str[a] != '"' && str[a] != '\'')
				a++;
		}
		if (str[a])
		{
			a++;
			if (str[a] && str[a] == c && str[a - 1] == '\\')
				a++;
		}
	}
	dest = ft_substr(str, 0, a);
	if (dest == NULL)
		ft_freetab(tab);
	return (dest);
}

int		ft_write_norme2(const char *str, char c, int a)
{
	while (str[a] && str[a] != c)
	{
		if (str[a] && (str[a] == '"' || str[a] == '\''))
		{
			a++;
			while (str[a] && str[a] != '"' && str[a] != '\'')
				a++;
		}
		if (str[a])
		{
			a++;
			if (str[a] && str[a] == c && str[a - 1] == '\\')
				a++;
		}
	}
	return (a);
}

void	ft_write_norme(const char *str, int d, int a, char **tab)
{
	char	*fri;

	fri = NULL;
	tab[d] = NULL;
	if (str[a] == ';')
		fri = ft_strdup("minishell: syntax error near unexpected token `;\'\n");
	write(1, fri, ft_strlen(fri));
	free(fri);
	ft_freetab(tab);
}

char	**ft_write(const char *str, char c, char **tab, t_shell *st)
{
	int		a;
	int		d;

	a = 0;
	d = 0;
	while (str[a])
	{
		while (str[a] && str[a] == ' ')
			a++;
		if (str[a] && str[a] == ';')
		{
			ft_write_norme(str, d, a, tab);
			st->status = 2;
			return (tab);
		}
		if (str[a] && str[a] != c)
			tab[d++] = ft_write2(&str[a], c, tab);
		a = ft_write_norme2(str, c, a);
		if (!str[a])
			break ;
		a++;
	}
	tab[d] = NULL;
	return (tab);
}

char	**ft_splitms(char const *s, char c, t_shell *st)
{
	char	**tab;

	if (s == NULL)
		return (NULL);
	if (!(tab = malloc((ft_malloc_tab(s, c) + 1) * sizeof(char*))))
		return (NULL);
	return (ft_write(s, c, tab, st));
}
