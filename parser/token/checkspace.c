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

int	ft_checkifsimplequote2(char *line, int i, int a)
{
	a = i + 1;
	while (line[a] && line[a] != ' ' && line[a] != '\t' &&
		line[a] != '\'' && line[a] != '\'')
		a++;
	return (a);
}

int	ft_checkifsimplequote(char *line, int i)
{
	int a;

	a = 0;
	i++;
	while (line[i] == '\'')
	{
		if (line[i + 1] && line[i + 1] != '\'')
			i++;
		while (line[i] && line[i] != '\'')
		{
			if (line[i] == ' ')
				return (i);
			i++;
		}
		i++;
	}
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


int	ft_checkifdoublequote2(char *line, int i)
{
	while (line[i] && line[i] != '"')
		i++;
	if (line[i] && line[i] == '"' && (line[i - 1] && line[i - 1] == '\\'))
		i++;
	return (i);
}

int	ft_checkifdoublequote(char *line, int i)
{
	int a;

	a = 0;
	i++;
	while (line[i] == '"')
	{
		if (line[i + 1] && line[i + 1] != '"')
			i++;
		while (line[i] && line[i] != '"')
		{
			if (line[i] == ' ')
				return (i);
			i++;
		}
		i++;
	}
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

int	ft_checkspace(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\'' &&
			line[i] != '"' && line[i] != '>' && line[i] != '<')
			i++;
		else if (line[i] && line[i] == '\'')
			i = ft_checkifsimplequote(line, i);
		else if (line[i] && line[i] == '"')
			i = ft_checkifdoublequote(line, i);
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
