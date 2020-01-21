//
// Invalid.hh for bomberman in /home/liron_b/rendu/cpp_bomberman/map
//
// Made by liron_b
// Login   <liron_b@epitech.net>
//
// Started on  Wed May 21 11:19:10 2014 liron_b
// Last update Sun Jun 15 18:42:23 2014 virgile prideaux
//

#ifndef		INVALID_HH_
# define	INVALID_HH_

#include	"Line.hh"
#include	"Case.hh"

class	Invalid : public Line, public Case
{
public:
  static Invalid	instance;

private:
  Invalid&	operator=(const Invalid&);
  Invalid(const Invalid&);

public:
  Invalid();
  ~Invalid();

  operator bool() const;
};

#endif	/* !INVALID_HH_ */
