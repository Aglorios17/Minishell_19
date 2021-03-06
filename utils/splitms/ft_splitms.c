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

char	*ft_write2(const char *str, char c, char **tabs)
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
		ft_freetab(tabs);
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

void	ft_write_norme(const char *str, int d, int a, char **tabs)
{
	char	*fri;

	fri = NULL;
	tabs[d] = NULL;
	if (str[a] == ';')
		fri = ft_strdup("minishell: syntax error near unexpected token `;\'\n");
	write(1, fri, ft_strlen(fri));
	free(fri);
	ft_freetab(tabs);
}

char	**ft_write(const char *str, char c, char **tabs, t_shell *st)
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
			ft_write_norme(str, d, a, tabs);
			st->status = 2;
			return (tabs);
		}
		if (str[a] && str[a] != c)
			tabs[d++] = ft_write2(&str[a], c, tabs);
		a = ft_write_norme2(str, c, a);
		if (!str[a])
			break ;
		a++;
	}
	tabs[d] = NULL;
	return (tabs);
}

char	**ft_splitms(char const *s, char c, t_shell *st)
{
	char	**tabs;

	if (s == NULL)
		return (NULL);
	if (!(tabs = malloc((ft_malloc_tab(s, c) + 1) * sizeof(char*))))
		return (NULL);
	return (ft_write(s, c, tabs, st));
}
