#include "../../include/minishell.h"

int ft_export(shell *st, char **envp)
{
	char *tmp;
	char *tmp2;
	char *bef;
	int	a;
	int	i;
	int	b;
	int err;

	tmp = NULL;
	tmp2 = NULL;
	bef = NULL;
	a = 0;
	b = 0;
	err = 0;
	i = 0;
	(void)envp;
//	if (!st->tokens->next)
//		return (0);
	if (!st->tokens->next)
	{
		while (st->envv->next)
		{	
			tmp = ft_strdup("declare -x ");
			write(1, tmp, ft_strlen(tmp));
			tmp = ft_strdup((char *)st->envv->content);
			i = 0;
			tmp2 = ft_strdup("");
			a = 0;
			while (tmp[i])
			{
//				printf("tmp|%c|\n", tmp[i]);
				if (ft_strchr("\\\"$", tmp[i]))
					tmp2 = ft_charjoin(tmp2, '\\');
				tmp2 = ft_charjoin(tmp2, tmp[i]);
				if (tmp[i] == '=' && !a)
				{
					tmp2 = ft_charjoin(tmp2, '"');
					a = 1;
				}
				i++;
				if (tmp[i] == '\0')
					tmp2 = ft_charjoin(tmp2, '"');
			}
			tmp2 = ft_strjoin(tmp2, "\n");
			i = 0;
			write(1, tmp2, ft_strlen(tmp2));
			st->envv = st->envv->next;
		}
		st->envv = st->firstenv;
		return (0);
	}
	st->tokens = st->tokens->next;
	while (st->tokens)
	{
		err = 0;
		tmp = (char *)st->tokens->content; 
//		printf("ok\n");
	//	printf("tmp|%s|\n", tmp);
//		printf("tmp|%c|\n", tmp[i]);
//		printf("ok1\n");
		if (tmp[0] == '\0')
		{
		
			write(1, "minishell: export: `", 20);
			write(1, "': not a valid identifier\n", 26);
			st->status = 1;
			err = 1;
		}
		if (((!ft_strchr(tmp, '=') && ft_strchr(tmp, ' ')) || tmp[0] == '=') && err == 0)
		{
			write(1, "minishell: export: `", 20);
			write(1, tmp, ft_strlen(tmp));
			write(1, "': not a valid identifier\n", 26);
			st->status = 1;
			err = 1;
		}
		if (err == 0)
		{
			b = 0;
			bef = ft_strdup("");
			while (tmp[b] && tmp[b] != '=')
			{
				bef = ft_charjoin(bef, tmp[b]);
				b++;
			}
			if (ft_isdigit(bef[0]) || ft_strchr(bef, '\\') || ft_strchr(bef, '\'') || ft_strchr(bef, '"') || ft_strchr(bef, '$') || ft_strchr(bef, '|') || ft_strchr(bef, ';') || ft_strchr(bef, '&') || ft_strchr(bef, '!') ||  ft_strchr(bef, '@'))
			{
				write(1, "minishell: export: `", 20);
				write(1, tmp, ft_strlen(tmp));
				write(1, "': not a valid identifier\n", 26);
				st->status = 1;
				err = 1;
	//			return (0);
			}
		}
		if (!ft_strchr(tmp, '=') && err == 0)
			err = 1;
//			return (0);
		a = 0;
		while (tmp[a] != '=' && err == 0) ////////////////////////////////////// export lol =mdr (parser)
		{
			if (tmp[a] == ' ')
			{
				write(1, "minishell: export: `", 20);
				write(1, tmp, ft_strlen(tmp));
				write(1, "': not a valid identifier\n", 26);
				st->status = 1;
				err = 1;
			}
			a++;
		}
		if (tmp[a] == '=' && tmp[a - 1] == ' ' && err == 0)
		{
			write(1, "minishell: export: `", 20);
			write(1, tmp, ft_strlen(tmp));
			write(1, "': not a valid identifier\n", 26);
			st->status = 1;
			err = 1;
		//	return (0);
		}
		if (err == 1)
			st->tokens = st->tokens->next;
		if (err == 0)
		{
			a = 0;
			while (st->envv != NULL)
			{
				tmp2 = (char *)st->envv->content;
				i = 0;
				while (tmp2[i] != '=')
					i++;
				if (tmp2[i] == '=')
					i++;
				if (!ft_strncmp(tmp, tmp2, i))
				{
					if (!ft_strncmp(tmp, "SHLVL=", i))
					{
						a = ft_atoi(&tmp2[i]);
				//		printf("ok\n");
						st->envv->content = ft_shlvl(&tmp[i], a);	
//						printf("envv|%s|\n", (char *)st->envv->content);
					}
					else
					{
						if (!ft_strncmp(tmp, "PWD=", i))
							st->pwd = ft_strdup(&tmp[i]);		
						if (!ft_strncmp(tmp, "OLDPWD=", i))
							st->oldpwd = ft_strdup(&tmp[i]);		
						st->envv->content = ft_strdup(tmp);
					}
					a = 1;
				}
				st->envv = st->envv->next;
			}	
			st->envv = st->firstenv;
			if (a == 0)
				ft_lstadd_back(&st->envv, ft_lstnew(ft_strdup(tmp)));
			st->tokens = st->tokens->next;
		}
	}
	st->tokens = st->firsttok;
/*
	while (st->envv != NULL)
	{
		printf("envv|%s|\n", (char *)st->envv->content);
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
*/
    return (0);
}
