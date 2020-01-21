//
// AI.cpp for  in /home/mar_j/rendu/cpp_bomberman/map
// 
// Made by julien martini
// Login   <mar_j@epitech.net>
// 
// Started on  Wed Jun  4 15:21:38 2014 julien martini
// Last update Sun Jun 15 18:59:52 2014 virgile prideaux
//

#include "AI.hh"

AI::AI(int x, int y)
  : Character(x, y, true), _x(0), _y(0), _bomb(false), _init(false)
{}

AI::~AI()
{}

void	AI::initMap(Map& map)
{
  int	i;

  i = 0;
  this->_map.resize(map.size());
  for (std::vector<Line>::iterator it = _map.begin(); it != _map.end(); ++it)
    (*it).resize(map[i++].size(), static_cast<int>(AI::NOTHING));
}

void					AI::refreshMap(Map& map)
{
  std::list<AElement*>::iterator	it;
  std::map<AElement::Type, AI::Type>	type;

  type[AElement::NOTHING] = AI::NOTHING;
  type[AElement::BOMB] = AI::BOMB;
  type[AElement::CHARACTER] = AI::PLAYER;
  type[AElement::BONUS] = AI::BONUS;
  type[AElement::WALL] = AI::WALL;
  type[AElement::EXPLOSION] = AI::EXPLODE;
 
  for (int y = 0; y != static_cast<int>(this->_map.size()); y += 1)
    for (int x = 0; x != static_cast<int>(this->_map[y].size()); x += 1)
      this->_map[y][x] = AI::NOTHING;

  for (int y = 0; y != static_cast<int>(this->_map.size()); y += 1)
    for (int x = 0; x != static_cast<int>(this->_map[y].size()); x += 1)
      for (it = map[y][x].begin(); it != map[y][x].end(); ++it)
	{
	  this->_map[y][x] |= type[(*it)->getType()];
	  if ((*it)->getType() == AElement::BOMB)
	    {
	      for (int i = 0; i <= dynamic_cast<Bomb*>(*it)->getScope(); i += 1)
		{ 
		  if ((x - i) > 0)
		    this->_map[y][x - i] |= AI::EXPLODE;
		  if ((x + i) < static_cast<int>(_map[y].size()))
		    this->_map[y][x + i] |= AI::EXPLODE;
		  if ((y - i) > 0)
		    this->_map[y - i][x] |= AI::EXPLODE;
		  if ((y + i) < static_cast<int>(_map.size()))
		    this->_map[y + i][x] |= AI::EXPLODE;
		}
	    }
	  else if ((*it)->getType() == AElement::WALL)
	    {
	      if (dynamic_cast<Wall*>(*it)->isDestroyable() == true)
		this->_map[y][x] = AI::DBLOCK;
	      else
		this->_map[y][x] = AI::WALL;
	    }
	}
  _map[this->_posX][this->_posY] &= ~AI::PLAYER;
}

int	AI::findSafeArea(float x, float y, int iter)
{
  int	up;
  int	down;
  int	left;
  int	right;

  if (iter >= MAX_ITER ||
      ((this->_map[x][y] & AI::BOMB) && iter != 0) ||
      (this->_map[x][y] & AI::WALL) ||
      (this->_map[x][y] & AI::DBLOCK))
    return (MAX_ITER + 1);
  else if (!(this->_map[x][y] & AI::EXPLODE) &&
	   !(this->_map[x][y] & AI::BOMB))
    return (0);
  else
    {
      up = findSafeArea(x - 1, y, iter + 1);
      right = findSafeArea(x, y + 1, iter + 1);
      down = findSafeArea(x + 1, y, iter + 1);
      left = findSafeArea(x, y - 1, iter + 1);
      if (up <= down && up <= left && up <= right)
	{
	  this->_x = -1;
	  this->_y = 0;
	  return (up + 1);
	}
      if (right <= up && right <= down && right <= left)
	{
	  this->_x = 0;
	  this->_y = 1;
	  return (right + 1);
	}
      if (down <= up && down <= left && down <= right)
	{
	  this->_x = 1;
	  this->_y = 0;
	  return (down + 1);
	}
      if (left <= up && left <= right && left <= down)
	{
	  this->_x = 0;
	  this->_y = -1;
	  return (left + 1);
	}
    }
  return (MAX_ITER + 1);
}

