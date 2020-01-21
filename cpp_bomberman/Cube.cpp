//
// Cube.cpp for bomberman in /home/pridea_v/rendu/cpp_bomberman
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Mon Jun  9 15:14:53 2014 virgile prideaux
// Last update Fri Jun 13 15:20:55 2014 virgile prideaux
//

#include	"Cube.hh"

Cube::Cube()
  : Plan(false)
{}

Cube::~Cube()
{}

void	Cube::setGeometry(int x, int y, int z)
{
  this->_geometry.pushVertex(glm::vec3(x, -y, z));
  this->_geometry.pushVertex(glm::vec3(x, y, z));
  this->_geometry.pushVertex(glm::vec3(-x, y, z));
  this->_geometry.pushVertex(glm::vec3(-x, -y, z));

  this->_geometry.pushUv(glm::vec2(0.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 1.0f));
  this->_geometry.pushUv(glm::vec2(0.0f, 1.0f));

  this->_geometry.pushVertex(glm::vec3(x, -y, -z));
  this->_geometry.pushVertex(glm::vec3(x, y, -z));
  this->_geometry.pushVertex(glm::vec3(-x, y, -z));
  this->_geometry.pushVertex(glm::vec3(-x, -y, -z));

  this->_geometry.pushUv(glm::vec2(0.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 1.0f));
  this->_geometry.pushUv(glm::vec2(0.0f, 1.0f));

  this->_geometry.pushVertex(glm::vec3(x, -y, -z));
  this->_geometry.pushVertex(glm::vec3(x, y, -z));
  this->_geometry.pushVertex(glm::vec3(x, y, z));
  this->_geometry.pushVertex(glm::vec3(x, -y, z));

  this->_geometry.pushUv(glm::vec2(0.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 1.0f));
  this->_geometry.pushUv(glm::vec2(0.0f, 1.0f));

  this->_geometry.pushVertex(glm::vec3(-x, -y, z));
  this->_geometry.pushVertex(glm::vec3(-x, y, z));
  this->_geometry.pushVertex(glm::vec3(-x, y, -z));
  this->_geometry.pushVertex(glm::vec3(-x, -y, -z));

  this->_geometry.pushUv(glm::vec2(0.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 1.0f));
  this->_geometry.pushUv(glm::vec2(0.0f, 1.0f));

  this->_geometry.pushVertex(glm::vec3(x, y, z));
  this->_geometry.pushVertex(glm::vec3(x, y, -z));
  this->_geometry.pushVertex(glm::vec3(-x, y, -z));
  this->_geometry.pushVertex(glm::vec3(-x, y, z));

  this->_geometry.pushUv(glm::vec2(0.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 1.0f));
  this->_geometry.pushUv(glm::vec2(0.0f, 1.0f));

  this->_geometry.pushVertex(glm::vec3(x, -y, -z));
  this->_geometry.pushVertex(glm::vec3(x, -y, z));
  this->_geometry.pushVertex(glm::vec3(-x, -y, z));
  this->_geometry.pushVertex(glm::vec3(-x, -y, -z));

  this->_geometry.pushUv(glm::vec2(0.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 1.0f));
  this->_geometry.pushUv(glm::vec2(0.0f, 1.0f));

  
  this->_geometry.build();
}
