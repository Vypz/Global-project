//
// Cube.hh for bomberman in /home/pridea_v/rendu/cpp_bomberman
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Mon Jun  9 15:10:07 2014 virgile prideaux
// Last update Fri Jun 13 15:14:10 2014 virgile prideaux
//

#ifndef		_CUBE_HH_
# define	_CUBE_HH_

# include	"Plan.hh"

class	Cube : public Plan
{
private:
  Cube(const Cube&);
  Cube&	operator=(const Plan&);

public:
  Cube();
  ~Cube();

  void	setGeometry(int x, int y, int z);
};

#endif	/* !CUBE_HH_ */
