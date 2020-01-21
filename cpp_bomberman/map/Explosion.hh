//
// Bomb.hh for  in /home/ouroub_a/rendu/cpp_bomberman/map
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Tue May 13 17:27:18 2014 amina ourouba
// Last update Sun Jun 15 18:41:30 2014 virgile prideaux
//

#ifndef		EXPLOSION_HH_
# define	EXPLOSION_HH_

# include	<Clock.hh>
# include	"AElement.hh"
# include	"Wall.hh"
# include	"Bonus.hh"

class	Engine;

class Explosion : public AElement
{
private:
  float			_curFrame;
  Bonus::BonType	_bonus;

  Explosion(const Explosion&);
  Explosion&		operator=(const Explosion&);

public:
  Explosion(int x, int y, Map& map);
  ~Explosion();

  bool		walkThrough() const;
  void		update(Engine& e);
  int		getFrame(gdl::Clock& clock);
};

#endif	/* !EXPLOSION_HH_ */
