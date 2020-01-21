#include	<stdio.h>
#include	<stdint.h>

inline void	set(uint64_t* tab, char i, char j, char new)
{
  tab[i*19+j] = new;
}

int	main()
{
  uint64_t	tab[19*19];
  int	n;
  char	i;
  char	j;

  for (n = 0; n < 1000000; n++)
    for (i = 0; i < 19; i++)
      for (j = 0; j < 19; j++)
	set(tab, i, j, 2);
  if (tab[7] == 2)
    printf("true\n");
  return 0;
}