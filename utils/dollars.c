#include "../include/minishell.h"

int	ft_cmddollars(shell *st, char *tmp)
{
	if (check_path(st, tmp) == 1)
		return (1);
	if (!ft_strcmp(tmp, "echo") || !ft_strcmp(tmp, "cd") || !ft_strcmp(tmp, "pwd") ||
		!ft_strcmp(tmp, "env") || !ft_strcmp(tmp, "export") ||
		!ft_strcmp(tmp, "unset") || !ft_strcmp(tmp, "exit") || !ft_strcmp(tmp, "exec"))
	{
		return (1);
	}
	else
		return (0);
}

int	ft_retokens(shell *st, char *env, char *first, char *after)
{
	int 	a;
	int		b;
	int		c;
	char	**trad;
	char	*backs;
	t_list	*bef;

	a = 0;
	b = 0;
	c = 0;
	bef = NULL;
	trad = NULL;
	backs = ft_strdup("");
	(void)after;
//	printf("env|%s|\n", env);
//	printf("first|%s|\n", first);
//	printf("after|%s|\n", after);
	while (after[b] && ft_strchr(after, '\\'))
	{
		if (after[b] == '\\' && (after[b + 1] == ' ' || after[b + 1] == '\0'))
		{
			backs = ft_charjoin(backs, ' ');
			b += 2;
		}
		else
		{	
			if (after[b] == '\\' && after[b + 1] == '\\')
				b++;
			backs = ft_charjoin(backs, after[b]);
			b++;
		}
	}
	if (b != 0 && after[2] != '\0')
		c = 1;
	b = 0;
	st->ddone = 0;
	while (env[a] && env[a] != '=')
		a++;
	if (st->flagdq == 0 && env[a])
	{
		trad = ft_split(&env[a + 1], ' ');
//		while (trad[b])
//		{
//			printf("trad|%s|\n", trad[b]);
//			b++;
//		}
//		b = 0;
	}
	else if (st->flagdq == 1)
	{
		st->tokens->content = ft_strdup(&env[a + 1]);
//		if (first[0] != '\0' && after[0] != '\0')
//		{
//			if (first[0] != '\0')
//				st->tokens->content = ft_strjoin(first, (char *)st->tokens->content);
//			if (after[0] != '\0')
//				st->tokens->content = ft_strjoin((char *)st->tokens->content, after);
//		}
		st->tmpq = ft_strdup((char *)st->tokens->content);
		return (1);
	}
	if (trad[0] == NULL)
	{
		if (first[0] != '\0')
		{
			if (env[a + 1] == ' ' && after[0] != '\0')
				st->tokens->content = ft_strjoin(first, " ");
			else
				st->tokens->content = ft_strdup(first);
			st->tmpq = ft_strdup((char *)st->tokens->content);
		}
		return (1);
	}
//	printf("trad[0]|%s|\n", trad[0]);
	if (!st->tokens->next)
	{
		if (first[0] == '\0' && after[0] == '\0' &&
			env[a + 1] != ' ' && env[ft_strlen(env) - 1] != ' ')
		{
			st->tokens->content = ft_strdup(trad[0]);
			a = 1;
		}
		else if (env[a + 1] != ' ' && env[ft_strlen(env) - 1] != ' ')
		{
			if (first[0] != '\0')
			{
				st->tokens->content = ft_strjoin(first, trad[0]);
				a = 1;
			}
			if (after[0] != '\0')
			{
				if (trad[1] == NULL)
				{
					if (first[0] != '\0')
						st->tokens->content = ft_strjoin(first, trad[0]);
					else
						st->tokens->content = ft_strdup(trad[0]);
//					st->tokens->content = ft_strdup((char *)st->tokens->content);
//					st->tokens->content = ft_strjoin((char *)st->tokens->content, after);
				}
				else
				{
				//	printf("trad[0]|%s|\n", trad[0]);
					if (first[0] == '\0')
						st->tokens->content = ft_strdup(trad[0]);
					else if (first[0] != '\0')
						st->tokens->content = ft_strjoin(first, trad[0]);
					if (after[0] != '\0')
					{
						a = 1;
						b = 0;
						while (trad[b])
							b++;
						(void)c;
						if (after[0] == '\\')////////////////////////// mouais
						{
							if (c == 1)
								trad[b - 1] = ft_strjoin(trad[b - 1], backs);
							else
								trad[b - 1] = ft_strjoin(trad[b - 1], " ");
						}
						else
							trad[b - 1] = ft_strjoin(trad[b - 1], after);
						st->pass += ft_strlen(after);
					}
				}
			}
		}
		else if (first[0] == '\0' && after[0] == '\0' &&
			env[a + 1] == ' ' && env[ft_strlen(env) - 1] == ' ')
		{
			st->tokens->content = ft_strdup(trad[0]);
			a = 1;
		}
		else if (env[a + 1] == ' ')
		{
		//	printf("first|%s|\n", first);
			if (first[0] != '\0')
			{
				st->tokens->content = ft_strdup(first);
				a = 0;
				if (after[0] != '\0' && env[ft_strlen(env) - 1] != ' ')
				{
					b = 0;
					while (trad[b])
						b++;
					trad[b - 1] = ft_strjoin(trad[b - 1], after);
			//		st->pass += ft_strlen(after);
				}
			}
			else
			{
				st->tokens->content = ft_strdup(trad[0]);
				a = 1;
			}
			st->ret = 1;
		}
		else if (env[a + 1] != ' ' && env[ft_strlen(env) - 1] == ' ')
		{
			if (first[0] != '\0')
			{
				st->tokens->content = ft_strjoin(first, trad[0]);
				a = 1;
			}
			if (after[0] != '\0' && trad[1] == NULL)
			{
				if (first[0] == '\0')
					st->tokens->content = ft_strdup(trad[0]);
				a = 1;
				b = 0;
				while (trad[b])
					b++;
				trad[b - 1] = ft_strjoin(trad[b - 1], after);
				st->pass += ft_strlen(after);
			}
		}
		st->tmpq = ft_strdup((char *)st->tokens->content);
//		printf("st->tmpqin|%s|\n", st->tmpq);
		b = 0;
		while (trad[b])
			b++;
		while (a < b && trad[a])
		{
		//	printf("ok\n");
			ft_lstadd_back(&st->tokens, ft_lstnew(trad[a]));
			st->ddone += 1;
			a++;
		}
		if (env[ft_strlen(env) - 1] == ' ' && after[0] != '\0')
		{
			ft_lstadd_back(&st->tokens, ft_lstnew(after));
		}
		///////////////// debug
/*
		printf("st->tmpq|%s|\n", st->tmpq);
		printf("toko|%s|\n", (char *)st->tokens->content);
		st->tokens = st->firsttok;
		while (st->tokens)
		{
			printf("st->tokens|%s|\n", (char *)st->tokens->content);
			st->tokens = st->tokens->next;
		}
		exit(1);
*/
		////////////////
	}
	else if (st->tokens->next)
	{
		if (st->tokens == st->firsttok)
		{
			if (env[a + 1] != ' ')
			{
				if (first[0] != '\0')
					st->tokens->content = ft_strjoin(first, trad[0]);
				else
					st->tokens->content = ft_strdup(trad[0]);
			}
			if (env[a + 1] == ' ')
			{		
				st->tokens->content = first;
				a = 0;
			}
			else
				a = 1;
			st->tmpq = ft_strdup((char *)st->tokens->content);
			st->tokens = lst_addin(&trad[a], st->tokens, 1);	
			st->firsttok = st->tokens;
		}
		else
		{
//			printf("st->tokens|%s|\n", (char *)st->tokens->content);
//			printf("trad[0]|%s|\n", trad[0]);
			bef = st->tokens;
			st->tokens = st->firsttok;
			b = 0;
			while (st->tokens != bef)
			{
				b++;
				st->tokens = st->tokens->next;
			}
			st->tokens = st->firsttok;					
			st->tokens = lst_addin(&trad[0], st->tokens, b);	
			st->firsttok = st->tokens;
			while (b)
			{
				st->tokens = st->tokens->next;
				b--;
			}
			st->tmpq = ft_strdup((char *)st->tokens->content);
		}
		///////////////// debug
/*
		printf("st->tmpq|%s|\n", st->tmpq);
		st->tokens = st->firsttok;
		while (st->tokens)
		{
			printf("st->tokens|%s|\n", (char *)st->tokens->content);
			st->tokens = st->tokens->next;
		}
		exit(1);
*/
		////////////////
	}
	return (1);
}

