#include "../include/minishell.h"

static int  ft_malloc_tab(char const *str, char c)
{
    int     a;
    int     counter;

    a = 0;
    counter = 0;
//    printf("str : |%s|\n", str);
    while (str[a])
    {
        while (str[a] && str[a] == ' ')
            a++;
        if (str[a] && str[a] != c)
            counter++;
        while (str[a] && str[a] != c)
        {
            if (str[a] && (str[a] == '"' || str[a] == '\''))
            {
                a++;
                while (str[a] && str[a] != '"' && str[a] != '\'')
                    a++;
            }
            a++;
            if (str[a] && str[a] == c && str[a - 1] == '\\')
                a++;
        }
//        printf("str[a] 1 : |%c|\n", str[a]);
        if (!str[a])
            break;
        a++;
//        printf("str[a] 2 : |%c|\n", str[a]);
    }
//    printf("counter : |%d|\n", counter);
    return (counter);
}

static char		*ft_free(char **tab)
{
	int	a;

	a = 0;
	while (tab[a] != NULL)
	{
		free(tab[a]);
		a++;
	}
	free(tab);
    return (NULL);
}

static char		*ft_write2(const char *str, char c, char **tab)
{
	int     a;
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
        a++;
        if (str[a] && str[a] == c && str[a - 1] == '\\')
            a++;
    }
//    printf("a : %d\n", a);
	dest = ft_substr(str, 0, a);
    if (dest == NULL)
        ft_free(tab);
//    printf("dest : |%s|\n", dest);
	return (dest);
}

static char     **ft_write(const char *str, char c, char **tab, shell *st)
{
    int     a;
    int     d;
    char    *fri;

    a = 0;
    d = 0;
    fri = NULL;
    while (str[a])
    {
        while (str[a] && str[a] == ' ')
            a++;
        if (str[a] && str[a] != c)
            tab[d++] = ft_write2(&str[a], c, tab);
        if (str[a] && str[a] == c)
        {
            tab[d] = NULL;
            fri = ft_strdup("minishell: syntax error near unexpected token `;\'\n");
       	    write(1, fri, ft_strlen(fri));
		    free(fri);
            ft_free(tab);
            st->status = 2;
            return (tab);
        }
        while (str[a] && str[a] != c)
        {
            if (str[a] && (str[a] == '"' || str[a] == '\''))
            {
                a++;
                while (str[a] && str[a] != '"' && str[a] != '\'')
                    a++;
            }
            a++;
            if (str[a] && str[a] == c && str[a - 1] == '\\')
                a++;
        }
        if (!str[a])
            break;
        a++;
    }
	tab[d] = NULL;
/*
    a = 0;
    while (tab[a])
    {
        printf("%d : |%s|\n", a, tab[a]);
        a++;
    }
    printf("%d : |%s|\n", a, tab[a]);
*/
    return (tab);
}

char			**ft_splitms(char const *s, char c, shell *st)
{
	char	**tab;

	if (s == NULL)
		return (NULL);
	if (!(tab = malloc((ft_malloc_tab(s, c) + 1) * sizeof(char*))))
		return (NULL);
	return (ft_write(s, c, tab, st));
}
