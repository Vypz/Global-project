//
// Menu.cpp for bomberman in /home/liron_b/rendu/cpp_bomberman
// 
// Made by liron_b
// Login   <liron_b@epitech.net>
// 
// Started on  Thu Jun  5 10:50:10 2014 liron_b
// Last update Sun Jun 15 22:40:39 2014 liron_b
//

#include	<iostream>
#include	<OpenGL.hh>
#include	<glm/glm.hpp>
#include	<glm/gtc/matrix_transform.hpp>
#include	"Menu.hh"
#include	"Engine.hh"
#include	<stdexcept>

glm::vec3	cursorPosMenu[] =
  {
    glm::vec3(-7, 13, 20),
    glm::vec3(-11, 8, 20),
    glm::vec3(-7, 3, 20),
    glm::vec3(-11.5, -2, 20),
    glm::vec3(-8, -6.5, 20),
    glm::vec3(-8, -12, 20)
  };

glm::vec3	cursorPosTest[] =
  {
    glm::vec3(-18, 11, 20),
    glm::vec3(-18, 6.5, 20),
    glm::vec3(-11, 1.8, 20),
    glm::vec3(-19, -2, 20),
  };

Screen::Screen(const char* plan, glm::vec3* cursorPos, int size, int (Menu::*func)(Engine&))
  : _cursors(cursorPos), _size(size), _func(func)
{
  this->_plan = new Plan(false);
  if (this->_plan->setTexture(plan) == false)
    throw std::runtime_error("failed to set texture");
  this->_plan->setGeometry(5, 5, 5);
  this->_plan->setPosition(glm::vec3(0, 0, 0));
  this->_plan->setRotation(glm::vec3(0, 0, -90));
  this->_plan->setScale(glm::vec3(4.39, 5.85, 6));
}

Screen::~Screen()
{}

Menu::Menu()
  : _cursorIdx(0), _keyPressed(false), _isDisplayed(false)
{}

Menu::~Menu()
{
  for (std::vector<Screen*>::iterator it = this->_screens.begin(); it != this->_screens.end(); ++it)
    delete *it;
  delete this->_arrow;
}

bool	Menu::initialize()
{
  this->_screens.push_back(new Screen("./LibBomberman_linux_x64/assets/menu/menu.tga",
				      cursorPosMenu, 6, &Menu::_updateMenu));
  this->_screens.push_back(new Screen("./LibBomberman_linux_x64/assets/menu/lose.tga",
				      cursorPosTest, 1, NULL));
  this->_screens.push_back(new Screen("./LibBomberman_linux_x64/assets/menu/win.tga",
				      cursorPosTest, 1, NULL));
  this->_curScreen = this->_screens[0];

  this->_arrow = new Plan(false);
  if (this->_arrow->setTexture("./LibBomberman_linux_x64/assets/menu/arrow.tga") == false)
    return (false);

  this->_arrow->setGeometry(5, 5, 5);
  //  this->_arrow->setPosition(this->_curScreen->_cursors[this->_cursorIdx]);
  this->_updateCursor(0);
  this->_arrow->setRotation(glm::vec3(0, 0, -90));
  this->_arrow->setScale(glm::vec3(0.5, 0.5, 2.5));

  this->_isDisplayed = true;

  return (true);
}

void		Menu::_updateCursor(int newPos)
{
  glm::vec3	vect;

  this->_cursorIdx = newPos;

  if (this->_cursorIdx == -1)
    this->_cursorIdx = this->_curScreen->_size - 1;
  if (this->_cursorIdx == (int)this->_curScreen->_size)
    this->_cursorIdx = 0;

  vect = this->_curScreen->_cursors[this->_cursorIdx];
  this->_arrow->setPosition(vect);
}

int	Menu::update(Engine& engine)
{
  bool	keyPressed;

  if (this->_isDisplayed == false)
    return (-1);
  if (this->_curScreen->_func == NULL)
    return (-2);
  keyPressed = engine.getInput().getKey(SDLK_RETURN) || engine.getInput().getKey(SDLK_UP) ||
    engine.getInput().getKey(SDLK_DOWN) || engine.getInput().getKey(SDLK_BACKSPACE);
  if (!keyPressed)
    {
      if (this->_keyPressed)
	this->_keyPressed = false;
      return (-1);
    }
  if (keyPressed && this->_keyPressed)
    return (-1);
  if (keyPressed)
    this->_keyPressed = true;

  if (engine.getInput().getKey(SDLK_UP))
    {
      engine.getAudiomanager().play(Audio::CHANGESELECT);
      this->_updateCursor(this->_cursorIdx - 1);
    }
  if (engine.getInput().getKey(SDLK_DOWN))
    {
      engine.getAudiomanager().play(Audio::CHANGESELECT);
      this->_updateCursor(this->_cursorIdx + 1);
    }
  return ((this->*(this->_curScreen->_func))(engine));
}

int	Menu::_updateMenu(Engine& engine)
{
  if (engine.getInput().getKey(SDLK_RETURN))
    {
      engine.getAudiomanager().play(Audio::OK);
      return (this->_cursorIdx);
    }
  return (-1);
}

void	Menu::draw(Engine& engine) const
{
  if (this->_isDisplayed == false)
    return ;
  this->_curScreen->_plan->draw(this->_curScreen->_plan->getTransform(), engine.getShader());
  if (this->_curScreen != this->_screens[1] && this->_curScreen != this->_screens[2])
    this->_arrow->draw(this->_arrow->getTransform(), engine.getShader());
}

bool	Menu::isDisplayed() const
{
  return (this->_isDisplayed);
}

void	Menu::setDisplayed(bool newState)
{
  this->_isDisplayed = newState;
}

bool	Menu::getDisplayed() const
{
  return (this->_isDisplayed);
}

void	Menu::setScreen(int n)
{
  this->_curScreen = this->_screens[n];
}
