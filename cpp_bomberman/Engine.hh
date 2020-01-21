//
// GameEngine.hh for bomberman in /home/pridea_v/rendu/cpp_bomberman
//
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
//
// Started on  Tue May 13 16:02:54 2014 virgile prideaux
// Last update Sun Jun 15 22:50:57 2014 liron_b
//

#ifndef		ENGINE_HH_
# define	ENGINE_HH_

# include	<Game.hh>
# include	<SdlContext.hh>
# include	<BasicShader.hh>
# include	<Clock.hh>
# include	<Input.hh>
# include	<Model.hh>
# include	<vector>

# include	"Plan.hh"
# include	"Map.hh"
# include	"Cube.hh"
# include	"Menu.hh"
# include	"Audio.hh"

# define	WIN_WIDTH		1440
# define	WIN_HEIGHT		1080
# define	WIN_NAME		"Bomberman"
# define	SHADER_FRAGMENT_PATH	"LibBomberman_linux_x64/shaders/basic.fp"
# define	SHADER_VERTEX_PATH	"LibBomberman_linux_x64/shaders/basic.vp"

class Character;

class	Engine : public gdl::Game
{
private:
  // elements de la gdl
  gdl::SdlContext		_context;
  gdl::BasicShader		_shader;
  gdl::Clock			_clock;
  gdl::Input			_input;

  // camera
  glm::vec3			_menuCamPos;
  float				_zoom;

  // objets
  gdl::Model			_marvin;
  gdl::Model			_marvinStatic;
  Map				_map;
  Character*			_player;
  Character*			_player2;
  std::vector<Character*>	_IAs;

  Audio				_audiomanager;

  int				_nbPlayers;
  int				_nbAI;
  Menu				_menu;
  Cube				_wall;
  Cube				_block;
  Cube				_bomb;
  Cube				_bonus_bomb;
  Cube				_bonus_speed;
  Cube				_bonus_scope;
  Plan*				_blast;

  std::vector<Plan*>		_healthbar;
  Plan*				_hbfull;
  Plan*				_hbhalf;
  Plan*				_hblow;

  int				_beginNbAI;
  int				_beginVolume;
  std::string			_initMap;
  std::string			_beginTexture;

  bool				_checkMap();
  Character*			_putCharacter(int& x, int& y, bool isAI);

  Engine&			operator=(const Engine&);
  Engine(const Engine&);

public:
  Engine(int nbAI, int volume, const std::string& map, const std::string& texture);
  ~Engine();
  virtual bool		initialize();
  virtual bool		update();
  virtual void		draw();
  bool			mapInit(const std::string& path);
  void			spawn();

  Map&			getMap();
  gdl::BasicShader&	getShader();
  gdl::Input&		getInput();
  gdl::Clock&		getClock();
  const Plan&		getExplosion();
  Audio&		getAudiomanager();
  void			setPlayer1(Character* character);
  Character*		getPlayer2();
  void			setPlayer2(Character* character);
  void			decNbPlayers();
  void			decNbAI();
};

#endif	/* !ENGINE_HH_ */
