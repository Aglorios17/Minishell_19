/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:47:57 by aglorios          #+#    #+#             */
/*   Updated: 2020/03/04 12:49:31 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnlsh(const char *s)
{
	size_t	a;

	a = 0;
	while (s[a] != '\0')
		a++;
	return (a);
}

char	*ft_strjoin_gnlsh(char const *s1, char const *s2)
{
	int		size;
	int		a;
	int		b;
	char	*str;

	a = 0;
	b = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen_gnl((char*)s1) + ft_strlen_gnl((char*)s2);
	str = malloc((size + 1) * sizeof(*str));
	if (str == NULL)
		return (NULL);
	while (s1[a] != '\0')
	{
		str[a] = s1[a];
		a++;
	}
	while (s2[b] != '\0')
	{
		str[a + b] = s2[b];
		b++;
	}
	str[a + b] = '\0';
	return (str);
}

char	*ft_strdup_gnlsh(const char *s1)
{
	int		a;
	char	*s;

	a = 0;
	if (s1 == NULL)
		return (ft_strdup_gnl(""));
	s = malloc((ft_strlen(s1) + 1) * sizeof(*s));
	if (s == NULL)
		return (NULL);
	while (s1[a] != '\0')
	{
		s[a] = s1[a];
		a++;
	}
	s[a] = '\0';
	return (s);
}

char	*ft_strchr_gnlsh(const char *s, int c)
{
	int	a;

	a = 0;
	while (s[a] != '\0')
	{
		if (s[a] == (unsigned char)c)
			return ((char*)&s[a + 1]);
		a++;
	}
	if (c == 0)
		return ((char*)&s[a]);
	return (NULL);
}
