//
// Bomb.hh for  in /home/ouroub_a/rendu/cpp_bomberman/map
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Tue May 13 17:27:18 2014 amina ourouba
// Last update Sun Jun 15 18:27:19 2014 virgile prideaux
//

#ifndef		BOMB_HH_
# define	BOMB_HH_

# include	"AElement.hh"
# include	"Character.hh"
# include	"Bonus.hh"

class Bomb : public AElement
{
public:
  static const float DEFAULT_TIME = 2;
  static const int DEFAULT_SCOPE = 2;
  static const float BONUS_TIME = 1.5;

private:
  float		_time;
  float		_elapsed;
  int		_scope;
  Character*	_owner;

  Bomb(const Bomb& b);
  Bomb&		operator=(const Bomb& b);

  void		_putExplosion(Map& map, int x, int y, bool& ignore);

public:
  Bomb(int x, int y, int scope, float time, Character *owner);
  ~Bomb();

  float	getTime() const;
  int	getScope() const;
  bool	walkThrough() const;
  void	update(Engine &e);
};

#endif	/* !BOMB_HH_ */