int	AI::searchObject(int x, int y, int iter, AI::Type object)
{
  int	up;
  int	right;
  int	left;
  int	down;

  if (iter >= MAX_ITER ||
      (this->_map[x][y] & AI::BOMB) ||
      (this->_map[x][y] & AI::WALL) ||
      (this->_map[x][y] & AI::EXPLODE))
    return (MAX_ITER + 1);
  else if ((this->_map[x][y] & object))
      return (0);
  else
    {
      up = searchObject(x - 1, y, iter + 1, object);
      right = searchObject(x, y + 1, iter + 1, object);
      down = searchObject(x + 1, y, iter + 1, object);
      left = searchObject(x, y - 1, iter + 1, object);
      if (up <= down && up <= left && up <= right)
	{
	  this->_x = -1;
	  this->_y = 0;
	  return (up + 1);
	}
      if (right <= up && right <= down && right <= left)
	{
	  this->_x = 0;
	  this->_y = 1;
	  return (right + 1);
	}
      if (down <= up && down <= left && down <= right)
	{
	  this->_x = 1;
	  this->_y = 0;
	  return (down + 1);
	}
      if (left <= up && left <= right && left <= down)
	{
	  this->_x = 0;
	  this->_y = -1;
	  return (left + 1);
	}
    }
  return (MAX_ITER + 1);
}

bool	AI::isDangerous()
{
  int	i;

  for (i = 0; i <= this->getBombScope(); i++)
    { 
      if ((_map[this->_posX + i][this->_posY] & AI::WALL) ||
	  (_map[this->_posX + i][this->_posY] & AI::BOMB))
	i = this->getBombScope() + 1;
      else if ((_map[this->_posX + i][this->_posY] & AI::EXPLODE))
	return (false);	
    }
  for (i = 0; i <= this->getBombScope(); i++)
    { 
      if ((_map[this->_posX][this->_posY - i] & AI::WALL) ||
	  (_map[this->_posX][this->_posY - i] & AI::BOMB))
	i = this->getBombScope() + 1;
      else if ((_map[this->_posX][this->_posY - i] & AI::EXPLODE))
	return (false);
    }
  for (i = 0; i <= this->getBombScope(); i++)
    { 
      if ((_map[this->_posX - i][this->_posY] & AI::WALL) ||
	  (_map[this->_posX - i][this->_posY] & AI::BOMB))
	i = this->getBombScope() + 1;
      else if ((_map[this->_posX - i][this->_posY] & AI::EXPLODE))
	return (false);	
    }
  for (i = 0; i <= this->getBombScope(); i++)
    { 
      if ((_map[this->_posX][this->_posY + i] & AI::WALL) ||
	  (_map[this->_posX][this->_posY + i] & AI::BOMB))
	i = this->getBombScope() + 1;
      else if ((_map[this->_posX][this->_posY - i] & AI::EXPLODE))
	return (false);	
    }
  return (true);
}

