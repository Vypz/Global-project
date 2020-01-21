//
// main.cpp for gomoku in /home/pridea_v/rendu/gomoku-2017-larue_a
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Mon Dec  1 19:28:28 2014 virgile prideaux
// Last update Tue Dec  2 14:13:10 2014 virgile prideaux
//

#include	"Gui.hpp"

int	main()
{
  Gui	gui;

  gui.init();
  while (true)
    {
      gui.input();
      if (gui.update() == false)
	break;
    }
  return 0;
}
