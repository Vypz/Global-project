//
// Engine.cpp for bomberman in /home/pridea_v/rendu/cpp_bomberman
//
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
//
// Started on  Tue May 13 16:05:26 2014 virgile prideaux
// Last update Sun Jun 15 23:03:22 2014 virgile prideaux
//

#include	"Engine.hh"
#include	"Character.hh"
#include	"AI.hh"
#include	<OpenGL.hh>
#include	<iostream>
#include	<sstream>
#include	<glm/glm.hpp>
#include	<glm/gtc/matrix_transform.hpp>
#include	<cmath>

#include	"AElement.hh"
#include	"Bomb.hh"
#include	"Explosion.hh"

glm::vec3	rotationvec[] =
  {
    glm::vec3(1, 0, 0),
    glm::vec3(0, 1, 0),
    glm::vec3(0, 0, 1)
  };

Engine::Engine(int nbAI, int volume, const std::string& map, const std::string& texture):
  _menuCamPos(0, 0, 68),
  _zoom(1700),
  _nbPlayers(2),
  _beginNbAI(nbAI), _beginVolume(volume), _initMap(map), _beginTexture(texture)
{}

Engine::~Engine()
{
  for (int i = 0; i < 3; i++)
    delete this->_healthbar[i];
  delete this->_blast;
}

bool		Engine::mapInit(const std::string& path)
{
  const char*	maps[] =
    {
      "map.bmp",
      "map_boo.bmp",
      "map_coxi.bmp",
      "map_creeper.bmp",
      "map_goomba.bmp",
      "map_lantern.bmp",
      "map_large.bmp",
      "map_robot.bmp",
      "map_toad.bmp",
    };
  int	i;

  if (path != "")
    return (this->_map.init(path));
  i = 0;
  i = (rand() % 9);
  return (this->_map.init(maps[i]));
}

bool	Engine::_checkMap()
{
  for (int x = 0; this->_map[x]; x++)
    for (int y = 0; this->_map[x][y]; y++)
      if (this->_map[x][y].walkThrough())
	return (true);
  return (false);
}

Character*	Engine::_putCharacter(int& x, int& y, bool isAI)
{
  Character*	character;

  if (this->_checkMap() == false)
    {
      std::cerr << "Not enough place for a new character." << std::endl;
      return (NULL);
    }
  do
    {
      x = random() % this->_map.getHeight();
      y = random() % this->_map.getWidth();
    } while (this->_map[x][y].walkThrough() == false);
  if (isAI)
    character = new AI(x, y);
  else
    character = new Character(x, y, false);
  return (character);
}

