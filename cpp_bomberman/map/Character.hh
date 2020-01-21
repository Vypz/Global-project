//
// Character.hh for  in /home/ouroub_a/rendu/cpp_bomberman/map
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Tue May 13 17:19:11 2014 amina ourouba
// Last update Sun Jun 15 18:37:29 2014 virgile prideaux
//

#ifndef		CHARACTER_HH_
# define	CHARACTER_HH_

# include	"Engine.hh"
# include	"AElement.hh"
# include	"Bomb.hh"
# include	"Hitbox.hh"

class		Engine;

class Character : public AElement
{
private:
  float		_shiftX;
  float		_shiftY;
  int		_anim;
  float		_speed;
  bool		_isAI;
  int		_bombScope;
  Hitbox	_hitbox;
  int		_bombMax;
  int		_posedBomb;
  int		_player;
  int		_hp;
  Coord3	_healthbar;
  float		_time;
  bool		_hasMoved;

  void		_putBomb(Engine& e);

  Character(const Character& c);
  Character&	operator=(const Character& c);

protected:
  bool		_canPutBomb() const;

public:
  Character(int x, int y, bool isAI, int player = 0);
  ~Character();

  int			getHealthPoint() const;
  const glm::mat4&	getHBTransform();
  bool			walkThrough() const;
  int			getAnimation() const;
  float			getSpeed() const;
  int			getBombScope() const;
  void			setAnimation(int anim);
  void			updatePosition(Map& map);
  void			displayHitbox(gdl::BasicShader &shader);
  void			setSpeed(float speed);
  void			move(float x, float y, Engine& e);
  bool			setPos(int x, int y, Engine& e);
  void			update(Engine &e);
  void			decBomb();
  void			setPlayerNum(int num);
  void			resetHasMoved();
};

#endif	/* !CHARACTER_HH_ */
