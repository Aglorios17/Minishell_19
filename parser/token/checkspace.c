/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_checkifsimplequote(char *line, int i, t_sekot *sekot)
{
	int a;

	a = 0;
	sekot->flagcs = 0;
	i++;
	a = ft_checkifsimplequote3(line, i, sekot);
	if (sekot->flagcs == 1)
		return (a);
	else
		i = a;
	while (line[i] && line[i] != '\'')
		i++;
	if (line[i] && line[i + 1] && (line[i + 1] &&
		(line[i + 1] == ' ' || line[i + 1] == '\0')))
		return (i + 1);
	if (line[i] && line[i + 1])
	{
		a = ft_checkifsimplequote2(line, i, a);
		if (line[a] == ' ' || line[a] == '\t')
			return (a);
	}
	return (i);
}

int	ft_checkifdoublequote3(char *line, int i, t_sekot *sekot)
{
	while (line[i] == '"')
	{
		if (line[i + 1] && line[i + 1] != '"')
			i++;
		while (line[i] && line[i] != '"')
		{
			if (line[i] == ' ')
			{
				sekot->flagcs = 1;
				return (i);
			}
			i++;
		}
		i++;
	}
	return (i);
}

int	ft_checkifdoublequote2(char *line, int i)
{
	while (line[i] && line[i] != '"')
		i++;
	if (line[i] && line[i] == '"' && (line[i - 1] && line[i - 1] == '\\'))
		i++;
	return (i);
}

int	ft_checkifdoublequote(char *line, int i, t_sekot *sekot)
{
	int a;

	a = 0;
	sekot->flagcs = 0;
	i++;
	a = ft_checkifdoublequote3(line, i, sekot);
	if (sekot->flagcs == 1)
		return (a);
	else
		i = a;
	i = ft_checkifdoublequote2(line, i);
	if (line[i] && line[i + 1])
	{
		a = i + 1;
		if (line[a - 1] && line[a] == '"' && line[a - 1] != '"')
			return (a + 1);
		while (line[a] && line[a] != ' ' && line[a] != '\t' &&
			line[a] != '"' && line[a] != '\'')
			a++;
		if (line[a] && (line[a] == ' ' || line[a] == '\t'))
			return (a);
	}
	return (i);
}

int	ft_checkspace(char *line, t_sekot *sekot)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\'' &&
			line[i] != '"' && line[i] != '>' && line[i] != '<')
			i++;
		else if (line[i] && line[i] == '\'')
			i = ft_checkifsimplequote(line, i, sekot);
		else if (line[i] && line[i] == '"')
			i = ft_checkifdoublequote(line, i, sekot);
		else if (line[i] && (line[i] == '>' || line[i] == '<'))
			return (i);
		else if (line[i] && (line[i] == ' ' || line[i] == '\t'))
		{
			if (line[i - 1] == '\\')
				i++;
			else
				return (i);
		}
	}
	return (i);
}
