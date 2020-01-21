//
// Rules.cpp for gomoku in /home/pridea_v/rendu/gomoku-2017-larue_a/gui
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Wed Dec  3 14:23:48 2014 virgile prideaux
// Last update Mon Feb  9 14:47:36 2015 virgile prideaux
//

#include	"Rules.hpp"
#include	<iostream>
#include	"Menu.hpp"
#include	"Goban.hpp"

Rules::Rules(bool ai)
  : ai(ai)
{}

Rules::~Rules()
{}

void		Rules::init()
{
  sf::Texture	tex;

  tex.loadFromFile("gui/components/background.jpg");
  this->textures.push_back(tex);
  this->background.setTexture(this->textures[0]);

  this->gameFont.loadFromFile("gui/components/Dekiru.ttf");

  this->title.setString(L"Règles optionnelles");
  this->title.setFont(this->gameFont);
  this->title.setCharacterSize(80);
  this->title.setColor(sf::Color(0, 0, 0, 200));
  GameScene::centerText(this->title, 1800, 150);

  this->menu.setString("Menu");
  this->menu.setFont(this->gameFont);
  this->menu.setCharacterSize(40);
  this->menu.setColor(sf::Color(0, 0, 0, 200));
  this->menu.setPosition(20, 20);

  this->rule1.setString("Cinq cassable");
  this->rule1.setFont(this->gameFont);
  this->rule1.setCharacterSize(60);
  this->rule1.setColor(sf::Color(0, 0, 0, 200));
  GameScene::centerText(this->rule1, 1800, 450);

  this->rule2.setString("Double-trois");
  this->rule2.setFont(this->gameFont);
  this->rule2.setCharacterSize(60);
  this->rule2.setColor(sf::Color(0, 0, 0, 200));
  GameScene::centerText(this->rule2, 1800, 550);

  this->bothRules.setString("Toutes");
  this->bothRules.setFont(this->gameFont);
  this->bothRules.setCharacterSize(60);
  this->bothRules.setColor(sf::Color(0, 0, 0, 200));
  GameScene::centerText(this->bothRules, 1800, 650);

  this->noneRules.setString("Aucune");
  this->noneRules.setFont(this->gameFont);
  this->noneRules.setCharacterSize(60);
  this->noneRules.setColor(sf::Color(0, 0, 0, 200));
  GameScene::centerText(this->noneRules, 1800, 750);
}

void	Rules::draw(sf::RenderWindow& window)
{
  window.clear();
  window.draw(this->background);
  window.draw(this->title);
  window.draw(this->menu);
  window.draw(this->rule1);
  window.draw(this->rule2);
  window.draw(this->bothRules);
  window.draw(this->noneRules);
  window.display();
}

void	Rules::input(int x, int y, bool action)
{
  if (GameScene::onMouseOver(this->menu, x, y) && action)
    this->returnScene = new Menu;
  if (GameScene::onMouseOver(this->noneRules, x, y) && action)
    this->returnScene = new Goban(0, ai);
  if (GameScene::onMouseOver(this->rule1, x, y) && action)
    this->returnScene = new Goban(1, ai);
  if (GameScene::onMouseOver(this->rule2, x, y) && action)
    this->returnScene = new Goban(2, ai);
  if (GameScene::onMouseOver(this->bothRules, x, y) && action)
    this->returnScene = new Goban(3, ai);
}
