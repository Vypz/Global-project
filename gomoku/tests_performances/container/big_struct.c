#include	<stdio.h>

typedef union
{
  char	val;
  char	zefio[4096];
}	type;

inline void	set(type* tab, char i, char j, char new)
{
  tab[i*19+j].val = new;
}

int	main()
{
  type	tab[19*19];
  int	n;
  char	i;
  char	j;

  for (n = 0; n < 1000000; n++)
    for (i = 0; i < 19; i++)
      for (j = 0; j < 19; j++)
	set(tab, i, j, 2);
  if (tab[7].val == 2)
    printf("true\n");
  return 0;
}