bool		Engine::initialize()
{
  glm::mat4	projection;
  glm::mat4	transformation;

  // CONTEXT
  if (this->_context.start(WIN_WIDTH, WIN_HEIGHT, WIN_NAME) == false)
    {
      std::cerr << "...failed to start game context" << std::endl;
      return (false);
    }
  glEnable(GL_DEPTH_TEST);
  glAlphaFunc(GL_GREATER, 0.1f);
  glEnable(GL_ALPHA_TEST);
  if (this->_shader.load(SHADER_FRAGMENT_PATH, GL_FRAGMENT_SHADER) == false
      || this->_shader.load(SHADER_VERTEX_PATH, GL_VERTEX_SHADER) == false
      || this->_shader.build() == false)
    {
      std::cerr << "...failed to load and / or build shader" << std::endl;
      return (false);
    }
  projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 50000.0f);
  transformation = glm::lookAt(_menuCamPos, glm::vec3(0, 0, 0), rotationvec[1]);
  this->_shader.bind();
  if (this->_shader.setUniform("view", transformation) == false)
    {
      std::cerr << "...failed to set view" << std::endl;
      return (false);
    }
  if (this->_shader.setUniform("projection", projection) == false)
    {
      std::cerr << "...failed to set projection" << std::endl;
      return (false);
    }

  if (this->_beginTexture != "")
    system((std::string("cp ") + this->_beginTexture + " LibBomberman_linux_x64/assets/bomber_uvw_colored.tga").c_str());
  // ANIMATED MODEL
  if (this->_marvin.load("LibBomberman_linux_x64/assets/marvin.fbx") == false)
    {
      std::cerr << "...failed to load model" << std::endl;
      return (false);
    }
  if (this->_marvin.setCurrentAnim(0, true) == false)
    {
      std::cerr << "...failed to load animation" << std::endl;
      return (false);
    }

  if (this->_marvinStatic.load("LibBomberman_linux_x64/assets/marvin_static.fbx") == false)
    {
      std::cerr << "...failed to load model" << std::endl;
      return (false);
    }

  // MAP 2D init
  if (mapInit(this->_initMap) == false)
    {
      std::cerr << "...failed to initialize map" << std::endl;
      return (false);
    }

  // MAP 3D init
  AElement*		tmp;

  for (int i = 0; this->_map[i]; i++)
    {
      for (int j = 0; this->_map[i][j]; j++)
	{
	  if ((tmp = this->_map[i][j].getElement(AElement::WALL)))
	    tmp->setPosition(glm::vec3(tmp->getYPos() * 80 - this->_map.getWidth() - 80, 0,
				       tmp->getXPos() * 80 - this->_map.getHeight() - 80));
	}
    }

  // BONUS

  // 3D ELEMENTS
  this->_wall.setTexture("./LibBomberman_linux_x64/assets/wall.tga");
  this->_wall.setGeometry(40, 40, 40);

  this->_bonus_bomb.setTexture("./LibBomberman_linux_x64/assets/bonusNbBomb.tga");
  this->_bonus_bomb.setGeometry(40, 40, 40);

  this->_bonus_scope.setTexture("./LibBomberman_linux_x64/assets/bonusPowerBomb.tga");
  this->_bonus_scope.setGeometry(40, 40, 40);

  this->_bonus_speed.setTexture("./LibBomberman_linux_x64/assets/bonusSpeed.tga");
  this->_bonus_speed.setGeometry(40, 40, 40);

  this->_bomb.setTexture("./LibBomberman_linux_x64/assets/bomb.tga");
  this->_bomb.setGeometry(40, 40, 40);

  this->_block.setTexture("./LibBomberman_linux_x64/assets/dblock.tga");
  this->_block.setGeometry(40, 40, 40);

  this->_blast = new Plan(true); // animé
  this->_blast->setTexture("./LibBomberman_linux_x64/assets/blast/out");
  this->_blast->setGeometry(40, 40, 40);

  Plan*	hb;

  hb = new Plan;
  hb->setTexture("./LibBomberman_linux_x64/assets/empty.tga");
  hb->setGeometry(40, 25, 40);
  this->_healthbar.push_back(hb);

  hb = new Plan;
  hb->setTexture("./LibBomberman_linux_x64/assets/half.tga");
  hb->setGeometry(40, 25, 40);
  this->_healthbar.push_back(hb);

  hb = new Plan;
  hb->setTexture("./LibBomberman_linux_x64/assets/full.tga");
  hb->setGeometry(40, 25, 40);
  this->_healthbar.push_back(hb);

  this->_menu.initialize();

  int	x;
  int	y;
  this->_player = this->_putCharacter(x, y, false);
  this->_map[x][y].addElement(this->_player);

  Character	*newia;

  for (int i = 0; i < this->_beginNbAI; i++)
    {
      newia = this->_putCharacter(x, y, true);
      this->_map[x][y].addElement(newia);
    }
  this->_nbAI = this->_beginNbAI;
  
  // SOUND
  this->_audiomanager.init();
  this->_audiomanager.load(Audio::BOMBPLANT, "./audio/SFX/bombplant.wav");
  this->_audiomanager.load(Audio::CANCEL, "./audio/SFX/cancel.wav");
  this->_audiomanager.load(Audio::CHANGESELECT, "./audio/SFX/changeselect.wav");
  this->_audiomanager.load(Audio::DESTROYEDWALL, "./audio/SFX/destroyedwall.wav");
  this->_audiomanager.load(Audio::DOUBLEKILL, "./audio/SFX/doublekill.wav");
  this->_audiomanager.load(Audio::EXPLOSION, "./audio/SFX/explosion.wav");
  this->_audiomanager.load(Audio::FIRSTBLOOD, "./audio/SFX/firstblood.wav");
  this->_audiomanager.load(Audio::HUMILIATION, "./audio/SFX/humiliation.wav");
  this->_audiomanager.load(Audio::MULTIKILL, "./audio/SFX/multikill.wav");
  this->_audiomanager.load(Audio::NEWRECORD, "./audio/SFX/newrecord.wav");
  this->_audiomanager.load(Audio::OK, "./audio/SFX/ok.wav");
  this->_audiomanager.load(Audio::PLAYERDEATH, "./audio/SFX/loss.wav");
  this->_audiomanager.load(Audio::PLAYERHIT, "./audio/SFX/powerdown.wav");
  this->_audiomanager.load(Audio::POWERUP, "./audio/SFX/powerup.wav");
  this->_audiomanager.load(Audio::UNSTOPPABLE, "./audio/SFX/unstoppable.wav");

  this->_audiomanager.load(Audio::CREATOR, "./audio/Melodies/creator.mp3");
  this->_audiomanager.load(Audio::GAME, "./audio/Melodies/game.mp3");
  this->_audiomanager.load(Audio::INTRO, "./audio/Melodies/intro.wav");
  this->_audiomanager.load(Audio::LOSS, "./audio/Melodies/loss.wav");
  this->_audiomanager.load(Audio::MENU, "./audio/Melodies/menu.mp3");
  this->_audiomanager.load(Audio::WIN, "./audio/Melodies/win.wav");

  this->_audiomanager.play(Audio::MENU);
  this->_audiomanager.setVolume(this->_beginVolume);
  return (true);
}

