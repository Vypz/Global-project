//
// Coord3.cpp for bomberman in /home/pridea_v/rendu/cpp_bomberman
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Sun Jun  1 01:23:49 2014 virgile prideaux
// Last update Sun Jun 15 18:19:26 2014 virgile prideaux
//

#include	"Coord3.hh"

extern glm::vec3	rotationvec[];

Coord3::Coord3(const glm::vec3& p, const glm::vec3& r, const glm::vec3& s)
  : _position(p), _rotation(r), _scale(s)
{}

Coord3::Coord3()
{}

Coord3::~Coord3()
{}

void		Coord3::updateTransform()
{
  glm::mat4	transform(1);

  transform = glm::translate(transform, this->_position);
  transform = glm::rotate(transform, this->_rotation.x, rotationvec[0]);
  transform = glm::rotate(transform, this->_rotation.y, rotationvec[1]);
  transform = glm::rotate(transform, this->_rotation.z, rotationvec[2]);
  transform = glm::scale(transform, this->_scale);

  this->_transform = transform;
}

void	Coord3::setPosition(const glm::vec3& p)
{
  this->_position = p;
  this->updateTransform();
}

void	Coord3::setRotation(const glm::vec3& r)
{
  this->_rotation = r;
  this->updateTransform();
}

void	Coord3::setScale(const glm::vec3& s)
{
  this->_scale = s;
  this->updateTransform();
}

const glm::mat4&	Coord3::getTransform() const
{
  return (this->_transform);
}

const glm::vec3&	Coord3::getPosition() const
{
  return (this->_position);
}

const glm::vec3&	Coord3::getRotation() const
{
  return (this->_rotation);
}

const glm::vec3&	Coord3::getScale() const
{
  return (this->_scale);
}
