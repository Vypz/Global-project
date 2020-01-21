//
// Character.cpp for  in /home/ouroub_a/rendu/cpp_bomberman/map
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Wed May 14 19:18:38 2014 amina ourouba
// Last update Sun Jun 15 20:43:00 2014 virgile prideaux
//

#include	"Character.hh"
#include	"Map.hh"
#include	"Bomb.hh"
#include	"AI.hh"
#include	<iostream>
#include	"SDL.h"

glm::vec3	charac[] =
  {
    glm::vec3(1, 1, 1),
    glm::vec3(0, 0, 0)
  };

unsigned int	keymap[] =
  {
    SDLK_z,
    SDLK_KP_8,
    SDLK_q,
    SDLK_KP_4,
    SDLK_s,
    SDLK_KP_5,
    SDLK_d,
    SDLK_KP_6,
    SDLK_SPACE,
    SDLK_KP_ENTER
  };

Character::Character(int x, int y, bool isAI, int player)
  : AElement(AElement::CHARACTER, x, y), _shiftX(0), _shiftY(0), _anim(0), _speed(5), _isAI(isAI), _bombScope(Bomb::DEFAULT_SCOPE), _bombMax(1), _posedBomb(0), _player(player), _hp(3), _time(0)
{
  this->setScale(charac[0]);
  this->setRotation(charac[1]);

  this->_hitbox.setTexture("./LibBomberman_linux_x64/assets/hitbox.tga");
  this->_hitbox.setGeometry(40, 40, 40);
  this->_hitbox.setScale(glm::vec3(2, 2, 0));
  this->_hitbox.setRotation(glm::vec3(-90, 0, 0));

  this->_healthbar.setScale(glm::vec3(3, 3, 0));
  this->_healthbar.setRotation(glm::vec3(0, 0, -90));
}

Character::~Character()
{}

int	Character::getHealthPoint() const
{
  return (this->_hp);
}

void	Character::displayHitbox(gdl::BasicShader &shader)
{
  this->_hitbox.setPosition(glm::vec3(this->_position.x, this->_position.y - 70, this->_position.z));
  this->_hitbox.draw(this->_hitbox.getTransform(), shader);
}

bool	Character::walkThrough() const
{
  return (true);
}

const glm::mat4&	Character::getHBTransform()
{
  this->_healthbar.setPosition(glm::vec3(this->_position.x, this->_position.y + 150, this->_position.z));
  return (this->_healthbar.getTransform());
}

int	Character::getAnimation() const
{
  return (this->_anim);
}

void	Character::move(float x, float y, Engine& e)
{
  float	newShiftX;
  float	newShiftY;

  newShiftX = this->_shiftX + x * this->_speed * e.getClock().getElapsed();
  newShiftY = this->_shiftY + y * this->_speed * e.getClock().getElapsed();
  if (e.getMap()[this->_posX + x][this->_posY + y].walkThrough() == false && (newShiftX * x >= 0.3 || newShiftY * y >= 0.3))
    return ;
  if (-0.5 < newShiftX && newShiftX < 0.5)
    x = 0;
  else if (x != 0)
    newShiftX -= x;
  if (-0.5 < newShiftY && newShiftY < 0.5)
    y = 0;
  else if (y != 0)
    newShiftY -= y;
  if ((x == 0 && y == 0) || this->setPos(this->_posX + x, this->_posY + y, e) == true)
    {
      this->_shiftX = newShiftX;
      this->_shiftY = newShiftY;
    }
}

float	Character::getSpeed() const
{
  return (this->_speed);
}

void	Character::setAnimation(int anim)
{
  this->_anim = anim;
}

void	Character::updatePosition(Map& map)
{
  this->_position = glm::vec3(80 * (static_cast<float>(this->_posY) + this->_shiftY) - map.getWidth(), 0,
			      80 * (static_cast<float>(this->_posX) + this->_shiftX) - map.getHeight());
  this->updateTransform();
}