bool	AI::iCanBomb()
{
  int	i;
  bool	ret;

  ret = false;
  for (i = 0; i <= this->getBombScope() && ret != true; i++)
    { 
      if ((_map[this->_posX + i][this->_posY] & AI::DBLOCK) ||
	  (_map[this->_posX + i][this->_posY] & AI::PLAYER))
	ret = true;
      else if ((_map[this->_posX + i][this->_posY] & AI::WALL) ||
	       (_map[this->_posX + i][this->_posY] & AI::BOMB))
	i = this->getBombScope() + 1;
    }
  for (i = 0; i <= this->getBombScope() && ret != true; i++)
    { 
      if ((_map[this->_posX - i][this->_posY] & AI::DBLOCK) ||
	  (_map[this->_posX - i][this->_posY] & AI::PLAYER))
	ret = true;
      else if ((_map[this->_posX - i][this->_posY] & AI::WALL) ||
	       (_map[this->_posX - i][this->_posY] & AI::BOMB))
	i = this->getBombScope() + 1;
    }
  for (i = 0; i <= this->getBombScope() && ret != true; i++)
    { 
      if ((_map[this->_posX][this->_posY + i] & AI::DBLOCK) ||
	  (_map[this->_posX][this->_posY + i] & AI::PLAYER))
       	ret = true;
      else if ((_map[this->_posX][this->_posY + i] & AI::WALL) ||
	       (_map[this->_posX][this->_posY + i] & AI::BOMB))
	i = this->getBombScope() + 1;
    }
  for (i = 0; i <= this->getBombScope() && ret != true; i++)
    { 
      if ((_map[this->_posX][this->_posY - i] & AI::DBLOCK) ||
	  (_map[this->_posX][this->_posY - i] & AI::PLAYER))
	ret = true;
      else if ((_map[this->_posX][this->_posY - i] & AI::WALL) ||
	       (_map[this->_posX][this->_posY - i] & AI::BOMB))
	i = this->getBombScope() + 1;
    }
  return (ret);
}

void	AI::randomMove()
{
  int	pileFace;

  srand(getuid() * getgid() * getpid() * time(0));
  pileFace = (rand() % 4);
  if (pileFace == 0 &&
      !(_map[this->_posX + 1][this->_posY] & AI::WALL) &&
      !(_map[this->_posX + 1][this->_posY] & AI::EXPLODE))
    this->_x = 1;
  if (pileFace == 1 &&
      !(_map[this->_posX][this->_posY - 1] & AI::WALL) &&
      !(_map[this->_posX][this->_posY - 1] & AI::EXPLODE))
    this->_y = -1;
  if (pileFace == 2 &&
      !(_map[this->_posX - 1][this->_posY] & AI::WALL) &&
      !(_map[this->_posX - 1][this->_posY] & AI::EXPLODE))
      this->_x = -1;
  if (pileFace == 3 &&
      !(_map[this->_posX][this->_posY + 1] & AI::WALL) &&
      !(_map[this->_posX][this->_posY + 1] & AI::EXPLODE))
    this->_y = 1;
}

void	AI::scan()
{
  this->_x = 0;
  this->_y = 0;
  if ((_map[this->_posX][this->_posY] & AI::EXPLODE) ||
      (_map[this->_posX][this->_posY] & AI::BOMB))
    {
      if (this->findSafeArea(this->_posX, this->_posY, 0) > MAX_ITER)
	randomMove();
    }
  else
    {
      if (this->searchObject(this->_posX, this->_posY, 0, AI::BONUS) > MAX_ITER || this->_map[this->_posX + this->_x][this->_posY + this->_y] == AI::DBLOCK)
	{
	  this->_x = 0;
	  this->_y = 0;
	  if (isDangerous() == true &&
	      iCanBomb() == true && this->_canPutBomb() == true)
	    this->_bomb = true;
	  else
	    {
	      if (this->searchObject(this->_posX, this->_posY, 0, AI::PLAYER) > MAX_ITER)
		{
		  this->_x = 0;
		  this->_y = 0;
		  if (this->searchObject(this->_posX, this->_posY, 0, AI::DBLOCK) > MAX_ITER)
		    {
		      
		      this->_x = 0;
		      this->_y = 0;
		      randomMove();
		    }
		}
	    }
	  if (this->_map[this->_posX + this->_x][this->_posY + this->_y] == AI::DBLOCK)
	    {
	      this->_x = 0;
	      this->_y = 0;
	    }
	}
    }
}

void	AI::sendInput(float& x, float& y, Map &map)
{
  this->_x = 0;
  this->_y = 0;
  if (this->_init == false)
    {
      this->_init = true;
      this->initMap(map);
    }
  this->refreshMap(map);
  this->scan();
  x = this->_x;
  y = this->_y;
}

bool	AI::getBomb() const
{
  return (this->_bomb);
}

void	AI::setBomb(bool set)
{
  this->_bomb = set;
}
