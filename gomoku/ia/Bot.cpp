//
// Bot.cpp for gomoku in /home/pridea_v/rendu/gomoku-2017-larue_a
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Mon Feb  9 15:31:05 2015 virgile prideaux
// Last update Wed Feb 25 00:29:20 2015 virgile prideaux
//


#include	<iostream>
#include	<stdio.h>
#include	"Bot.hpp"

Bot::Bot()
  : seed(std::chrono::system_clock::now().time_since_epoch().count())
{
  this->gen = new std::mt19937(seed);
}

Bot::~Bot()
{
  delete this->gen;
}

bool			Bot::genGame(const Arbitre& a, Arbitre& b, uint8_t x, uint8_t y, uint8_t& bestX, uint8_t& bestY, int& best, uint8_t simulation, uint8_t whoseTurn)
{
  int			wins = 0;
  Arbitre::Event	e;
  int			i;
  uint8_t		v;
  uint8_t		stuck = 0;
  uint8_t		w;
  int			random;

  // printf("genGame(%d, %d)\n", x, y);
  if (a.getCaseContent(x, y))
    return false;
  b = a;
  if (a.getRules() >= 2)
    {
      if (b.play(x, y) == Arbitre::DENIED)
	{
	  // printf("DENIED on %d, %d\n", x, y);
	  b = a;
	  return false;
	}
      else
	{
	  b = a;
	}
    }
  for (int j = 0; j < simulation; j++)
    {
      e = Arbitre::NONE;
      v = x;
      w = y;
      i = 0;
      while (e != Arbitre::WIN && i < 300)
	{
	  e = b.play(v, w);
	  while (i < 300)
	    {
	      random = (*this->gen)() % 10 + 1;
	      if (random > 5)
		v = x + 11 - random;
	      else
		v = x + random - 6;
	      random = (*this->gen)() % 10 + 1;
	      if (random > 5)
		w = y + 11 - random;
	      else
		w = y + random - 6;
	      if (v < 19 && w < 19 && !b.getCaseContent(v, w))
		break;
	      i++;
	    }
	}
      if (i == 300)
	stuck++;
      else if (b.getWhoseTurn() == whoseTurn)
	wins++;
      b = a;
    }
  // printf("stuck / simulation = %d/%d\n", stuck, simulation);
  if (stuck != simulation && wins * 100 / (simulation - stuck) >= best)
    {
      // printf("new best !\n");
      best = wins * 100 / (simulation - stuck);
      bestX = x;
      bestY = y;
    }
  if (best == 100)
    return true;
  b.setWhoseTurn(whoseTurn);
  if (b.play(x, y) == Arbitre::WIN)
    {
      // printf("bloque un alignement gagnant\n");
      best = 100;
      bestX = x;
      bestY = y;
    }
  return false;
}

Arbitre::Event				Bot::play(Arbitre& a, uint8_t x, uint8_t y, uint8_t& playTime, uint8_t simulation, double timeLimit, uint8_t& savedX, uint8_t& savedY, uint8_t whoseTurn)
{
  std::chrono::steady_clock::time_point	begin = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point	end;
  std::chrono::steady_clock::duration	span = end - begin;
  double				nseconds = 0;
  Arbitre				b(a);
  int					i = 1;
  int					best = 0;
  uint8_t				_x;
  uint8_t				_y;
  uint8_t				bestX;
  uint8_t				bestY;
  uint8_t				spawnMet = 42;
  // printf("--------------------------------------\n");
  // printf("le joueur a joué en %d, %d\n", x, y);
  // while (i < 6)
  while (best == 0 || (spawnMet && i < 6 && nseconds <= timeLimit))
    {
      // printf("nseconds = %d\n", (int)(nseconds * 1000));
      _x = x - i;
      _y = y - i;
      spawnMet = 0;
      for (int j = 1; j <= i * 2; j++)
	{
	  if (_x < 19 && _y < 19)
	    {
	      if (!b.getCaseContent(_x, _y))
		{
		  // printf("[%d][%d]\n", _x, _y);
		  if (this->genGame(a, b, _x, _y, bestX, bestY, best, simulation, whoseTurn))
		    goto end;
		}
	      else
		spawnMet++;
	    }
	  _x += 1;
	}
      for (int j = 1; j <= i * 2; j++)
	{
	  if (_x < 19 && _y < 19)
	    {
	      if (!b.getCaseContent(_x, _y))
		{
		  // printf("[%d][%d]\n", _x, _y);
		  if (this->genGame(a, b, _x, _y, bestX, bestY, best, simulation, whoseTurn))
		    goto end;
		}
	      else
		spawnMet++;
	    }
	  _y += 1;
	}
      for (int j = 1; j <= i * 2; j++)
	{
	  if (_x < 19 && _y < 19)
	    {
	      if(!b.getCaseContent(_x, _y))
		{
		  // printf("[%d][%d]\n", _x, _y);
		  if (this->genGame(a, b, _x, _y, bestX, bestY, best, simulation, whoseTurn))
		    goto end;
		}
	      else
		spawnMet++;
	    }
	  _x -= 1;
	}
      for (int j = 1; j <= i * 2; j++)
	{
	  if (_x < 19 && _y < 19)
	    {
	      if (!b.getCaseContent(_x, _y))
		{
		  // printf("[%d][%d]\n", _x, _y);
		  if (this->genGame(a, b, _x, _y, bestX, bestY, best, simulation, whoseTurn))
		    goto end;
		}
	      else
		spawnMet++;
	    }
	  _y -= 1;
	}
      i++;
      end = std::chrono::steady_clock::now();
      span = end - begin;
      nseconds = double(span.count()) * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
    }
 end:
  // printf("i = %d\n", i);
  // printf("range = %d\n", i);
  if (best != 100 && a.getTheElephant())
    {
      best = 0;
      const uint16_t* dumbo = a.getDumbo();
      // printf("bloque un trois libre (dumbo)\n");
      this->genGame(a, b, dumbo[0] % 19, dumbo[0] / 19, bestX, bestY, best, simulation, whoseTurn);
      this->genGame(a, b, dumbo[1] % 19, dumbo[1] / 19, bestX, bestY, best, simulation, whoseTurn);
      if (dumbo[2] != 0)
  	this->genGame(a, b, dumbo[2] % 19, dumbo[2] / 19, bestX, bestY, best, simulation, whoseTurn);
    }
  // printf("bestX = %d, bestY = %d, best = %d\n", bestX, bestY, best);
  Arbitre::Event	e;

  savedX = bestX;
  savedY = bestY;
  e = a.play(bestX, bestY, true);
  end = std::chrono::steady_clock::now();
  span = end - begin;
  nseconds = double(span.count()) * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
  playTime = (int)(nseconds * 1000);
  return e;
}

// < 10 ms : 10 simul, i < 2
// < 20 ms : 20 simul, i < 2
// < 50 ms : 20 simul, i < 3
