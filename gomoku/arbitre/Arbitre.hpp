//
// Arbitre.hpp for gomoku in /home/pridea_v/rendu/gomoku-2017-larue_a/arbitre
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Sat Jan 17 13:48:20 2015 virgile prideaux
// Last update Tue Feb 24 23:02:41 2015 virgile prideaux
//

#ifndef		_ARBITRE_HPP_
# define	_ARBITRE_HPP_

# include	<stdint.h>

# define	LENGTH	2

class	Arbitre
{
public:
  enum	Event
    {
      DENIED,
      PREVENTED,
      WIN,
      CAPTURE,
      NONE
    };

private:
  uint8_t	rules;
  uint8_t	whoseTurn;
  uint8_t	redScore;
  uint8_t	blueScore;
  bool		update;
  uint8_t	board[19 * 19];
  uint16_t	capturedThisTurn[16];
  uint8_t	_capturedThisTurn;
  bool		theElephant;
  uint16_t	dumbo[3];

  bool		tryAxis(uint16_t z, uint8_t dz);
  bool		tryPlay(uint16_t z);
  bool		tryVulnerable(uint16_t z, uint8_t dz);
  bool		vulnerable(uint8_t x, uint8_t y, uint16_t z, uint8_t dz);
  bool		tryFree(uint16_t z, uint8_t dz);
  bool		free(uint8_t x, uint8_t y, uint16_t z, uint8_t dz);
  Event		axis(uint8_t x, uint8_t y, uint16_t z, uint8_t dz, bool elephant);
  void		axisInit(uint8_t *counters, bool *done, bool *left, bool *right);
  void		axisPart1(uint16_t z, uint8_t dz, uint8_t& vRight, uint8_t* counters, bool* right, bool* done, uint8_t limit);
  void		axisPart2(uint16_t z, uint8_t dz, uint8_t& vLeft, uint8_t* counters, bool* left, bool* done, uint8_t limit);
  Event		axisPart3(uint16_t z, uint8_t dz, uint8_t vLeft, uint8_t vRight);
  Event		axisPart4(uint16_t z, uint8_t dz, bool* left, bool* right);

public:
  Arbitre(uint8_t rules);
  Arbitre(const Arbitre& other);
  ~Arbitre();
  const Arbitre&	operator=(const Arbitre& other);

  void		reset();
  Event		play(uint8_t x, uint8_t y, bool elephant = false);
  uint8_t	getRules() const;
  uint8_t	getBlueScore() const;
  uint8_t	getRedScore() const;
  uint8_t	getCaseContent(uint8_t x, uint8_t y) const;
  void		resetUpdate();
  bool		getUpdate() const;
  uint8_t	getWhoseTurn() const;
  void		setWhoseTurn(uint8_t whose);
  const uint16_t*	getDumbo() const;
  bool		getTheElephant() const;
};

#endif	// !ARBITRE_HPP_
