//
// Case.cpp for bomberman in /home/liron_b/rendu/cpp_bomberman/map
// 
// Made by liron_b
// Login   <liron_b@epitech.net>
// 
// Started on  Mon May 19 16:14:49 2014 liron_b
// Last update Sun Jun 15 18:35:22 2014 virgile prideaux
//

#include	<iostream>
#include	<iomanip>
#include	<algorithm>
#include	"Case.hh"
#include	"AElement.hh"
#include	"Wall.hh"
#include	"Explosion.hh"

Case::Case()
{}

Case::~Case()
{
  for (std::list<AElement*>::iterator it = this->_content.begin();
       it != this->_content.end(); ++it)
    delete *it;
}


Case::operator bool() const
{
  return (true);
}


bool	Case::init(unsigned int rgbType, int x, int y)
{
  switch (rgbType)
    {
    case AElement::WALL:
      this->_content.push_back(new Wall(x, y, false));
      break ;

    case AElement::DESTRUCTIBLE_WALL:
      this->_content.push_back(new Wall(x, y, true));
      break ;

    case AElement::NOTHING:
      break ;

    default:
      std::cerr << "Unknown color 0x" << std::hex << std::uppercase << rgbType << std::nouppercase << std::dec << " in bitmap" << std::endl;
      return (false);
    }
  return (true);
}


bool	Case::_cantWalkThrough(const AElement* element)
{
  return (!element->walkThrough());
}
// Mettre en statique dans la classe appropriée (probablement AElement)

bool	Case::walkThrough() const
{
  if (this->_content.empty())
    return (true);
  return (std::find_if(this->_content.begin(), this->_content.end(), &Case::_cantWalkThrough) == this->_content.end());
}

bool	Case::hasElement(const AElement::Type type) const
{
  if (type == AElement::NOTHING && this->_content.empty())
    return (true);
  for (std::list<AElement*>::const_iterator it = this->_content.begin();
       it != this->_content.end(); ++it)
    if ((*it)->getType() == type)
      return (true);
  return (false);
}

AElement*	Case::getElement(const AElement::Type type) const
{
  if (type == AElement::NOTHING && this->_content.empty())
    return (NULL);
  for (std::list<AElement*>::const_iterator it = this->_content.begin();
       it != this->_content.end(); ++it)
    if ((*it)->getType() == type)
      return (*it);
  return (NULL);
}

void	Case::addElement(AElement* element)
{
  this->_content.push_front(element);
}

void	Case::removeElement(AElement* element)
{
  std::list<AElement*>::iterator	it;

  it = std::find(this->_content.begin(), this->_content.end(), element);
  if (it == this->_content.end())
    return ;
  this->_nextIt = this->_content.erase(it);
}

std::list<AElement*>::iterator	Case::begin()
{
  this->_nextIt = static_cast<std::list<AElement*>::iterator>(0);
  return (this->_content.begin());
}

std::list<AElement*>::iterator	Case::end()
{
  return (this->_content.end());
}

void	Case::nextIterator(std::list<AElement*>::iterator& it)
{
  if (this->_nextIt != static_cast<std::list<AElement*>::iterator>(0))
    it = this->_nextIt;
  else
    ++it;
  this->_nextIt = static_cast<std::list<AElement*>::iterator>(0);
}
