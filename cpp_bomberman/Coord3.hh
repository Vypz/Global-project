//
// Coord3.hh for bomberman in /home/pridea_v/rendu/cpp_bomberman
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Sun Jun  1 01:09:08 2014 virgile prideaux
// Last update Sun Jun 15 18:52:03 2014 virgile prideaux
//

#ifndef		COORD3_HH_
# define	COORD3_HH_

# include	<glm/glm.hpp>
# include	<glm/gtc/matrix_transform.hpp>

class	Coord3
{
private:
  Coord3(const Coord3&);
  Coord3&	operator=(const Coord3&);

protected:
  glm::vec3	_position;
  glm::vec3	_rotation;
  glm::vec3	_scale;
  glm::mat4	_transform;

public:
  Coord3(const glm::vec3& p, const glm::vec3& r, const glm::vec3& s);
  Coord3();
  ~Coord3();

  void			setPosition(const glm::vec3& p);
  void			setRotation(const glm::vec3& r);
  void			setScale(const glm::vec3& s);
  void			updateTransform();
  const glm::mat4&	getTransform() const;
  const glm::vec3&	getPosition() const;
  const glm::vec3&	getRotation() const;
  const glm::vec3&	getScale() const;
};

#endif	/* !COORD3_HH_ */
