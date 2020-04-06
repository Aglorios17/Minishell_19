#include "minishell.h"

int main()
{
	int bcl;
	char *line;
	int i;
	int y;
	char *echo;
//	int ret;

	bcl = 1;
	y = 0;
	line = NULL;
	echo = NULL;
	write(1,"\n",1);
	write(1,"by Aglorios and Gverhelp\n",25);
	write(1,"\n",1);
	while(bcl == 1)
	{
		write(1,"#",1);
		while (get_next_line3d(0, &line) != 1)
		{
		}
		if (ft_strncmp(&line[1], "echo", 4))
		{
			i = 5;
			while(line[i])
			{
				write(1,&line[i],1);
				i++;
			}
		}
		else
			write(1, "NOP", 4);
		write(1,"\n",1);
	}
	return (0);
}
