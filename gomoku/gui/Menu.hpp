//
// Menu.hpp for gomoku in /home/pridea_v/rendu/gomoku-2017-larue_a/gui
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Mon Dec  1 19:59:08 2014 virgile prideaux
// Last update Thu Jan  8 14:10:44 2015 virgile prideaux
//

#ifndef		_MENU_HPP_
# define	_MENU_HPP_

# include	"GameScene.hpp"

class	Menu : public GameScene
{
private:
  sf::Text	title;
  sf::Text	exit;
  sf::Text	vsPlayer;
  sf::Text	vsIA;

public:
  Menu();
  ~Menu();

  void	init();
  void	draw(sf::RenderWindow& window);
  void	input(int x, int y, bool action);
};

#endif	// !MENU_HPP_
