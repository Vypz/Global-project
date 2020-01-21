//
// main.cpp for bomberman in /home/pridea_v/rendu/mybomberman
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Wed Apr 30 13:23:26 2014 virgile prideaux
// Last update Sun Jun 15 19:37:04 2014 larue_a
//

#include	"Engine.hh"

#include	<iostream>
#include	<stdexcept>
#include	<sstream>
#include	<time.h>
#include	<unistd.h>

int	commandLine(int ac, char **av, int& nbAI, int& volume, std::string& map, std::string& skin)
{
  nbAI = 1;
  volume = 10;
  ac--;
  av++;
  while (ac)
    {
      if (std::string(av[0]) == "--help")
	{
	  std::cout << "Usage : ./bomberman [--nb-ai|--volume|--map|--skin value]" << std::endl;
	  return (-1);
	}
      if (ac == 1)
	{
	  std::cerr << "Missing argument for " << av[0] << std::endl;
	  return (-1);
	}
      if (std::string(av[0]) == "--nb-ai")
	{
	  std::istringstream	is(av[1]);
	  is >> nbAI;
	}
      else if (std::string(av[0]) == "--volume")
	{
	  std::istringstream	is(av[1]);
	  is >> volume;
	}
      else if (std::string(av[0]) == "--map")
	map = av[1];
      else if (std::string(av[0]) == "--skin")
	skin = av[1];
      else
	{
	  std::cerr << "Unknown parameter " << av[0] << std::endl;
	  return (-1);
	}
      ac -= 2;
      av += 2;
    }
  return (0);
}

int		main(int ac, char **av)
{
  int		nbAI;
  int		volume;
  std::string	map;
  std::string	texture;

  if (commandLine(ac, av, nbAI, volume, map, texture) == -1)
    return (EXIT_FAILURE);
  std::cout << "nbAI: " << nbAI << std::endl << "volume: " << volume << std::endl << "map: " << (map != "" ? map : "Random") << std::endl << "texture: " << (texture != "" ? texture : "Default") << std::endl;
  try
    {
      srandom(time(NULL));
      Engine	engine(nbAI, volume, map, texture);

      if (engine.initialize() == false)
	_exit(EXIT_FAILURE);
      while (engine.update() == true)
	engine.draw();
    }
  catch (std::exception &e)
    {
      std::cerr << e.what() << std::endl;
    }
  return (EXIT_SUCCESS);
}
