//
// Goban.hpp for gomoku in /home/pridea_v/rendu/gomoku-2017-larue_a/gui
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Tue Dec  2 14:20:48 2014 virgile prideaux
// Last update Tue Feb 24 23:36:30 2015 virgile prideaux
//

#ifndef		_GOBAN_HPP_
# define	_GOBAN_HPP_

# include	"GameScene.hpp"
# include	"Arbitre.hpp"
# include	"Bot.hpp"

class	Goban : public GameScene
{
private:
  Arbitre	arbitre;
  bool		displayPreview;
  sf::Sprite	preview;
  sf::Sprite	goban;
  sf::Sprite	blue;
  sf::Sprite	orange;
  sf::Text	menu;
  sf::Text	playerLog;
  sf::Text	botLog;
  sf::Text	blueScore;
  sf::Text	orangeScore;
  bool		isPlaying;
  sf::RectangleShape	overlay;
  sf::Text		replay;
  uint8_t	board[19][19];
  Bot		bot;
  bool		ai;

  uint8_t	simulation;
  double	timeLimit;

  sf::Text	findAPlay;
  sf::Text	botSpeed;
  sf::Text	ten;
  sf::Text	twenty;
  sf::Text	fifty;
  sf::Text	takeYourTime;

  uint8_t	_x;
  uint8_t	_y;

  void		drawSpawns(sf::RenderWindow& window);
  void		onMouseOver(int x, int y, bool action);

public:
  Goban(int rules, bool ai);
  ~Goban();

  void	init();
  void	update();
  void	draw(sf::RenderWindow& window);
  void	input(int x, int y, bool action);
  void	updateBoard();
};

#endif	// !GOBAN_HPP_
