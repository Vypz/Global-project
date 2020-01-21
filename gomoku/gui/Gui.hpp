//
// Gui.hpp for gomoku in /home/pridea_v/rendu/gomoku-2017-larue_a/gui
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Mon Dec  1 19:28:15 2014 virgile prideaux
// Last update Mon Dec  8 16:15:17 2014 virgile prideaux
//

#ifndef		_GUI_HPP_
# define	_GUI_HPP_

# include	"GameScene.hpp"

class	Gui
{
private:
  sf::RenderWindow	window;
  sf::Mouse		mouse;
  GameScene*		currentScene;
  GameScene*		tmp;

public:
  Gui();
  ~Gui();

  void	init();
  bool	update();
  void	input();
};

#endif	// !GUI_HPP_