int	ft_dollars(shell *st, char *tmp, int i)
{
	char	*new;
	char	*space;
	char	*tmp2;
	char	*env;
	char	*first;
	char	*after;
	int		a;

	new = ft_strdup("");
	first = ft_strdup("");
	after = NULL;
	st->pass = 0;
	space = NULL;
	env = NULL;
	a = 0;
	(void)tmp2;
	(void)space;
	tmp2 = tmp;
//	printf("tmp[i]|%c|\n", tmp[i]);
	a = 0;
	while (a < i)
	{
		first = ft_charjoin(first, tmp[a]);
		a++;
	}
//	printf("first|%s|\n", first);
	if (tmp[i + 1] == '\0' || tmp[i + 1] == '\\')
	{
//		a = 0;
//		while (a < i)
//		{
//			first = ft_charjoin(first, tmp[a]);
//			a++;
//		}
		if (first[0] != '\0')
		{
			st->tmpq = ft_strjoin(first, "$");
//			printf("st->tmpq|%s|\n", st->tmpq);
		}
		else
			st->tmpq = ft_charjoin(st->tmpq, '$');
		st->pass = i;
		return (0);
	}
	i++;
	while (tmp[i] && !ft_strchr("\'\"", tmp[i]) && tmp[i] != '\0')
	{
		if (!ft_isalnum(tmp[i]) && tmp[i] != '_' && tmp[i] != '?')
			break;
		if (tmp[i] == '$' || tmp[i] == '\\')
		{
			if (tmp[i] == '\\' && !tmp[i + 1])
				space = ft_strdup(" ");
			break;
		}
		new = ft_charjoin(new, tmp[i]);
		i++;
	}

	after = ft_strdup(&tmp[i]);
//	if (after[0] != '\0')
//		st->pass = i + ft_strlen(after) - 1;
//	else
	st->pass = i - 1;
	new = ft_charjoin(new, '=');
//	printf("new|%s|\n", new);
	while (st->envv)
	{
		env = ft_strdup((char *)st->envv->content);
//		printf("env|%s|\n", env);
		if (!ft_strncmp(new, env, ft_strlen(new)))
			break;
		st->envv = st->envv->next;
		free(env);
		env = NULL;
	}
	st->envv = st->firstenv;
//	printf("env|%s|\n", env);
	if (!ft_strncmp(new, "SHLVL=", ft_strlen(new)))
	{
		a = ft_atoi(&tmp[i]);
		st->tmpq = ft_strdup(&ft_shlvl(&env[i], a)[6]);	
	}
	else if (!ft_strncmp(new, "?=", ft_strlen(new)))
		st->tmpq = ft_itoa(st->status);	
	else if (env == NULL && !ft_strncmp("$OLDPWD", tmp2, 7))
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strjoin("OLDPWD=", "")));
	else
	{
//		printf("|ok|\n");
		if (env == NULL)
			env = ft_strdup("=");
//		printf("|ok|\n");
//		printf("env|%s|\n", env);
		ft_retokens(st, env, first, after);
//		printf("|ok|\n");
//		printf("st->tmpq|%s|\n", st->tmpq);
	}
	return (1);
}
