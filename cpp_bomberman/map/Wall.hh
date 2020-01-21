//
// Wall.hh for  in /home/ouroub_a/C++/Bomberman/map
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Tue May 20 09:34:16 2014 amina ourouba
// Last update Sun Jun 15 18:43:46 2014 virgile prideaux
//

#ifndef		WALL_HH_
# define	WALL_HH_

# include	"AElement.hh"
# include	"Bonus.hh"

class Wall : public AElement
{
private:
  Wall(const Wall& b);
  Wall&			operator=(const Wall& b);
  bool			_destroyable;
  Bonus::BonType	_hiddenBonus;

public:
  Wall(int x, int y, bool destroyable);
  ~Wall();

  bool			isDestroyable() const;
  bool			walkThrough() const;
  Bonus::BonType	getBonType() const;
};

#endif	/* !WALL_HH_ */
