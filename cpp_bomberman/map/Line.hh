//
// Line.hh for bomberman in /home/liron_b/rendu/cpp_bomberman/map
// 
// Made by liron_b
// Login   <liron_b@epitech.net>
// 
// Started on  Tue May 13 15:01:35 2014 liron_b
// Last update Sun Jun 15 22:43:14 2014 liron_b
//

#ifndef		LINE_HH_
# define	LINE_HH_

#include	<vector>
#include	"Case.hh"

class	Line
{
private:
  std::vector<Case*>	_cases;

  Line(const Line&);
  Line&			operator=(const Line&);

public:
  Line();
  virtual	~Line();

  bool		init(const std::vector<int>& line, int x);

  Case&		operator[](int idx);
  virtual	operator bool() const;
  int		size() const;
};

#endif /* !LINE_HH_ */
