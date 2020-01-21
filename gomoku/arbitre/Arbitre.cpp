//
// Arbitre.cpp for gomoku in /home/pridea_v/rendu/gomoku-2017-larue_a/arbitre
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Fri Jan 16 16:46:13 2015 virgile prideaux
// Last update Wed Feb 25 02:02:40 2015 virgile prideaux
//

#include	<iostream>
#include	<stdio.h>
#include	"Arbitre.hpp"

enum	State
  {
    SELF,
    OTHER,
    EMPTY,
    END
  };

static const State	allPatterns[][5] = 
  {
    {OTHER, OTHER, SELF, END, END},
    {SELF, SELF, EMPTY, END, END},
    {SELF, EMPTY, END, END, END},
    {EMPTY, END, END, END, END},
    {EMPTY, SELF, SELF, EMPTY, END},
    {EMPTY, SELF, EMPTY, END, END},
    {SELF, EMPTY, SELF, EMPTY, END}
  };

static const State	capPatterns[][3] = 
  {
    {SELF, OTHER, END},
    {SELF, EMPTY, END},
    {EMPTY, END, END},
    {OTHER, END, END}
  };

Arbitre::Arbitre(uint8_t rules)
  : rules(rules), whoseTurn(1), redScore(0), blueScore(0), update(true)
{
  for (int i = 0; i < 19 * 19; i++)
    {
      this->board[i] = 0;
    }
}

Arbitre::Arbitre(const Arbitre& other)
  : rules(other.rules), whoseTurn(other.whoseTurn),
    redScore(other.redScore), blueScore(other.blueScore),
    theElephant(other.theElephant)
{
  for (int i = 0; i < 19 * 19; i++)
    {
      this->board[i] = other.board[i];
    }
  for (int i = 0; i < 3; i++)
    {
      this->dumbo[i] = other.dumbo[i];
    }
}

const Arbitre&	Arbitre::operator=(const Arbitre& other)
{
  this->rules = other.rules;
  this->whoseTurn = other.whoseTurn;
  this->redScore = other.redScore;
  this->blueScore = other.blueScore;
  this->theElephant = other.theElephant;
  for (int i = 0; i < 19 * 19; i++)
    this->board[i] = other.board[i];
  for (int i = 0; i < 3; i++)
    this->dumbo[i] = other.dumbo[i];
  return *this;
}

Arbitre::~Arbitre()
{}

bool	Arbitre::tryVulnerable(uint16_t z, uint8_t dz)
{
  if (dz != 1 && this->vulnerable(z % 19, z / 19, z, 1))
    return true;
  if (dz != 19 && this->vulnerable(z % 19, z / 19, z, 19))
    return true;
  if (dz != 18 && this->vulnerable(z % 19, z / 19, z, 18))
    return true;
  if (dz != 20 && this->vulnerable(z % 19, z / 19, z, 20))
    return true;
  return false;
}

