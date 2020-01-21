//
// Bonus.cpp for  in /home/ouroub_a/rendu/cpp_bomberman/map
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Tue May 27 08:03:23 2014 amina ourouba
// Last update Sun Jun 15 18:27:37 2014 virgile prideaux
//

#include	"Bonus.hh"

Bonus::Bonus(int x, int y, BonType type)
  : AElement(AElement::BONUS, x, y), _bonType(type)
{}

Bonus::~Bonus()
{}

bool	Bonus::walkThrough() const
{
  return (true);
}

Bonus::BonType	Bonus::getBonType() const
{
  return (this->_bonType);
}
