//
// Map.cpp for bomberman in /home/liron_b/rendu/cpp_bomberman/map
// 
// Made by liron_b
// Login   <liron_b@epitech.net>
// 
// Started on  Mon May 19 11:20:27 2014 liron_b
// Last update Sun Jun 15 22:42:17 2014 liron_b
//

#include	<stdexcept>
#include	"Map.hh"
#include	"Bitmap.hh"
#include	"Invalid.hh"
#include	<iostream>

Map::Map()
{}

Map::~Map()
{
  for (std::vector<Line*>::iterator it = this->_lines.begin();
       it != this->_lines.end(); ++it)
    delete *it;
}

bool			Map::init(const std::string& mapFilename)
{
  Bitmap		bmp;
  std::vector<int>	line;

  if (bmp.openBitmap(mapFilename) == false)
    return (false);

  this->_height = bmp.getHeight();
  this->_width = bmp.getWidth();

  this->_lines.resize(bmp.getHeight());
  line.resize(bmp.getWidth());
  for (int i = 0; i < bmp.getWidth() * bmp.getHeight(); )
    {
      do
	{
	  line[i % bmp.getWidth()] = bmp[i].value();
	  i++;
	} while (i % bmp.getWidth() != 0);
      this->_lines[i / bmp.getWidth() - 1] = new Line;
      if (this->_lines[i / bmp.getWidth() - 1]->init(line, i / bmp.getWidth()) == false)
	return (false);
    }
  return (true);
}

bool	Map::init(const char* mapFilename)
{
  return (this->init(std::string(mapFilename)));
}

Line&	Map::operator[](int idx)
{
  if (idx < 0 || idx >= static_cast<int>(this->_lines.size()))
    return (Invalid::instance);
  return (*(this->_lines[idx]));
}

int	Map::size() const
{
  return (this->_lines.size());
}

int	Map::getHeight() const
{
  return (this->_height);
}

int	Map::getWidth() const
{
  return (this->_width);
}
