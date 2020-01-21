//
// Bot.hpp for gomoku in /home/pridea_v/rendu/gomoku-2017-larue_a/ia
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Mon Feb  9 15:25:54 2015 virgile prideaux
// Last update Tue Feb 24 23:33:59 2015 virgile prideaux
//

#ifndef		BOT_HPP_
# define	BOT_HPP_

# include	<chrono>
# include	<random>
# include	"Arbitre.hpp"

class	Bot
{
private:
  unsigned	seed;
  std::mt19937*	gen;

public:
  Bot();
  ~Bot();

  bool			genGame(const Arbitre& a, Arbitre& b, uint8_t x, uint8_t y, uint8_t& bestX, uint8_t& bestY, int& best, uint8_t simulation, uint8_t whoseTurn);
  Arbitre::Event	play(Arbitre& a, uint8_t x, uint8_t y, uint8_t& playTime, uint8_t simulation, double timeLimit, uint8_t& savedX, uint8_t& savedY, uint8_t whoseTurn = 1);
};

#endif	// !BOT_HPP_
