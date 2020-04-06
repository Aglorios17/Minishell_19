#include "minishell.h"

int main()
{
	int bcl;
	char *line;

	bcl = 1;
	line = NULL;
	write(1,"\n",1);
	write(1,"by Aglorios and Gverhelp\n",25);
	write(1,"\n",1);
	write(1,"#",1);
	while(bcl == 1)
	{
		while (ft_get_next_line(0, &line))
		{
		}
	}
	return (0);
}
