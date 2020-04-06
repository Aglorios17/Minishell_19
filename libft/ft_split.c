/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:14:34 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 17:28:35 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_words_count(char const *str, char c)
{
	int	i;
	int wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			wc++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (wc);
}

static char			*ft_add_word(char const *str, char c)
{
	int		i;
	char	*lstr;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	lstr = malloc(sizeof(char *) * i);
	if (lstr == NULL)
		return (0);
	i = 0;
	while (str[i] && str[i] != c)
	{
		lstr[i] = str[i];
		i++;
	}
	lstr[i] = '\0';
	return (lstr);
}

static char			**ft_free(int j, char **split)
{
	while (j != 0)
		free(split[j--]);
	free(split);
	return (NULL);
}

char				**ft_split(char const *str, char c)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	j = 0;
	if (str == 0)
		return (NULL);
	if ((split = malloc(sizeof(char *) * (ft_words_count(str, c) + 1))) == NULL)
		return (0);
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			split[j++] = ft_add_word(&str[i], c);
			if (ft_add_word(&str[i], c) == 0)
				return (ft_free(--j, split));
			while (str[i] && str[i] != c)
				i++;
		}
	}
	split[j] = 0;
	return (split);
}