bool	Arbitre::vulnerable(uint8_t x, uint8_t y, uint16_t z, uint8_t dz)
{
  State		s;
  uint8_t	counters[5];
  bool		left[5];
  bool		right[5];
  bool		done[5];
  uint8_t	posLimit = 0;
  uint8_t	negLimit = 0;

  for (int i = 0; i < 5; i++)
    {
      counters[i] = 0;
      left[i] = false;
      right[i] = false;
      done[i] = false;
    }

  if (dz == 1)
    {
      posLimit = 18 - x;
      negLimit = x;
    }
  else if (dz == 19)
    {
      posLimit = 18 - y;
      negLimit = y;
    }
  else if (dz == 18)
    {
      if (x + y > 18)
	{
	  posLimit = 18 - y;
	  negLimit = 18 - x;
	}
      else
	{
	  posLimit = x;
	  negLimit = y;
	}
    }
  else if (dz == 20)
    {
      if (y >= x)
	{
	  posLimit = 18 - y;
	  negLimit = x;
	}
      else
	{
	  posLimit = 18 - x;
	  negLimit = y;
	}
    }

  for (int i = 1; i <= posLimit; i++)
    {
      if (done[0] && done[1] && done[2] && done[3])
	break;
      if (this->board[z + i * dz] == this->whoseTurn)
	{
	  s = SELF;
	}
      else if (this->board[z + i * dz])
	{
	  s = OTHER;
	}
      else
	{
	  s = EMPTY;
	}
      for (int j = 0; j < 4; j++)
	{
	  if (done[j])
	    continue;
	  if (capPatterns[j][counters[j]] != s)
	    done[j] = true;
	  else
	    {
	      counters[j]++;
	      if (capPatterns[j][counters[j]] == END)
		{
		  right[j] = true;
		  done[j] = true;
		}
	    }
	}
    }
  for (int i = 0; i < 5; i++)
    {
      counters[i] = 0;
      done[i] = false;
    }
  for (int i = 1; i <= negLimit; i++)
    {
      if (done[0] && done[1] && done[2] && done[3])
	break;
      if (this->board[z - i * dz] == this->whoseTurn)
	{
	  s = SELF;
	}
      else if (this->board[z - i * dz])
	{
	  s = OTHER;
	}
      else
	{
	  s = EMPTY;
	}
      for (uint8_t j = 0; j < 4; j++)
	{
	  if (done[j])
	    continue;
	  if (capPatterns[j][counters[j]] != s)
	    done[j] = true;
	  else
	    {
	      counters[j]++;
	      if (capPatterns[j][counters[j]] == END)
		{
		  left[j] = true;
		  done[j] = true;
		}
	    }
	}
    }
  if (right[1] && left[3])
    {
      // std::cout << "vulnerable() : o(x)x." << std::endl;
      if (this->rules >= 2)
	{
	  if (!this->tryPlay(z + 2 * dz))
	    {
	      this->board[z + 2 * dz] = 0;
	      return false;
	    }
	  this->board[z + 2 * dz] = 0;
	}
      return true;
    }
  if (right[2] && left[0])
    {
      // std::cout << "vulnerable() : ox(x)." << std::endl;
      if (this->rules >= 2)
	{
	  if (!this->tryPlay(z + dz))
	    {
	      this->board[z + dz] = 0;
	      return false;
	    }
	  this->board[z + dz] = 0;
	}
      return true;
    }
  if (right[0] && left[2])
    {
      // std::cout << "vulnerable() : .(x)xo" << std::endl;
      if (this->rules >= 2)
	{
	  if (!this->tryPlay(z - dz))
	    {
	      this->board[z - dz] = 0;
	      return false;
	    }
	  this->board[z - dz] = 0;
	}
      return true;
    }
  if (right[3] && left[1])
    {
      // std::cout << "vulnerable() : .x(x)o" << std::endl;
      if (this->rules >= 2)
	{
	  if (!this->tryPlay(z - 2 * dz))
	    {
	      this->board[z - 2 * dz] = 0;
	      return false;
	    }
	  this->board[z - 2 * dz] = 0;
	}
      return true;
    }
  return false;
}

