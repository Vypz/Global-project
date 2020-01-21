//
// Color.hh for bomberman in /home/liron_b/rendu/cpp_bomberman/map
// 
// Made by liron_b
// Login   <liron_b@epitech.net>
// 
// Started on  Mon May 19 11:48:24 2014 liron_b
// Last update Sat May 24 14:43:45 2014 liron_b
//

#ifndef		COLOR_HH_
# define	COLOR_HH_

# include	<stdint.h>

class	Color
{
public:
  static const char	ARGB	= 0;
  static const char	RGB	= 1;
  static const char	BE	= 0;
  static const char	LE	= 0x80;

private:
  uint32_t	_color;

public:
  Color(uint32_t value);
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF, char type = 0);
  Color(const Color& src);
  ~Color();
  Color&	operator=(const Color& src);

  uint8_t	red() const;
  uint8_t	green() const;
  uint8_t	blue() const;
  uint8_t	alpha() const;
  uint32_t	value() const;

  bool		operator==(const Color& src) const;
};

#endif /* !COLOR_HH_ */
