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


int	ft_dollars(shell *st, char *tmp, int i)
{
	char	*new;
	char	*space;
	int 	a;
	int		b;
	int		c;
	char	*tmp2;
	char	*trad; //////////////////////// changer trad char * (nouv)/ char **
	char	*first;
	char	*val;

	new = ft_strdup("");
	st->pass = 0;
	trad = NULL;
	space = NULL;
	first = NULL;
	val = NULL;
	(void)tmp2;
	(void)trad;
	(void)first;
	a = 0;
	b = 0;
	c = 0;
	(void)b;
	(void)val;
	tmp2 = tmp;
//	printf("tmp2 : |%s|\n", tmp2);
	val = ft_strdup(&tmp[i - 1]);
	if (tmp[i + 1] == '\0' || tmp[i + 1] == '\\')
	{
		st->tmpq = ft_charjoin(st->tmpq, '$');
		st->pass = i;
		return (0);
	}
	i++;
//	printf("tmp|%c|\n", tmp[1]);
	while (tmp[i] && !ft_strchr("\'\"", tmp[i]) && tmp[i] != '\0')
	{
//		printf("tmp[1] : |%c|\n", tmp[1]);
//		printf("tmp[i] : |%c|\n", tmp[i]);
		if (!ft_isalnum(tmp[i]) && tmp[i] != '_' && tmp[i] != '?')
		{
//			printf("OK\n");
			break;
		}
		if (tmp[i] == '$' || tmp[i] == '\\') /////////////////////////////////////////////////////////// 
		{
			if (tmp[i] == '\\' && !tmp[i + 1])
				space = ft_strdup(" ");
			break;
		}
		new = ft_charjoin(new, tmp[i]);
//		printf("join|%s|\n", new);
		i++;
	}
//	printf("new|%s|\n", new);
	st->pass = i - 1;
	new = ft_charjoin(new, '=');
//	printf("new|%s|\n", new);
	tmp = NULL;
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
//		printf("tmp|%s|\n", tmp);
		if ((!ft_strncmp(new, tmp, ft_strlen(new))) || !ft_strncmp(new, "?=", 2))
		{
			i = 0;
//			printf("ok\n");
			while (tmp[i] && tmp[i] != '=')
				i++;
			if (tmp[i] == '=')
				i++;
//			tmp = ft_pass_space(tmp, i);
			if (!ft_strncmp(tmp, "SHLVL=", i))
			{
//				printf("ok\n");
				a = ft_atoi(&tmp[i]);
				st->tmpq = ft_strdup(&ft_shlvl(&tmp[i], a)[6]);	
//				printf("envv|%s|\n", (char *)st->envv->content);
			}///* //////////////////////////////////////////////////////////////////////////////////// debut nouv
			else if (!ft_strncmp(new, "?=", i))
			{
				st->tmpq = ft_itoa(st->status);	
//				printf("envv|%s|\n", (char *)st->envv->content);
			}///* //////////////////////////////////////////////////////////////////////////////////// debut nouv
			else
			{
//				printf("ok\n");
				(void)tmp2;
				(void)first;
//				printf("&tmp[i] : |%s|\n", &tmp[i]);
//				printf("tmp2 : |%s|\n", tmp2);
//				printf("flag : |%i|\n", st->flagdq);
				first = ft_substr(tmp2, st->pass + 1, ft_strlen(tmp2));
				trad = ft_strdup(&tmp[i]);
//				printf("first : |%s|\n", first);
//				printf("tmp : |%s|\n", tmp);
//				printf("trad1 : |%s|\n", trad);
//				printf("val : |%s|\n", val);
				a = 0;
				b = 0;
				while (trad[a] && trad[a] == ' ')
					a++; 
				if (trad[a] != '\0' && st->flagdq == 1)
					c = 1;
//				printf("trad[a] : |%c|\n", trad[a]);
				else if (trad[a] != '\0')
				{
//					if (!ft_strncmp(trad, "echo", 5) || !ft_strncmp(trad, "cd", 3) ||
//						!ft_strncmp(trad, "pwd", 4) ||
//						!ft_strncmp(trad, "env", 4) || !ft_strncmp(trad, "export", 7) ||
//						!ft_strncmp(trad, "unset", 6) || !ft_strncmp(trad, "exit", 5))
//					{
//						printf("ok\n");
//					//	st->envv = st->firstenv;
					//	return (ft_strlen(st->tmpq));
//					}
					if (trad[a] != '\0')
					{
						tmp = ft_strdup("");
						while (trad[a])
						{
//							printf("trad[a]bcl : |%c|\n", trad[a]);
							if (trad[a] == ' ' && (trad[a + 1] == ' ' || trad[a + 1] == '\0'))
								a++;
							else
							{
								tmp = ft_charjoin(tmp, trad[a]);
								a++;
							}
						}
						i = 0;
					}
				}
				else if (trad[a] == '\0')
				{
//					printf("trad[a] : |%c|\n", trad[a]);
					if (st->flagdq == 1)
					{
//						printf("trad2 : |%s|\n", trad);
						tmp = ft_strdup(trad);
					}
					else if (st->flagdq == 0 && tmp2[0] != '$' && first[0])
						tmp = ft_strdup(" ");
					else
						tmp = ft_strdup("");
					i = 0;
					b = 1;
				}
//				printf("tmp2[0] : |%c|\n", tmp2[0]);
//				printf("first[0] : |%c|\n", first[0]);
//				printf("tmpfin trad : |%s|\n", tmp);
				while (tmp[i])
				{
					st->tmpq = ft_charjoin(st->tmpq, tmp[i]);
					i++;
				}
//				printf("firstd : |%i|\n", st->firstd);
			//	if (trad[0] == ' ' && st->firstd > 2)
			//		st->tmpq = ft_strjoin(" ", st->tmpq);
				if (trad[ft_strlen(trad) - 1] == ' ' && (first[0] && first[0] != '$') && b == 0 && c== 0)
					st->tmpq = ft_charjoin(st->tmpq, ' ');
				if (trad[0] == ' ' && val[0] && b == 0 && c == 0)
					st->tmpq = ft_strjoin(" ", st->tmpq);
	//			printf("tmpqfin : |%s|\n", st->tmpq);
			}
//			printf("st->tmpq|%s|\n", st->tmpq);
			if (space)
				st->tmpq = ft_charjoin(st->tmpq, ' ');
			st->envv = st->firstenv;
			return (ft_strlen(st->tmpq));
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	if (!ft_strncmp("$OLDPWD", tmp2, 7))
	{
//		printf("okok\n");
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strjoin("OLDPWD=", "")));
	}
	st->envv = st->firstenv;
	return (ft_strlen(new));
}