bool	Arbitre::free(uint8_t x, uint8_t y, uint16_t z, uint8_t dz)
{
  State		s;
  uint8_t	counters[7];
  bool		left[7];
  bool		right[7];
  bool		done[7];
  uint8_t	posLimit = 0;
  uint8_t	negLimit = 0;

  for (int i = 0; i < 7; i++)
    {
      counters[i] = 0;
      left[i] = false;
      right[i] = false;
      done[i] = false;
    }
  if (dz == 1)
    {
      posLimit = 18 - x;
      negLimit = x;
    }
  else if (dz == 19)
    {
      posLimit = 18 - y;
      negLimit = y;
    }
  else if (dz == 18)
    {
      if (x + y > 18)
	{
	  posLimit = 18 - y;
	  negLimit = 18 - x;
	}
      else
	{
	  posLimit = x;
	  negLimit = y;
	}
    }
  else if (dz == 20)
    {
      if (y >= x)
	{
	  posLimit = 18 - y;
	  negLimit = x;
	}
      else
	{
	  posLimit = 18 - x;
	  negLimit = y;
	}
    }

  for (int i = 1; i <= posLimit; i++)
    {
      if (done[0] && done[1] && done[2] && done[3] && done[4] && done[5])
	break;
      if (this->board[z + i * dz] == this->whoseTurn)
	{
	  s = SELF;
	}
      else if (this->board[z + i * dz])
	{
	  s = OTHER;
	}
      else
	{
	  s = EMPTY;
	}
      for (uint8_t j = 0; j < 6; j++)
	{
	  if (done[j])
	    continue;
	  if (allPatterns[j + 1][counters[j]] != s)
	    done[j] = true;
	  else
	    {
	      counters[j]++;
	      if (allPatterns[j + 1][counters[j]] == END)
		{
		  right[j] = true;
		  done[j] = true;
		}
	    }
	}
    }
  for (int i = 0; i < 7; i++)
    {
      counters[i] = 0;
      done[i] = false;
    }
  for (int i = 1; i <= negLimit; i++)
    {
      if (done[0] && done[1] && done[2] && done[3] && done[4] && done[5])
	break;
      if (this->board[z - i * dz] == this->whoseTurn)
	{
	  s = SELF;
	}
      else if (this->board[z - i * dz])
	{
	  s = OTHER;
	}
      else
	{
	  s = EMPTY;
	}
      for (int j = 0; j < 6; j++)
	{
	  if (done[j])
	    continue;
	  if (allPatterns[j + 1][counters[j]] != s)
	    done[j] = true;
	  else
	    {
	      counters[j]++;
	      if (allPatterns[j + 1][counters[j]] == END)
		{
		  left[j] = true;
		  done[j] = true;
		}
	    }
	}
    }
  if (right[0] && left[2])
    {
      // std::cout << "free() : .(x)xx." << std::endl;
      return true;
    }
  if (right[1] && left[1])
    {
      // std::cout << "free() : .x(x)x." << std::endl;
      return true;
    }
  if (right[2] && left[0])
    {
      // std::cout << "free() : .xx(x)." << std::endl;
      return true;
    }
  if (right[5] && left[2])
    {
      // std::cout << "free() : .(x)x.x." << std::endl;
      return true;
    }
  if (right[4] && left[1])
    {
      // std::cout << "free() : .x(x).x." << std::endl;
      return true;
    }
  if (right[2] && left[3])
    {
      // std::cout << "free() : .xx.(x)." << std::endl;
      return true;
    }
  if (right[3] && left[2])
    {
      // std::cout << "free() : .(x).xx." << std::endl;
      return true;
    }
  if (right[1] && left[4])
    {
      // std::cout << "free() : .x.(x)x." << std::endl;
      return true;
    }
  if (right[2] && left[5])
    {
      // std::cout << "free() : .x.x(x)." << std::endl;
      return true;
    }
  return false;
}

bool	Arbitre::tryFree(uint16_t z, uint8_t dz)
{
  if (dz != 1 && this->free(z % 19, z / 19, z, 1))
    return true;
  if (dz != 19 && this->free(z % 19, z / 19, z, 19))
    return true;
  if (dz != 18 && this->free(z % 19, z / 19, z, 18))
    return true;
  if (dz != 20 && this->free(z % 19, z / 19, z, 20))
    return true;
  return false;
}

void		Arbitre::axisPart1(uint16_t z, uint8_t dz, uint8_t& vRight, uint8_t* counters, bool* right, bool* done, uint8_t limit)
{
  State		s;
  bool		vCheck = true;

  for (int i = 1; i <= limit; i++)
    {
      if (!vCheck && done[0] && done[1] && done[2] && done[3] && done[4] && done[5] && done[6])
	break;
      if (this->board[z + i * dz] == this->whoseTurn)
	{
	  if (vCheck)
	    vRight++;
	  s = SELF;
	}
      else if (this->board[z + i * dz])
	{
	  vCheck = false;
	  s = OTHER;
	}
      else
	{
	  vCheck = false;
	  s = EMPTY;
	}
      for (int j = 0; j < 7; j++)
	{
	  if (done[j])
	    continue;
	  if (allPatterns[j][counters[j]] != s)
	    done[j] = true;
	  else
	    {
	      counters[j]++;
	      if (allPatterns[j][counters[j]] == END)
		{
		  right[j] = true;
		  done[j] = true;
		}
	    }
	}
    }
}

