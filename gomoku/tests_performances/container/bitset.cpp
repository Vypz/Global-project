#include	<bitset>
#include	<iostream>

int	main()
{
  std::bitset<19*19*2>	tab;
  int	n;
  char	i;
  char	j;

  for (n = 0; n < 1000000; n++)
    for (i = 0; i < 19; i++)
      for (j = 0; j < 19; j++)
	tab.set((j * 19 + i) * 2);
  if (tab.test(7) == 1)
    std::cout << "true\n" << std::endl;
  return 0;
}
