//
// Gui.cpp for gomoku in /home/pridea_v/rendu/gomoku-2017-larue_a/gui
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Mon Dec  1 19:26:05 2014 virgile prideaux
// Last update Fri Jan 16 15:13:42 2015 virgile prideaux
//

#include	"Gui.hpp"
#include	"Menu.hpp"

Gui::Gui()
{}

Gui::~Gui()
{}

void	Gui::init()
{
  this->window.create(sf::VideoMode(1920, 1080), "gomoku", sf::Style::None);
  this->currentScene = new Menu;
  this->tmp = this->currentScene;
  this->currentScene->init();
}

bool	Gui::update()
{
  this->currentScene = this->currentScene->toScene();
  if (this->currentScene == NULL)
    return false;
  if (this->currentScene != this->tmp)
    {
      delete this->tmp;
      this->tmp = this->currentScene;
      this->currentScene->init();
    }
  this->currentScene->update();
  this->currentScene->draw(this->window);
  return true;
}

void		Gui::input()
{
  sf::Event	event;

  while (this->window.pollEvent(event))
    {
      if (event.type == sf::Event::MouseButtonReleased)
	this->currentScene->input(event.mouseButton.x, event.mouseButton.y, true);
      if (event.type == sf::Event::MouseMoved)
	this->currentScene->input(event.mouseMove.x, event.mouseMove.y, false);
    }
}