void			Arbitre::axisPart2(uint16_t z, uint8_t dz, uint8_t& vLeft, uint8_t* counters, bool* left, bool* done, uint8_t limit)
{
  State		s;
  bool		vCheck = true;

  for (int i = 1; i <= limit; i++)
    {
      if (!vCheck && done[0] && done[1] && done[2] && done[3] && done[4] && done[5] && done[6])
	break;
      if (this->board[z - i * dz] == this->whoseTurn)
	{
	  if (vCheck)
	    vLeft++;
	  s = SELF;
	}
      else if (this->board[z - i * dz])
	{
	  vCheck = false;
	  s = OTHER;
	}
      else
	{
	  vCheck = false;
	  s = EMPTY;
	}
      for (int j = 0; j < 7; j++)
	{
	  if (done[j])
	    continue;
	  if (allPatterns[j][counters[j]] != s)
	    done[j] = true;
	  else
	    {
	      counters[j]++;
	      if (allPatterns[j][counters[j]] == END)
		{
		  left[j] = true;
		  done[j] = true;
		}
	    }
	}
    }
}

Arbitre::Event			Arbitre::axisPart3(uint16_t z, uint8_t dz, uint8_t vLeft, uint8_t vRight)
{
  if (vRight + vLeft >= 4)
    {
      if (this->rules == 1 || this->rules == 3)
	{
	  uint16_t	start = z - vLeft * dz;
	  uint8_t	size = vRight + vLeft + 1;

	  for (uint8_t i = 0; i < size; i++)
	    {
	      if (this->tryVulnerable(start + i * dz, dz))
		{
		  if (i < 5 && size - i - 1 < 5)
		    return PREVENTED;
		}
	    }
	}
      return WIN;
    }
  return NONE;
}

Arbitre::Event			Arbitre::axisPart4(uint16_t z, uint8_t dz, bool* left, bool* right)
{
  if (left[0] || right[0])
    {
      if (left[0])
	{
	  this->capturedThisTurn[this->_capturedThisTurn++] = z - dz;
	  this->capturedThisTurn[this->_capturedThisTurn++] = z - 2 * dz;
	}
      if (right[0])
	{
	  this->capturedThisTurn[this->_capturedThisTurn++] = z + dz;
	  this->capturedThisTurn[this->_capturedThisTurn++] = z + 2 * dz;
	}
      return CAPTURE;
    }
  return NONE;
}

