//
// Wall.cpp for  in /home/ouroub_a/C++/Bomberman/map
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Tue May 20 09:32:05 2014 amina ourouba
// Last update Sun Jun 15 18:43:40 2014 virgile prideaux
//

#include	"Wall.hh"
#include	"Bonus.hh"

glm::vec3	wall[] =
  {
    glm::vec3(1, 1, 1),
    glm::vec3(0, 0, 0)
  };

Wall::Wall(int x, int y, bool destroyable)
  : AElement(AElement::WALL, x, y), _destroyable(destroyable)
{
  int	r;

  if (destroyable)
    {
      r = random();
      if (r % 10 == 0)
	{
	  r /= 2;
	  if (r % 4 == 1)
	    this->_hiddenBonus = Bonus::SPEED;
	  else if (r % 4 == 2)
	    this->_hiddenBonus = Bonus::ONE_MORE_BOMB;
	  else if (r % 4 == 3)
	    this->_hiddenBonus = Bonus::SCOPE;
	  else
	    this->_hiddenBonus = Bonus::NONE;
	}
      else
	this->_hiddenBonus = Bonus::NONE;
    }
  this->setScale(wall[0]);
  this->setRotation(wall[1]);
}

Wall::~Wall()
{}

bool	Wall::isDestroyable() const
{
  return (_destroyable);
}

bool	Wall::walkThrough() const
{
  return (false);
}

Bonus::BonType	Wall::getBonType() const
{
  return (_hiddenBonus);
}
