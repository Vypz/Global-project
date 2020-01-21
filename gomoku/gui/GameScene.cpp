//
// GameScene.cpp for gomoku in /home/pridea_v/rendu/gomoku-2017-larue_a/gui
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Mon Dec  1 19:42:16 2014 virgile prideaux
// Last update Thu Jan  8 14:11:12 2015 virgile prideaux
//

#include	"GameScene.hpp"
#include	<iostream>

GameScene::GameScene()
  : returnScene(this)
{}

GameScene::~GameScene()
{}

void	GameScene::centerText(sf::Text& obj, int x, int y)
{
  obj.setPosition(x / 2 - obj.getLocalBounds().width / 2, y);
}

bool	GameScene::onMouseOver(sf::Text& obj, int x, int y)
{
  if (x >= obj.getPosition().x && x <= obj.getLocalBounds().width + obj.getPosition().x + 20 &&
      y >= obj.getPosition().y && y <= obj.getLocalBounds().height + obj.getPosition().y + 20)
    {
      obj.setColor(sf::Color::White);
      return true;
    }
  obj.setColor(sf::Color(0, 0, 0, 200));
  return false;
}

bool	GameScene::onMouseOver(sf::Sprite& obj, int x, int y)
{
  if (x >= obj.getPosition().x && x <= obj.getLocalBounds().width + obj.getPosition().x &&
      y >= obj.getPosition().y && y <= obj.getLocalBounds().height + obj.getPosition().y)
    return true;
  return false;
}

GameScene*	GameScene::toScene()
{
  return this->returnScene;
}

void	GameScene::update()
{}
