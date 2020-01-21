void	func()
{
  char	tab[8];

  tab[0] = 0;
  tab[1] = 0;
  tab[2] = 0;
  tab[3] = 0;
  tab[4] = 0;
  tab[5] = 0;
  tab[6] = 0;
  tab[7] = 0;
}

int	main()
{
  int	i;

  for (i = 0; i < 100000000; i++)
    func();
  return 0;
}