bool	Engine::update()
{
  int	n;

  this->_context.updateInputs(this->_input);
  if (this->_input.getKey(SDLK_ESCAPE) || this->_input.getInput(SDL_QUIT))
    return (false);
  if (this->_menu.isDisplayed())
    {
      n = this->_menu.update(*this);
      if (n == 0)
	{
	  this->_menu.setDisplayed(false);
	  this->_nbPlayers = 1;
	}
      if (n == 1)
	{
	  int	x;
	  int	y;
	  this->_menu.setDisplayed(false);
	  this->_nbPlayers = 2;
	  this->_player2 = this->_putCharacter(x, y, false);
	  this->_player2->setPlayerNum(1);
	  this->_map[x][y].addElement(this->_player2);
	}
      if (n == 0 || n == 1)
	{
	  this->_audiomanager.stop();
	  this->_audiomanager.play(Audio::GAME);
	}
      if (n == -2)
	return (true);
    }

  if (this->_menu.getDisplayed() == false)
    for (int x = 0; this->_map[x]; x++)
      for (int y = 0; this->_map[x][y]; y++)
	if (this->_map[x][y])
	  for (std::list<AElement*>::iterator it = this->_map[x][y].begin(); it != this->_map[x][y].end(); this->_map[x][y].nextIterator(it))
	    if ((*it)->getType() == AElement::CHARACTER)
	      dynamic_cast<Character*>(*it)->resetHasMoved();
  if (this->_menu.getDisplayed() == false)
    for (int x = 0; this->_map[x]; x++)
      for (int y = 0; this->_map[x][y]; y++)
	if (this->_map[x][y])
	  for (std::list<AElement*>::iterator it = this->_map[x][y].begin(); it != this->_map[x][y].end(); this->_map[x][y].nextIterator(it))
	    (*it)->update(*this);
  this->_context.updateClock(this->_clock);

  if (this->_nbPlayers == 0)
    {
      this->_audiomanager.stop();
      this->_menu.setDisplayed(true);
      this->_menu.setScreen(1);
      this->_audiomanager.play(Audio::LOSS);
    }
  if (this->_nbAI == 0 && this->_nbPlayers == 1)
    {
      this->_audiomanager.stop();
      this->_menu.setDisplayed(true);
      this->_menu.setScreen(2);
      this->_audiomanager.play(Audio::WIN);
    }

  return (true);
}

