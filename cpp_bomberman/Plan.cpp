//
// Plan.cpp for bomberman in /home/pridea_v/rendu/cpp_bomberman
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Sat May 31 23:26:31 2014 virgile prideaux
// Last update Sun Jun 15 18:21:33 2014 virgile prideaux
//

#include	"Plan.hh"

#include	<glm/glm.hpp>
#include	<glm/gtc/matrix_transform.hpp>
#include	<sstream>
#include	<iostream>

Plan::Plan(bool animate)
  : _curFrame(0), _animate(animate)
{}

Plan::~Plan()
{
  size_t	i = 0;

  while (i < this->_texture.size())
    delete this->_texture[i++];
}

bool			Plan::setTexture(const std::string& path)
{
  gdl::Texture*		tmp;
  std::ostringstream	ss;//(path);
  int			i = 1;

  ss << path;
  if (this->_animate)
    ss << i << ".tga";
  tmp = new gdl::Texture;
  while (tmp->load(ss.str()))
    {
      this->_texture.push_back(tmp);
      i++;
      tmp = new gdl::Texture;
      ss.str("");
      ss << path;
      ss << i;
      ss << ".tga";
    }
  delete tmp;
  return (true);
}

void	Plan::setGeometry(int x, int y, int z)
{
  this->_geometry.pushVertex(glm::vec3(x, -y, z));
  this->_geometry.pushVertex(glm::vec3(x, y, z));
  this->_geometry.pushVertex(glm::vec3(-x, y, z));
  this->_geometry.pushVertex(glm::vec3(-x, -y, z));

  this->_geometry.pushUv(glm::vec2(0.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 1.0f));
  this->_geometry.pushUv(glm::vec2(0.0f, 1.0f));

  this->_geometry.build();
}

void		Plan::draw(const glm::mat4 &transform, gdl::BasicShader &shader)
{
  this->_texture[this->_curFrame]->bind();
  this->_geometry.draw(shader, transform, GL_QUADS);
}

void		Plan::draw(const glm::mat4 &transform, gdl::BasicShader &shader, int frame)
{
  this->_texture[frame]->bind();
  this->_geometry.draw(shader, transform, GL_QUADS);
}

int	Plan::getNbFrame() const
{
  return (this->_texture.size());
}
