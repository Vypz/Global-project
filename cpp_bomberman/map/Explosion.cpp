//
// Bomb.cpp for  in /home/ouroub_a/rendu/cpp_bomberman/map
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Wed May 14 19:18:55 2014 amina ourouba
// Last update Sun Jun 15 18:41:13 2014 virgile prideaux
//

#include	"Explosion.hh"
#include	"Plan.hh"
#include	"Bonus.hh"
#include	"Engine.hh"
#include	"Wall.hh"

glm::vec3	tab[] =
  {
    glm::vec3(4, 6, 0),	// SCALE
    glm::vec3(70, 0, 0)	// ROTATION
  };

Explosion::Explosion(int x, int y, Map& map)
  : AElement(AElement::EXPLOSION, x, y), _curFrame(0)
{
  Wall*		wall;
  Bonus*	bonus;

  wall = dynamic_cast<Wall*>(map[this->_posX][this->_posY].getElement(AElement::WALL));
  if (wall && wall->isDestroyable())
  {
    map[this->_posX][this->_posY].removeElement(wall);
    if (wall->getBonType() != Bonus::NONE)
    {
      bonus = new Bonus(this->_posX, this->_posY, wall->getBonType());
      map[this->_posX][this->_posY].addElement(bonus);
      bonus->setPosition(glm::vec3(this->_posY * 80 - map.getWidth(), 0,
				   this->_posX * 80 - map.getHeight()));
      bonus->setRotation(glm::vec3(0, 0, -90));
      bonus->setScale(glm::vec3(1, 1, 1));
    }
    delete wall;
  }

  this->setScale(tab[0]);
  this->setRotation(tab[1]);
}

Explosion::~Explosion()
{}

bool	Explosion::walkThrough() const
{
  return (true);
}

void	Explosion::update(Engine& e)
{
  if (this->_curFrame >= e.getExplosion().getNbFrame())
    {
      e.getMap()[this->_posX][this->_posY].removeElement(this);
      delete this;
    }
}

int	Explosion::getFrame(gdl::Clock& clock)
{
  float	curFrame;

  curFrame = this->_curFrame;
  this->_curFrame += clock.getElapsed() * 30;
  return (static_cast<int>(curFrame));
}
