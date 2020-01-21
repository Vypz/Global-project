#define	SIZE(x)	((x) & 0x7F)
#define	FREE(x)	((x) >> 7)

int	main()
{
  unsigned char	tab[19*19] = {0};
  int		n;
  int		i;
  int		j;
  int		a;
  int		b;

  for (n = 0; n < 1000000; n++)
    for (i = 0; i < 19; i++)
      for (j = 0; j < 19; j++)
	{
	  a = SIZE(tab[i * j]);
	  b = FREE(tab[i * j]);
	}
  return 0;
}
