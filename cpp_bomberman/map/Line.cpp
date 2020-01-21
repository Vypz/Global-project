//
// Line.cpp for bomberman in /home/liron_b/rendu/cpp_bomberman/map
// 
// Made by liron_b
// Login   <liron_b@epitech.net>
// 
// Started on  Mon May 19 15:48:18 2014 liron_b
// Last update Sun Jun 15 22:41:59 2014 liron_b
//

#include	"Line.hh"
#include	"Invalid.hh"

Line::Line()
{}

Line::~Line()
{
  for (std::vector<Case*>::iterator it = this->_cases.begin();
       it != this->_cases.end(); ++it)
    delete *it;
}


bool	Line::init(const std::vector<int>& line, int x)
{
  this->_cases.resize(line.size());
  for (unsigned int i = 0; i < line.size(); i++)
    {
      this->_cases[i] = new Case;
      if (this->_cases[i]->init(line[i], x, i + 1) == false)
	return (false);
    }
  return (true);
}

Case&	Line::operator[](int idx)
{
  if (idx < 0 || idx >= static_cast<int>(this->_cases.size()))
    return (Invalid::instance);
  return (*(this->_cases[idx]));
}

Line::operator bool() const
{
  return (true);
}

int	Line::size() const
{
  return (this->_cases.size());
}
