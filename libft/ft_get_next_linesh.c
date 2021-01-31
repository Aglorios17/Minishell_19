/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line3d.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:52:08 by aglorios          #+#    #+#             */
/*   Updated: 2020/03/04 12:53:38 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_free(char **rest, int nb)
{
	if (*rest == NULL)
	{
		free(*rest);
		*rest = NULL;
	}
	return (nb);
}

static char	*ft_strndup1(const char *s)
{
	int		a;
	int		len;
	char	*str;

	len = 0;
	a = 0;
	while (s[len] != '\n' && s[len] != '\0')
		len++;
	str = malloc((len + 1) * sizeof(*str));
	if (str == NULL)
		return (NULL);
	while (s[a] != '\n' && s[a] != '\0')
	{
		str[a] = s[a];
		a++;
	}
	str[a] = '\0';
	return (str);
}

static int	ft_read1(int fd, char **line, char *rest)
{
	int		ret;
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;

	ret = 1;
	if (rest != NULL)
		if ((*line = ft_strdup_gnlsh(rest)) == NULL)
			return (-1);
	if (rest == NULL)
		if ((*line = ft_strdup_gnlsh("")) == NULL)
			return (-1);
	while ((ft_strchr_gnlsh(*line, '\n') == NULL) &&
			(ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		tmp = *line;
		buf[ret] = '\0';
		if ((*line = ft_strjoin_gnlsh(*line, buf)) == NULL)
			return (-1);
		free(tmp);
	}
	return (ret);
}

int			get_next_linesh(int fd, char **line)
{
	int			ret;
	static char	*rest[FOPEN_MAX];
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	if ((ret = ft_read1(fd, line, rest[fd])) == -1)
		return (ft_free(&rest[fd], -1));
	if (rest[fd] != NULL)
		free(rest[fd]);
	if ((rest[fd] = ft_strdup_gnlsh(ft_strchr_gnlsh(*line, '\n'))) == NULL)
		return (ft_free(&rest[fd], -1));
	if (ft_strchr_gnlsh(*line, '\n') == NULL)
		return (ft_free(&rest[fd], 0));
	tmp = *line;
	if ((*line = ft_strndup1(*line)) == NULL)
		return (ft_free(&rest[fd], -1));
	free(tmp);
	return (1);
}
