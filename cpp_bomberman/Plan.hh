//
// Plan.hh for bomberman in /home/pridea_v/rendu/cpp_bomberman
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Sat May 31 23:14:15 2014 virgile prideaux
// Last update Sun Jun 15 18:21:49 2014 virgile prideaux
//

#ifndef		PLAN_HH_
# define	PLAN_HH_

# include	<BasicShader.hh>
# include	<Geometry.hh>
# include	<Texture.hh>

# include	"Coord3.hh"

class	Plan : public Coord3
{
protected:
  gdl::Geometry			_geometry;
  std::vector<gdl::Texture*>	_texture;
  size_t			_curFrame;
  bool				_animate;

  Plan(const Plan&);
  Plan&				operator=(const Plan&);

public:
  Plan(bool animate = false);
  virtual ~Plan();

  bool		setTexture(const std::string& path);
  virtual void	setGeometry(int x, int y, int z);  
  void		draw(const glm::mat4 &transform, gdl::BasicShader &shader);
  void		draw(const glm::mat4 &transform, gdl::BasicShader &shader, int frame);
  int		getNbFrame() const;
};

#endif	/* !PLAN_HH_ */
