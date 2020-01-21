//
// Color.cpp for bomberman in /home/liron_b/rendu/cpp_bomberman/map
// 
// Made by liron_b
// Login   <liron_b@epitech.net>
// 
// Started on  Mon May 19 11:54:47 2014 liron_b
// Last update Thu Jun 12 11:09:05 2014 liron_b
//

#include	"Color.hh"

Color::Color(uint32_t value)
  : _color(value)
{}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a, char type)
{
  if (type & Color::RGB)
    a = 0;
  if ((type & Color::LE) == 0)
    this->_color = a << 24 | r << 16 | g << 8 | b;
  else
    {
      this->_color = b << 24 | g << 16 | r << 8 | a;
      if (type & Color::RGB)
	this->_color >>= 8;
    }
}

Color::Color(const Color& src)
  : _color(src._color)
{}

Color::~Color()
{}

Color&	Color::operator=(const Color& src)
{
  this->_color = src._color;
  return (*this);
}


uint8_t	Color::red() const
{
  return (this->_color >> 24);
}

uint8_t	Color::green() const
{
  return ((this->_color >> 16) & 0xFF);
}

uint8_t	Color::blue() const
{
  return ((this->_color >> 8) & 0xFF);
}

uint8_t	Color::alpha() const
{
  return (this->_color & 0xFF);
}

uint32_t	Color::value() const
{
  return (this->_color);
}


bool	Color::operator==(const Color& src) const
{
  return (this->_color == src._color);
}