Arbitre::Event			Arbitre::axis(uint8_t x, uint8_t y, uint16_t z, uint8_t dz, bool elephant)
{
  uint8_t	vLeft = 0;
  uint8_t	vRight = 0;
  uint8_t	counters[7];
  bool		left[7];
  bool		right[7];
  bool		done[7];
  uint8_t	posLimit = 0;
  uint8_t	negLimit = 0;

  for (int i = 0; i < 7; i++)
    {
      counters[i] = 0;
      left[i] = false;
      right[i] = false;
      done[i] = false;
    }
  if (dz == 1)
    {
      posLimit = 18 - x;
      negLimit = x;
    }
  else if (dz == 19)
    {
      posLimit = 18 - y;
      negLimit = y;
    }
  else if (dz == 18)
    {
      if (x + y > 18)
	{
	  posLimit = 18 - y;
	  negLimit = 18 - x;
	}
      else
	{
	  posLimit = x;
	  negLimit = y;
	}
    }
  else if (dz == 20)
    {
      if (y >= x)
	{
	  posLimit = 18 - y;
	  negLimit = x;
	}
      else
	{
	  posLimit = 18 - x;
	  negLimit = y;
	}
    }

  this->axisPart1(z, dz, vRight, counters, right, done, posLimit);

  for (int i = 0; i < 7; i++)
    {
      counters[i] = 0;
      done[i] = false;
    }
  this->axisPart2(z, dz, vLeft, counters, left, done, negLimit);

  if (right[1] && left[3])
    {
      // std::cout << "axis() : .(x)xx." << std::endl;
      if (this->rules >= 2 && (this->tryFree(z, dz) ||
			       this->tryFree(z + dz, dz) ||
			       this->tryFree(z + 2 * dz, dz)))
	return DENIED;
      if (elephant)
	{
	  this->theElephant = true;
	  this->dumbo[0] = z - dz;
	  this->dumbo[1] = z + 3 * dz;
	  this->dumbo[2] = 0;
	}
    }
  if (right[2] && left[2])
    {
      // std::cout << "axis() : .x(x)x." << std::endl;
      if (this->rules >= 2 && (this->tryFree(z, dz) ||
			       this->tryFree(z + dz, dz) ||
			       this->tryFree(z - dz, dz)))
	return DENIED;
      if (elephant)
	{
	  this->theElephant = true;
	  this->dumbo[0] = z - 2 * dz;
	  this->dumbo[1] = z + 2 * dz;
	  this->dumbo[2] = 0;
	}
    }
  if (right[3] && left[1])
    {
      // std::cout << "axis() : .xx(x)." << std::endl;
      if (this->rules >= 2 && (this->tryFree(z, dz) ||
			       this->tryFree(z - dz, dz) ||
			       this->tryFree(z - 2 * dz, dz)))
	return DENIED;
      if (elephant)
	{
	  this->theElephant = true;
	  this->dumbo[0] = z - 3 * dz;
	  this->dumbo[1] = z + dz;
	  this->dumbo[2] = 0;
	}
    }
  if (right[6] && left[3])
    {
      // std::cout << "axis() : .(x)x.x." << std::endl;
      if (this->rules >= 2 && (this->tryFree(z, dz) ||
			       this->tryFree(z + dz, dz) ||
			       this->tryFree(z + 3 * dz, dz)))
	return DENIED;
      if (elephant)
	{
	  this->theElephant = true;
	  this->dumbo[0] = z - dz;
	  this->dumbo[1] = z + 2 * dz;
	  this->dumbo[2] = z + 4 * dz;
	}
    }
  if (right[5] && left[2])
    {
      // std::cout << "axis() : .x(x).x." << std::endl;
      if (this->rules >= 2 && (this->tryFree(z, dz) ||
			       this->tryFree(z - dz, dz) ||
			       this->tryFree(z + 2 * dz, dz)))
	return DENIED;
      if (elephant)
	{
	  this->theElephant = true;
	  this->dumbo[0] = z - 2 * dz;
	  this->dumbo[1] = z + dz;
	  this->dumbo[2] = z + 3 * dz;
	}
    }
  if (right[3] && left[4])
    {
      // std::cout << "axis() : .xx.(x)." << std::endl;
      if (this->rules >= 2 && (this->tryFree(z, dz) ||
			       this->tryFree(z - 3 * dz, dz) ||
			       this->tryFree(z - 2 * dz, dz)))
	return DENIED;
      if (elephant)
	{
	  this->theElephant = true;
	  this->dumbo[0] = z + dz;
	  this->dumbo[1] = z - dz;
	  this->dumbo[2] = z - 4 * dz;
	}
    }
  if (right[4] && left[3])
    {
      // std::cout << "axis() : .(x).xx." << std::endl;
      if (this->rules >= 2 && (this->tryFree(z, dz) ||
			       this->tryFree(z + 3 * dz, dz) ||
			       this->tryFree(z + 2 * dz, dz)))
	return DENIED;
      if (elephant)
	{
	  this->theElephant = true;
	  this->dumbo[0] = z - dz;
	  this->dumbo[1] = z + dz;
	  this->dumbo[2] = z + 4 * dz;
	}
    }
  if (right[2] && left[5])
    {
      // std::cout << "axis() : .x.(x)x." << std::endl;
      if (this->rules >= 2 && (this->tryFree(z, dz) ||
			       this->tryFree(z + dz, dz) ||
			       this->tryFree(z - 2 * dz, dz)))
	return DENIED;
      if (elephant)
	{
	  this->theElephant = true;
	  this->dumbo[0] = z - dz;
	  this->dumbo[1] = z - 3 * dz;
	  this->dumbo[2] = z + 2 * dz;
	}
    }
  if (right[3] && left[6])
    {
      // std::cout << "axis() : .x.x(x)." << std::endl;
      if (this->rules >= 2 && (this->tryFree(z, dz) ||
			       this->tryFree(z - dz, dz) ||
			       this->tryFree(z - 3 * dz, dz)))
	return DENIED;
      if (elephant)
	{
	  this->theElephant = true;
	  this->dumbo[0] = z + dz;
	  this->dumbo[1] = z - 2 * dz;
	  this->dumbo[2] = z - 4 * dz;
	}
    }
  
  Arbitre::Event e = this->axisPart3(z, dz, vLeft, vRight);
  if (e != NONE)
    return e;

  return this->axisPart4(z, dz, left, right);
}