bool		Character::setPos(int x, int y, Engine& e)
{
  AElement*	elem;

  if (e.getMap()[x][y].walkThrough())
    {
      e.getMap()[this->_posX][this->_posY].removeElement(this);
      this->_posX = x;
      this->_posY = y;
      e.getMap()[this->_posX][this->_posY].addElement(this);
      if ((elem = e.getMap()[this->_posX][this->_posY].getElement(AElement::BONUS)) &&
	  dynamic_cast<Bonus *>(elem)->getBonType() != Bonus::NONE)
	{
	  e.getAudiomanager().play(Audio::POWERUP);
	  if (dynamic_cast<Bonus *>(elem)->getBonType() == Bonus::SCOPE)
	    this->_bombScope++;
	  else if (dynamic_cast<Bonus *>(elem)->getBonType() == Bonus::SPEED)
	    this->_speed += 0.5;
	  else if (dynamic_cast<Bonus *>(elem)->getBonType() == Bonus::ONE_MORE_BOMB)
	    this->_bombMax++;
	  e.getMap()[this->_posX][this->_posY].removeElement(elem);
	}
      this->_hasMoved = true;
      return (true);
    }
  return (false);
}

void	Character::_putBomb(Engine& e)
{
  if (e.getMap()[this->_posX][this->_posY].hasElement(AElement::BOMB))
    return ;
  e.getAudiomanager().play(Audio::BOMBPLANT);
  this->_posedBomb += 1;
  e.getMap()[this->_posX][this->_posY].addElement(new Bomb(this->_posX, this->_posY, this->_bombScope, Bomb::DEFAULT_TIME, this));
  e.getMap()[this->_posX][this->_posY].getElement(AElement::BOMB)->
    setPosition(glm::vec3(this->_posY * 80 - e.getMap().getWidth(), 0,
			  this->_posX * 80 - e.getMap().getHeight()));
}

void	Character::update(Engine &e)
{
  float	x = 0;
  float	y = 0;
  float	angle;

  if (this->_hasMoved)
    return ;
  if (this->_isAI)
    {
      dynamic_cast<AI*>(this)->sendInput(x, y, e.getMap());
      if (dynamic_cast<AI*>(this)->getBomb() == true)
	{
	  this->_putBomb(e);
	  dynamic_cast<AI*>(this)->setBomb(false);
	}
    }
  else
    {
      if (e.getInput().getKey(keymap[this->_player + 2]))
	y += -1;
      if (e.getInput().getKey(keymap[this->_player]))
	x += -1;
      if (e.getInput().getKey(keymap[this->_player + 4]))
	x += 1;
      if (e.getInput().getKey(keymap[this->_player + 6]))
	y += 1;
      if (e.getInput().getKey(keymap[this->_player + 8]) && this->_canPutBomb() == true)
	this->_putBomb(e);
    }
  if (x == 0 && y == 0 && this->_anim == 1)
    this->_anim = 0;
  if ((x != 0 || y != 0) && this->_anim == 0)
    this->_anim = 1;
  this->move(x, y, e);
  this->updatePosition(e.getMap());
  if (x == -1 && y == 0)
    angle = 180.0f;
  else
    angle = 2.0f * atan(y / (x + sqrtf(x * x + y * y))) * 180.0f / M_PI;
  if (x != 0 || y != 0)
    this->setRotation(glm::vec3(0, angle, 0));

  if (this->_time > 0)
    this->_time -= e.getClock().getElapsed();
  if (e.getMap()[this->_posX][this->_posY].hasElement(AElement::EXPLOSION) && this->_time <= 0)
    {
      e.getAudiomanager().play(Audio::PLAYERHIT);
      this->_hp--;
      if (this->_hp == 0)
	{
	  if (this->_isAI == false)
	    {
	      if (this->_player == 0)
		{
		  e.setPlayer1(e.getPlayer2());
		  e.setPlayer2(NULL);
		}
	      else
		e.setPlayer2(NULL);
	      e.decNbPlayers();
	    }
	  else
	    e.decNbAI();
	  (e.getMap()[this->_posX][this->_posY].removeElement(this));
	  delete this;
	  return ;
	}
      this->_time = 2;
    }
}

int	Character::getBombScope() const
{
  return (this->_bombScope);
}

void	Character::setSpeed(float speed)
{
  this->_speed += speed;
}

bool	Character::_canPutBomb() const
{
  return (this->_posedBomb < this->_bombMax);
}

void	Character::decBomb()
{
  this->_posedBomb -= 1;
}

void	Character::setPlayerNum(int num)
{
  this->_player = num;
}

void	Character::resetHasMoved()
{
  this->_hasMoved = false;
}
