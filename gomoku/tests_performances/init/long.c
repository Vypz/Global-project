#include	<stdint.h>

void	func()
{
  char	tab[8];

  *(uint64_t*)tab = 0;
}

int	main()
{
  int	i;

  for (i = 0; i < 100000000; i++)
    func();
  return 0;
}