bool		Arbitre::tryAxis(uint16_t z, uint8_t dz)
{
  uint8_t	x = z % 19;
  uint8_t	y = z / 19;
  State		s;
  uint8_t	counters[7];
  bool		left[7];
  bool		right[7];
  bool		done[7];
  uint8_t	posLimit = 0;
  uint8_t	negLimit = 0;

  for (int i = 0; i < 7; i++)
    {
      counters[i] = 0;
      left[i] = false;
      right[i] = false;
      done[i] = false;
    }

  if (dz == 1)
    {
      posLimit = 18 - x;
      negLimit = x;
    }
  else if (dz == 19)
    {
      posLimit = 18 - y;
      negLimit = y;
    }
  else if (dz == 18)
    {
      if (x + y > 18)
	{
	  posLimit = 18 - y;
	  negLimit = 18 - x;
	}
      else
	{
	  posLimit = x;
	  negLimit = y;
	}
    }
  else if (dz == 20)
    {
      if (y >= x)
	{
	  posLimit = 18 - y;
	  negLimit = x;
	}
      else
	{
	  posLimit = 18 - x;
	  negLimit = y;
	}
    }

  for (int i = 1; i <= posLimit; i++)
    {
      if (done[0] && done[1] && done[2] && done[3] && done[4] && done[5])
	break;
      if (this->board[z + i * dz] == this->whoseTurn)
	{
	  s = SELF;
	}
      else if (this->board[z + i * dz])
	{
	  s = OTHER;
	}
      else
	{
	  s = EMPTY;
	}
      for (int j = 0; j < 6; j++)
	{
	  if (done[j])
	    continue;
	  if (allPatterns[j + 1][counters[j]] != s)
	    done[j] = true;
	  else
	    {
	      counters[j]++;
	      if (allPatterns[j + 1][counters[j]] == END)
		{
		  right[j] = true;
		  done[j] = true;
		}
	    }
	}
    }
  for (int i = 0; i < 7; i++)
    {
      counters[i] = 0;
      done[i] = false;
    }
  for (int i = 1; i <= negLimit; i++)
    {
      if (done[0] && done[1] && done[2] && done[3] && done[4] && done[5])
	break;
      if (this->board[z - i * dz] == this->whoseTurn)
	{
	  s = SELF;
	}
      else if (this->board[z - i * dz])
	{
	  s = OTHER;
	}
      else
	{
	  s = EMPTY;
	}
      for (int j = 0; j < 6; j++)
	{
	  if (done[j])
	    continue;
	  if (allPatterns[j + 1][counters[j]] != s)
	    done[j] = true;
	  else
	    {
	      counters[j]++;
	      if (allPatterns[j + 1][counters[j]] == END)
		{
		  left[j] = true;
		  done[j] = true;
		}
	    }
	}
    }
  if (right[0] && left[2])
    {
      // std::cout << "tryAxis() : .(x)xx." << std::endl;
      if (this->tryFree(z, dz) ||
	  this->tryFree(z + dz, dz) ||
	  this->tryFree(z + 2 * dz, dz))
	return false;
      return true;
    }
  if (right[1] && left[1])
    {
      // std::cout << "tryAxis() : .x(x)x." << std::endl;
      if (this->tryFree(z, dz) ||
	  this->tryFree(z + dz, dz) ||
	  this->tryFree(z - dz, dz))
	return false;
      return true;
    }
  if (right[2] && left[0])
    {
      // std::cout << "tryAxis : .xx(x)." << std::endl;
      if (this->tryFree(z, dz) ||
	  this->tryFree(z - dz, dz) ||
	  this->tryFree(z - 2 * dz, dz))
	return false;
      return true;
    }
  if (right[5] && left[2])
    {
      // std::cout << "tryAxis() : .(x)x.x." << std::endl;
      if (this->tryFree(z, dz) ||
	  this->tryFree(z + dz, dz) ||
	  this->tryFree(z + 3 * dz, dz))
	return false;
      return true;
    }
  if (right[4] && left[1])
    {
      // std::cout << "tryAxis() : .x(x).x." << std::endl;
      if (this->tryFree(z, dz) ||
	  this->tryFree(z - dz, dz) ||
	  this->tryFree(z + 2 * dz, dz))
	return false;
      return true;
    }
  if (right[2] && left[3])
    {
      // std::cout << "tryAxis() : .xx.(x)." << std::endl;
      if (this->tryFree(z, dz) ||
	  this->tryFree(z - 3 * dz, dz) ||
	  this->tryFree(z - 2 * dz, dz))
	return false;
      return true;
    }
  if (right[3] && left[2])
    {
      // std::cout << "tryAxis() : .(x).xx." << std::endl;
      if (this->tryFree(z, dz) ||
	  this->tryFree(z + 3 * dz, dz) ||
	  this->tryFree(z + 2 * dz, dz))
	return false;
      return true;
    }
  if (right[1] && left[4])
    {
      // std::cout << "tryAxis() : .x.(x)x." << std::endl;
      if (this->tryFree(z, dz) ||
	  this->tryFree(z + dz, dz) ||
	  this->tryFree(z - 2 * dz, dz))
	return false;
      return true;
    }
  if (right[2] && left[5])
    {
      // std::cout << "tryAxis() : .x.x(x)." << std::endl;
      if (this->tryFree(z, dz) ||
	  this->tryFree(z - dz, dz) ||
	  this->tryFree(z - 3 * dz, dz))
	return false;
      return true;
    }
  return true;
}

