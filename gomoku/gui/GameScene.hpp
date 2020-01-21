//
// GameScene.hpp for gomoku in /home/pridea_v/rendu/gomoku-2017-larue_a/gui
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Mon Dec  1 19:39:53 2014 virgile prideaux
// Last update Thu Jan  8 14:10:59 2015 virgile prideaux
//

#ifndef		_GAMESCENE_HPP_
# define	_GAMESCENE_HPP_

# include	<SFML/Graphics.hpp>

class	GameScene
{
protected:
  std::vector<sf::Texture>	textures;
  sf::Font			gameFont;
  sf::Sprite			background;
  GameScene*			returnScene;

  static void			centerText(sf::Text& obj, int x, int y);
  static bool			onMouseOver(sf::Text& obj, int x, int y);
  static bool			onMouseOver(sf::Sprite& obj, int x, int y);

public:
  GameScene();
  virtual ~GameScene();

  virtual void	init() = 0;
  virtual void	update();
  virtual void	draw(sf::RenderWindow&) = 0;
  virtual void	input(int x, int y, bool action) = 0;
  GameScene*	toScene();
};

#endif	// !GAMESCENE_HPP_
