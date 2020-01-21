//
// AI.hh for AI in /home/mar_j/rendu/cpp_bomberman/map
// 
// Made by julien martini
// Login   <mar_j@epitech.net>
// 
// Started on  Wed Jun  4 15:06:45 2014 julien martini
// Last update Sun Jun 15 18:59:59 2014 virgile prideaux
//

#ifndef		AI_HH_
# define	AI_HH_

# include	<iostream>
# include	<map>
# include	<vector>
# include	<ctime>
# include	<unistd.h>
# include	<stdlib.h>
# include	<utility>
# include	<algorithm>
# include	"AElement.hh"
# include	"Character.hh"
# include	"Bomb.hh"
# include	"Wall.hh"
# include	"Map.hh"

# define	MAX_ITER 5

class AI : public Character
{
public:
  
  typedef std::vector<long int>	Line;

  enum	Type
    {
      NOTHING	= 0x00000000,
      WALL	= 0x0000000F,
      EXPLODE	= 0x000000F0,
      BOMB	= 0x00000F00,
      BONUS	= 0x0000F000,
      PLAYER	= 0x000F0000,
      DBLOCK	= 0x00F00000
    };

private:
  float				_x; // input x
  float				_y; // input y
  bool				_bomb; // pour les lancé de bombes
  bool				_init;
  std::vector<AI::Line >	_map; // pour faciliter le fonctionnent des ia
  AI();
  AI(const AI& other);
  AI&	operator=(const AI& other);
  

public:
  AI(int x, int y);
  ~AI();

  void	initMap(Map& map); // resize la map afin de pouvoir s'en servir
  void	refreshMap(Map& map); // remplit la map 
  void	scan(); // set de l'objectif
  int	searchObject(int x, int y, int iter, AI::Type object); // sert a cherche un objet en perticulier
  int	findSafeArea(float x, float y, int iter); // Cherche une case sans danger
  void	randomMove();
  void	sendInput(float& x, float& y, Map& map); //envoi l'input pour l'IA
  bool	iCanBomb();
  bool	getBomb() const;
  bool	isDangerous();
  void	setBomb(bool set);
};

#endif		/* !AI_HH_ */
