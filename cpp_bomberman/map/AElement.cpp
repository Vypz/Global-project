//
// AElement.cpp for  in /home/ouroub_a/rendu/cpp_bomberman/map
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Tue May 20 11:02:21 2014 amina ourouba
// Last update Sun Jun 15 18:58:53 2014 virgile prideaux
//

#include	"AElement.hh"
#include	"Map.hh"

AElement::AElement(AElement::Type type, int x, int y)
  : _posX(x), _posY(y), _type(type)
{}

AElement::~AElement()
{}

int	AElement::getXPos() const
{
  return (this->_posX);
}

int	AElement::getYPos() const
{
  return (this->_posY);
}

bool	AElement::setPos(int, int, Map&)
{
  return (false);
}

AElement::Type	AElement::getType() const
{
  return (this->_type);
}

void	AElement::setType(AElement::Type type)
{
  this->_type = type;
}

void	AElement::update(Engine&)
{}

int	AElement::getAnimation() const
{
  return (0);
}
