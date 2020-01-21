//
// Bomb.cpp for  in /home/ouroub_a/rendu/cpp_bomberman/map
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Wed May 14 19:18:55 2014 amina ourouba
// Last update Sun Jun 15 18:26:00 2014 virgile prideaux
//

#include	<iostream>
#include	<time.h>
#include	"Bomb.hh"
#include	"Bonus.hh"
#include	"Engine.hh"
#include	"Map.hh"
#include	"Wall.hh"
#include	"Explosion.hh"

glm::vec3	bomb[] =
  {
    glm::vec3(1, 1, 1),		// SCALE
    glm::vec3(0, -90, 0)	// ROTATION
  };

Bomb::Bomb(int x, int y, int scope, float time, Character *owner)
  : AElement(AElement::BOMB, x, y), _time(time), _elapsed(0), _scope(scope), _owner(owner)
{
  this->setScale(bomb[0]);
  this->setRotation(bomb[1]);
}

Bomb::~Bomb()
{
}

float Bomb::getTime() const
{
  return (this->_time);
}

void		Bomb::_putExplosion(Map& map, int x, int y, bool& ignore)
{
  AElement*	explosion;

  if (ignore)
    return ;
  if (!map[x][y] || map[x][y].hasElement(AElement::WALL))
  {
    ignore = true;
    if (map[x][y] && dynamic_cast<Wall*>(map[x][y].getElement(AElement::WALL))->isDestroyable() == false)
      return ;
  }
  else if (!map[x][y] || map[x][y].hasElement(AElement::BOMB))
    dynamic_cast<Bomb*>(map[x][y].getElement(AElement::BOMB))->_time = 0;
  if (map[x][y] && (explosion = map[x][y].getElement(AElement::EXPLOSION)))
  {
    map[x][y].removeElement(explosion);
    delete explosion;
  }
  explosion = new Explosion(x, y, map);
  map[x][y].addElement(explosion);
  explosion->setPosition(glm::vec3(y * 80 - map.getWidth() - 30, 0,
				   x * 80 - map.getHeight()));
}

void	Bomb::update(Engine& e)
{
  bool	ignoreLeft = false;
  bool	ignoreRight = false;
  bool	ignoreUp = false;
  bool	ignoreDown = false;
  int	x;
  int	y;

  x = this->_posX;
  y = this->_posY;
  this->_time -= e.getClock().getElapsed();
  if (this->_time <= 0)
    {
      e.getAudiomanager().play(Audio::EXPLOSION);
      this->_owner->decBomb();
      this->_putExplosion(e.getMap(), x, y, ignoreLeft);
      for (int range = 1; range <= this->_scope; range++)
	{
	  this->_putExplosion(e.getMap(), x - range, y, ignoreLeft);
	  this->_putExplosion(e.getMap(), x + range, y, ignoreRight);
	  this->_putExplosion(e.getMap(), x, y - range, ignoreUp);
	  this->_putExplosion(e.getMap(), x, y + range, ignoreDown);
	}
      e.getMap()[this->_posX][this->_posY].removeElement(this);
      delete this;
    }
}

int	Bomb::getScope() const
{
  return (this->_scope);
}

bool	Bomb::walkThrough() const
{
  return (false);
}
