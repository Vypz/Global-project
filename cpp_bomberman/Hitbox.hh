//
// Hitbox.hh for bomberman in /home/pridea_v/rendu/cpp_bomberman
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Fri Jun 13 15:17:38 2014 virgile prideaux
// Last update Fri Jun 13 15:23:06 2014 virgile prideaux
//

#ifndef		_HITBOX_HH_
# define	_HITBOX_HH_

# include	"Plan.hh"

class	Hitbox : public Plan
{
private:
  Hitbox(const Hitbox&);
  Hitbox&	operator=(const Hitbox&);

public:
  Hitbox();
  ~Hitbox();

  void	setGeometry(int x, int y, int z);
};

#endif	/* !HITBOX */
