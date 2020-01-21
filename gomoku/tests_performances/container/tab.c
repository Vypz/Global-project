#include	<stdio.h>

inline void	set(char tab[19][19], int i, int j, char new)
{
  tab[i][j] = new;
}

int	main()
{
  char	tab[19][19];
  int	n;
  char	i;
  char	j;

  for (n = 0; n < 1000000; n++)
    for (i = 0; i < 19; i++)
      for (j = 0; j < 19; j++)
	set(tab, i, j, 2);
  if (tab[7][3] == 2)
    printf("true\n");
  return 0;
}