bool	Arbitre::tryPlay(uint16_t z)
{
  this->board[z] = this->whoseTurn;
  if (!this->tryAxis(z, 1))
    return false;
  if (!this->tryAxis(z, 19))
    return false;
  if (!this->tryAxis(z, 18))
    return false;
  if (!this->tryAxis(z, 20))
    return false;
  return true;
}

Arbitre::Event		Arbitre::play(uint8_t x, uint8_t y, bool elephant)
{
  uint16_t			z = y * 19 + x;
  Arbitre::Event		last;
  Arbitre::Event		most = NONE;

  if (!this->board[z])
    {
      this->theElephant = false;
      this->_capturedThisTurn = 0;
      this->board[z] = this->whoseTurn;
      if ((last = this->axis(x, y, z, 1, elephant)) < most)
	most = last;
      if ((last = this->axis(x, y, z, 19, elephant)) < most)
	most = last;
      if ((last = this->axis(x, y, z, 18, elephant)) < most)
	most = last;
      if ((last = this->axis(x, y, z, 20, elephant)) < most)
	most = last;
      if (most != DENIED)
	{
	  if (most == CAPTURE)
	    {
	      if (this->whoseTurn == 2)
		this->redScore += this->_capturedThisTurn;
	      else
		this->blueScore += this->_capturedThisTurn;
	      for (uint8_t i = 0; i < this->_capturedThisTurn; i++)
		{
		  this->board[this->capturedThisTurn[i]] = 0;
		}
	      if (this->redScore >= 10 || this->blueScore >= 10)
		most = WIN;
	    }
	  this->update = true;
	  this->whoseTurn = (this->whoseTurn == 2 ? 1 : 2);
	}
      else
	this->board[z] = 0;
    }
  return most;
}

uint8_t	Arbitre::getRules() const
{
  return this->rules;
}

uint8_t	Arbitre::getBlueScore() const
{
  return this->blueScore;
}

uint8_t	Arbitre::getRedScore() const
{
  return this->redScore;
}

uint8_t	Arbitre::getCaseContent(uint8_t x, uint8_t y) const
{
  return this->board[y * 19 + x];
}

void	Arbitre::resetUpdate()
{
  this->update = false;
}

uint8_t	Arbitre::getWhoseTurn() const
{
  return this->whoseTurn;
}

void	Arbitre::reset()
{
  this->whoseTurn = 1;
  this->redScore = 0;
  this->blueScore = 0;
  for (int i = 0; i < 19 * 19; i++)
    {
      this->board[i] = 0;
    }
  this->update = true;
}

bool	Arbitre::getUpdate() const
{
  return this->update;
}

void	Arbitre::setWhoseTurn(uint8_t whose)
{
  this->whoseTurn = whose;
}

const uint16_t*	Arbitre::getDumbo() const
{
  return this->dumbo;
}

bool		Arbitre::getTheElephant() const
{
  return this->theElephant;
}
