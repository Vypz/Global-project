void	func()
{
  char	tab[8];
  int	i;

  for (i = 0; i < 8; i++)
    tab[i] = 0;
}

int	main()
{
  int	i;

  for (i = 0; i < 100000000; i++)
    func();
  return 0;
}
