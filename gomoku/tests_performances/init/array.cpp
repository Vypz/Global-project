#include	<array>

void	func()
{
  std::array<char, 8>	tab;

  tab.fill(0);
}

int	main()
{
  int	i;

  for (i = 0; i < 100000000; i++)
    func();
  return 0;
}
