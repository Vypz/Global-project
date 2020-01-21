//
// Map.hh for bomberman in /home/liron_b/rendu/cpp_bomberman/map
// 
// Made by liron_b
// Login   <liron_b@epitech.net>
// 
// Started on  Tue May 13 15:01:28 2014 liron_b
// Last update Sun Jun 15 17:31:21 2014 virgile prideaux
//

#ifndef		MAP_HH_
# define	MAP_HH_

#include	<vector>
#include	<string>
#include	"Line.hh"

class	Map
{
private:
  std::vector<Line*>	_lines;
  int			_height;
  int			_width;

  Map(const Map&);
  Map&			operator=(const Map&);

public:
  Map();
  ~Map();

  bool		init(const std::string& mapFilename);
  bool		init(const char* mapFilename);

  Line&		operator[](int idx);
  int		size() const;
  int		getHeight() const;
  int		getWidth() const;
};

#endif /* !MAP_HH_ */
