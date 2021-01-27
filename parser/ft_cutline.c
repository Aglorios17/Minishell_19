#include "../include/minishell.h"

static int      ft_verif_syntax(shell *st)
{
    int a;
	int flagspace;
	char c;

    a = 0;
	c = 0;
	flagspace = 0;
	(void)c;
	while (st->line[a] == ' ')
		a++;
	if (st->line[a] && (st->line[a] == '<' || st->line[a] == '>'))
	{
		if (st->line[a] == '>')
		{
			if (st->line[a + 1] != '>')
				a++;
			else if (st->line[a + 1] == '>')
				a += 2;
		}
		if (st->line[a] == '<')
		{
			if (st->line[a + 1] == '<' && st->line[a + 2] == '<')
				a += 3;
			else if (st->line[a + 1] == '<')
				a += 2;
			else if (st->line[a + 1] != '<')
				a++;
		}
		while (st->line[a] && st->line[a] == ' ')
			a++;
		if (st->line[a] == ';' || st->line[a] == '|')
		{
			write(2, "minishell: syntax error near unexpected token `", 47);
			if (st->line[a] == ';')
				write(2, ";\'\n", 3);
			if (st->line[a] == '|')
				write(2, "|\'\n", 3);
			st->status = 2;
            return (1);
		}
	}
	if (st->line[a] && (st->line[a] == ';' || st->line[a] == '|'))
	{
		    write(2, "minishell: syntax error near unexpected token `", 47);
            if (st->line[a] == ';' && st->line[a + 1] == ';')
				write(2, ";;\'\n", 4);
			else if (st->line[a] == '|' && st->line[a + 1] == '|')
				write(2, "||\'\n", 4);
            else if (st->line[a] == ';')
				write(2, ";\'\n", 3);
			else if (st->line[a] == '|')
				write(2, "|\'\n", 3);
			st->status = 2;
            return (1);
	}
	a = 0;
    while (st->line[a])
    {
		if (st->line[a] == '"' || st->line[a] == '\'')
		{
			a++;
			while (st->line[a] && (st->line[a] != '"' || st->line[a] != '\''))
				a++;
		}
		if (st->line[a] == ';' || st->line[a] == '|')
		{
			if (st->line[a - 1] == '\\')
				a++;
		}
		if (st->line[a] == ';')
		{
			a++;
			if (st->line[a] == ';')
			{
				write(2, "minishell: syntax error near unexpected token `", 47);
				write(2, ";;\'\n", 4);
				st->status = 2;
				return (1);
			}
			while (st->line[a] == ' ')
				a++;
			if (st->line[a] == '|')
			{
				write(2, "minishell: syntax error near unexpected token `", 47);
				write(2, "|\'\n", 3);
				st->status = 2;
				return (1);
			}
			if (st->line[a] == ';')
			{
				write(2, "minishell: syntax error near unexpected token `", 47);
				write(2, ";\'\n", 3);
				st->status = 2;
				return (1);
			}
		}
		if (st->line[a] == '|')
		{
			a++;
			while(st->line[a] == ' ')
			{
				flagspace = 1;
				a++;
			}
			if (!st->line[a])
			{
				write(2, "minishell: syntax error near unexpected token `", 47);
				write(2, "|\'\n", 3);
				st->status = 2;
				return (1);
			}
			if (st->line[a] == ';')
			{
				write(2, "minishell: syntax error near unexpected token `", 47);
				write(2, ";\'\n", 3);
				st->status = 2;
				return (1);
			}
			if (st->line[a] == '|' && flagspace == 1)
			{
				write(2, "minishell: syntax error near unexpected token `", 47);
				write(2, "|\'\n", 3);
				st->status = 2;
				return (1);
			} 
			if (st->line[a] == '|' && flagspace == 0)
			{
				if (st->line[a + 1] == '|' && st->line[a + 2] == '|')
				{
					write(2, "minishell: syntax error near unexpected token `", 47);
					write(2, "||\'\n", 4);
					st->status = 2;
					return (1);
				}
				if (st->line[a + 1] == '|')
				{
					write(2, "minishell: syntax error near unexpected token `", 47);
					write(2, "|\'\n", 3);
					st->status = 2;
					return (1);
				}
			}
		}
        a++;
    }
    return (0);
}

int	ft_cutpipe(shell *st)
{
	int a;
	char **line;
	a = 0;
	line = ft_splitms((char *)st->cutline->content, '|', st);
	while (line[a])
	{
		ft_lstadd_back(&st->pipe, ft_lstnew(ft_strdup(line[a])));
		a++;
	}
	st->firstpipe = st->pipe;
    return (0);
}

int	ft_cutline(shell *st)
{
	int a;
	char **line;

	a = 0;
	if (ft_verif_syntax(st) == 1)
		return (1);
	if ((line = ft_splitms(st->line, ';', st)) == NULL)
		return (1);
	while (line[a])
	{
		ft_lstadd_back(&st->cutline, ft_lstnew(ft_strdup(line[a])));
		a++;
	}
	st->firstcut = st->cutline;
    return (0);
}



/*
        if (st->line[a] && (st->line[a] == ';' || st->line[a] == '|'))
        {
			c = st->line[a];
            a++;
            while (st->line[a] == ' ')
                a++;
            if (st->line[a] == ';' || st->line[a] == '|')
            {
                if (st->line[a] == ';')
				{
					write(2, "minishell: syntax error near unexpected token `", 47);          //xd\'\n"
					if (st->line[a] == c)
						write(2, ";;\'\n", 4);
					else
						write(2, ";\'\n", 3);
					st->status = 2;
                	return (1);
				}
				if (st->line[a] == '|' && st->line[a] != c)
				{
					write(2, "minishell: syntax error near unexpected token `", 47);          //xd\'\n"
						write(2, "|\'\n", 3);
						st->status = 2;
                		return (1);
				}
            }
        }
*/

/*			if (st->line[a] == '<')
			{
				a++;
				while (st->line[a])
				{
					while (st->line[a] == ' ')
						a++;
           			if (st->line[a] == ';' || st->line[a] == '|')
            		{
                		if (st->line[a] == ';')
							write(2, ";\'\n", 3);
						if (st->line[a] == '|')
							write(2, "|\'\n", 3);
                		st->status = 2;
                		return (1);
					}
					a++;
				} 
//				write(2, "newline'\n", 9);
			}*/