void		Engine::draw()
{
  bool		marvinIsDrawn = false;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (this->_menu.getDisplayed() == true)
    {
      glm::mat4	transformation;
      transformation = glm::lookAt(_menuCamPos, glm::vec3(0, 0, 0), rotationvec[1]);
      this->_shader.setUniform("view", transformation);
      this->_menu.draw(*this);
    }
  else
    {
      for (int x = 0; this->_map[x]; x++)
	for (int y = 0; this->_map[x][y]; y++)
	  if (this->_map[x][y])
	    for (std::list<AElement*>::iterator it = this->_map[x][y].begin(); it != this->_map[x][y].end(); this->_map[x][y].nextIterator(it))
	      if ((*it)->getType() == AElement::BOMB)
		this->_bomb.draw((*it)->getTransform(), this->_shader);
	      else if ((*it)->getType() == AElement::EXPLOSION)
		this->_blast->draw((*it)->getTransform(), this->_shader, dynamic_cast<Explosion*>(*it)->getFrame(this->_clock));
	      else if ((*it)->getType() == AElement::CHARACTER)
		{
		  if ((*it)->getAnimation() == 0)
		    this->_marvinStatic.draw(this->_shader, (*it)->getTransform(), this->_clock.getElapsed());
		  else
		    {
		      this->_marvin.draw(this->_shader, (*it)->getTransform(), marvinIsDrawn ? 0 : this->_clock.getElapsed() * dynamic_cast<Character*>(*it)->getSpeed() * 0.4);
		      marvinIsDrawn = true;
		    }
		  int	hp = dynamic_cast<Character*>(*it)->getHealthPoint();
		  if (hp > 0)
		    this->_healthbar[hp - 1]->draw(dynamic_cast<Character*>(*it)->getHBTransform(), this->_shader);
		  dynamic_cast<Character*>(*it)->displayHitbox(this->_shader);
		}
	      else if ((*it)->getType() == AElement::WALL)
		{
		  if (dynamic_cast<Wall*>(*it)->isDestroyable())
		    this->_block.draw((*it)->getTransform(), this->_shader);
		  else
		    this->_wall.draw((*it)->getTransform(), this->_shader);
		}
	      else if ((*it)->getType() == AElement::BONUS)
		{
		  if (dynamic_cast<Bonus*>(*it)->getBonType() == Bonus::ONE_MORE_BOMB)
		    this->_bonus_bomb.draw((*it)->getTransform(), this->_shader);
		  if (dynamic_cast<Bonus*>(*it)->getBonType() == Bonus::SPEED)
		    this->_bonus_speed.draw((*it)->getTransform(), this->_shader);
		  if (dynamic_cast<Bonus*>(*it)->getBonType() == Bonus::SCOPE)
		    this->_bonus_scope.draw((*it)->getTransform(), this->_shader);
		}
      glm::vec3	p1 = this->_player->getPosition();
      
      if (this->_nbPlayers == 2)
	{
	  glm::vec3	p2 = this->_player2->getPosition();
	  this->_zoom = p1.x - p2.x;
	  if (this->_zoom < 0)
	    this->_zoom *= -1;
	  int	tmp = p1.z - p2.z;
	  if (tmp < 0)
	    tmp *= -1;
	  tmp *= 1.5;
	  if (this->_zoom < tmp)
	    this->_zoom = tmp;
	  if (this->_zoom < 1700) // zoom minimal
	    this->_zoom = 1700;

	  if (this->_shader.setUniform("view", glm::lookAt(glm::vec3((p1.x + p2.x) / 2, this->_zoom, 800 + (p1.z + p2.z) / 2), glm::vec3((p1.x + p2.x) / 2, (p1.y + p2.y) / 2, (p1.z + p2.z) / 2), rotationvec[1])) == false)
	    std::cerr << "failed to move camera" << std::endl;
	}
      else
	{
	  this->_zoom = 1700;
	  if (this->_shader.setUniform("view", glm::lookAt(glm::vec3(p1.x, this->_zoom, 800 + p1.z), glm::vec3(p1.x, p1.y, p1.z), rotationvec[1])) == false)
	    std::cerr << "failed to move camera" << std::endl;
	}
    }
  this->_context.flush();
}

gdl::BasicShader&	Engine::getShader()
{
  return (this->_shader);
}

gdl::Input&	Engine::getInput()
{
  return (this->_input);
}

Map&		Engine::getMap()
{
  return (this->_map);
}

gdl::Clock&	Engine::getClock()
{
  return (this->_clock);
}

const Plan&	Engine::getExplosion()
{
  return (*this->_blast);
}

Audio&		Engine::getAudiomanager()
{
  return (this->_audiomanager);
}

void	Engine::setPlayer1(Character* character)
{
  this->_player = character;
}

Character*	Engine::getPlayer2()
{
  return (this->_player2);
}

void	Engine::setPlayer2(Character* character)
{
  this->_player2 = character;
}

void	Engine::decNbPlayers()
{
  this->_nbPlayers--;
}

void	Engine::decNbAI()
{
  this->_nbAI--;
}
