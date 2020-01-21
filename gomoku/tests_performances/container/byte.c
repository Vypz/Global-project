#include	<stdio.h>

inline void	set(unsigned char* tab, char i, char j, char new)
{
  int	mod = j % 4;
  int	n = i * 5 + j / 4;

  tab[n] &= 3 << (mod * 2);
  tab[n] |= new << (mod * 2);
}

int	main()
{
  unsigned char	tab[5*19];
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
