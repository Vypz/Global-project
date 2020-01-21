//
// Hitbox.cpp for bomberman in /home/pridea_v/rendu/cpp_bomberman
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Fri Jun 13 15:20:06 2014 virgile prideaux
// Last update Fri Jun 13 15:59:56 2014 virgile prideaux
//

#include	"Hitbox.hh"
#include	<cstdlib>
#include	<iostream>

Hitbox::Hitbox()
  : Plan(false)
{}

Hitbox::~Hitbox()
{}

void	Hitbox::setGeometry(int x, int y, int z)
{
  this->_geometry.setColor(glm::vec4((float)random() / RAND_MAX, (float)random() / RAND_MAX, (float)random() / RAND_MAX, 1));

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
