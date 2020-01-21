//
// Menu.cpp for gomoku in /home/pridea_v/rendu/gomoku-2017-larue_a/gui
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Mon Dec  1 20:02:50 2014 virgile prideaux
// Last update Mon Feb  9 14:46:35 2015 virgile prideaux
//

#include	"Menu.hpp"
#include	<iostream>
#include	"Rules.hpp"

Menu::Menu()
{}

Menu::~Menu()
{}

void		Menu::init()
{
  sf::Texture	tex;

  tex.loadFromFile("gui/components/background.jpg");
  this->textures.push_back(tex);
  this->background.setTexture(this->textures[0]);
  this->gameFont.loadFromFile("gui/components/Dekiru.ttf");

  this->title.setString("Gomoku Ninuki");
  this->title.setFont(this->gameFont);
  this->title.setCharacterSize(80);
  this->title.setColor(sf::Color(0, 0, 0, 200));
  GameScene::centerText(this->title, 1800, 150);

  this->exit.setString("Quitter");
  this->exit.setFont(this->gameFont);
  this->exit.setCharacterSize(40);
  this->exit.setColor(sf::Color(0, 0, 0, 200));
  this->exit.setPosition(20, 20);

  this->vsPlayer.setString("Joueur c. Joueur");
  this->vsPlayer.setFont(this->gameFont);
  this->vsPlayer.setCharacterSize(60);
  this->vsPlayer.setColor(sf::Color(0, 0, 0, 200));
  GameScene::centerText(this->vsPlayer, 1800, 450);

  this->vsIA.setString("Joueur c. IA");
  this->vsIA.setFont(this->gameFont);
  this->vsIA.setCharacterSize(60);
  this->vsIA.setColor(sf::Color(0, 0, 0, 200));
  GameScene::centerText(this->vsIA, 1800, 550);
}

void	Menu::draw(sf::RenderWindow& window)
{
  window.clear();
  window.draw(this->background);
  window.draw(this->title);
  window.draw(this->exit);
  window.draw(this->vsPlayer);
  window.draw(this->vsIA);
  window.display();
}

void	Menu::input(int x, int y, bool action)
{
  if (GameScene::onMouseOver(this->exit, x, y) && action)
    this->returnScene = NULL;
  if (GameScene::onMouseOver(this->vsPlayer, x, y) && action)
    this->returnScene = new Rules(false);
  if (GameScene::onMouseOver(this->vsIA, x, y) && action)
    this->returnScene = new Rules(true);
}
