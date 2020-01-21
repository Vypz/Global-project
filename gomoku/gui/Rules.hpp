//
// Rules.hpp for gomoku in /home/pridea_v/rendu/gomoku-2017-larue_a/gui
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Wed Dec  3 14:20:12 2014 virgile prideaux
// Last update Mon Feb  9 14:47:13 2015 virgile prideaux
//

#ifndef		_RULES_HPP_
# define	_RULES_HPP_

# include	"GameScene.hpp"

class	Rules : public GameScene
{
private:
  sf::Text		title;
  sf::Text		rule1;
  sf::Text		rule2;
  sf::Text		bothRules;
  sf::Text		check;
  sf::Text		menu;
  sf::Text		noneRules;
  bool			ai;

public:
  Rules(bool ai);
  ~Rules();

  void	init();
  void	draw(sf::RenderWindow& window);
  void	input(int x, int y, bool action);
};

#endif	// !RULES_HPP_
