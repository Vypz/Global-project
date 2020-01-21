//
// Goban.cpp for gomoku in /home/pridea_v/rendu/gomoku-2017-larue_a/gui
// 
// Made by virgile prideaux
// Login   <pridea_v@epitech.net>
// 
// Started on  Tue Dec  2 14:22:46 2014 virgile prideaux
// Last update Wed Feb 25 00:27:51 2015 virgile prideaux
//

#include	<iostream>
#include	"Menu.hpp"
#include	"Goban.hpp"

static const std::string	logstr[] = 
  {
    "Vous ne pouvez pas jouer ici",
    "Alignement cassable",
    "Victoire",
    "Capture",
    "-"
  };

Goban::Goban(int rules, bool ai)
  : arbitre(rules), displayPreview(false), isPlaying(true), ai(ai), simulation(20), timeLimit(0.020), _x(9), _y(9)
{}

Goban::~Goban()
{}

void		Goban::init()
{
  sf::Texture	tex;

  tex.loadFromFile("gui/components/background.jpg");
  this->textures.push_back(tex);
  tex.loadFromFile("gui/components/goban.png");
  this->textures.push_back(tex);
  tex.loadFromFile("gui/components/bluespawn.png");
  this->textures.push_back(tex);
  tex.loadFromFile("gui/components/orangespawn.png");
  this->textures.push_back(tex);
  tex.loadFromFile("gui/components/preview.png");
  this->textures.push_back(tex);

  this->background.setTexture(this->textures[0]);
  this->goban.setTexture(this->textures[1]);
  this->goban.setPosition(500, 255);

  this->gameFont.loadFromFile("gui/components/Dekiru.ttf");
  this->menu.setString("Menu");
  this->menu.setFont(this->gameFont);
  this->menu.setCharacterSize(40);
  this->menu.setColor(sf::Color(0, 0, 0, 200));
  this->menu.setPosition(20, 20);

  this->replay.setString("Rejouer");
  this->replay.setFont(this->gameFont);
  this->replay.setCharacterSize(40);
  this->replay.setColor(sf::Color(0, 0, 0, 200));
  this->replay.setPosition(20, 70);

  this->findAPlay.setString("   Suggerer un coup\n(ne bougez plus la souris)");
  this->findAPlay.setFont(this->gameFont);
  this->findAPlay.setCharacterSize(40);
  this->findAPlay.setColor(sf::Color(0, 0, 0, 200));
  this->findAPlay.setPosition(570, 825);

  this->playerLog.setString("Joueur : " + logstr[Arbitre::NONE]);
  this->playerLog.setFont(this->gameFont);
  this->playerLog.setCharacterSize(40);
  this->playerLog.setColor(sf::Color(0, 0, 0, 200));

  this->botSpeed.setString("Vitesse du Bot : 50 ms");
  this->botSpeed.setFont(this->gameFont);
  this->botSpeed.setCharacterSize(40);
  this->botSpeed.setColor(sf::Color(0, 0, 0, 200));
  this->botSpeed.setPosition(50, 300);

  this->ten.setString("10 ms");
  this->ten.setFont(this->gameFont);
  this->ten.setCharacterSize(40);
  this->ten.setColor(sf::Color(0, 0, 0, 200));
  this->ten.setPosition(200, 400);

  this->twenty.setString("20 ms");
  this->twenty.setFont(this->gameFont);
  this->twenty.setCharacterSize(40);
  this->twenty.setColor(sf::Color(0, 0, 0, 200));
  this->twenty.setPosition(200, 450);

  this->fifty.setString("50 ms");
  this->fifty.setFont(this->gameFont);
  this->fifty.setCharacterSize(40);
  this->fifty.setColor(sf::Color(0, 0, 0, 200));
  this->fifty.setPosition(200, 500);

  this->takeYourTime.setString("Own Me");
  this->takeYourTime.setFont(this->gameFont);
  this->takeYourTime.setCharacterSize(40);
  this->takeYourTime.setColor(sf::Color(0, 0, 0, 200));
  this->takeYourTime.setPosition(200, 550);

  this->botLog.setString("Bot : " + logstr[Arbitre::NONE]);
  this->botLog.setFont(this->gameFont);
  this->botLog.setCharacterSize(40);
  this->botLog.setColor(sf::Color(0, 0, 0, 200));

  this->blueScore.setFont(this->gameFont);
  this->blueScore.setCharacterSize(40);
  this->blueScore.setColor(sf::Color(0, 0, 0, 200));
  this->blueScore.setPosition(1250, 250);

  this->orangeScore.setFont(this->gameFont);
  this->orangeScore.setCharacterSize(40);
  this->orangeScore.setColor(sf::Color(0, 0, 0, 200));
  this->orangeScore.setPosition(1250, 300);

  this->overlay.setSize(sf::Vector2f(570, 570));
  this->overlay.setFillColor(sf::Color(0, 0, 0, 200));
  this->overlay.setPosition(500, 255);

  this->blue.setTexture(this->textures[2]);
  this->orange.setTexture(this->textures[3]);
  this->preview.setTexture(this->textures[4]);
  for (int i = 0; i < 19; i++)
    {
      for (int j = 0; j < 19; j++)
	this->board[i][j] = 0;
    }
}

void	Goban::drawSpawns(sf::RenderWindow& window)
{
  for (uint8_t i = 0; i < 19; i++)
    {
      for (uint8_t j = 0; j < 19; j++)
  	{
  	  if (this->board[i][j] == 1)
  	    {
  	      this->blue.setPosition(this->goban.getPosition().x + i * 30,
  				     this->goban.getPosition().y + j * 30);
  	      window.draw(this->blue);
  	    }
  	  else if (this->board[i][j] == 2)
  	    {
  	      this->orange.setPosition(this->goban.getPosition().x + i * 30,
  				       this->goban.getPosition().y + j * 30);
  	      window.draw(this->orange);
  	    }
  	}
    }
  if (this->arbitre.getWhoseTurn() == 1)
    {
      this->blue.setPosition(1200, 265);
      window.draw(this->blue);
    }
  else
    {
      this->orange.setPosition(1200, 315);
      window.draw(this->orange);
    }
}

void	Goban::update()
{
  if (this->arbitre.getUpdate())
    {
      this->updateBoard();
      this->arbitre.resetUpdate();
    }
  GameScene::centerText(this->playerLog, 1570, 100);
  GameScene::centerText(this->botLog, 1570, 150);
  this->blueScore.setString("Score Bleu : " + std::to_string(this->arbitre.getBlueScore()));
  this->orangeScore.setString("Score Rouge : " + std::to_string(this->arbitre.getRedScore()));
}

void	Goban::draw(sf::RenderWindow& window)
{
  window.clear();
  window.draw(this->background);
  window.draw(this->goban);
  window.draw(this->menu);
  if (this->ai)
    {
      window.draw(this->botSpeed);
      window.draw(this->ten);
      window.draw(this->twenty);
      window.draw(this->fifty);
      window.draw(this->takeYourTime);
    }
  window.draw(this->playerLog);
  window.draw(this->findAPlay);
  window.draw(this->botLog);
  window.draw(this->blueScore);
  window.draw(this->orangeScore);
  window.draw(this->replay);
  if (this->displayPreview == true)
    window.draw(this->preview);
  this->drawSpawns(window);
  if (this->isPlaying == false)
    window.draw(this->overlay);
  window.display();
}

void	Goban::onMouseOver(int x, int y, bool action)
{
  int i = 1;
  while (i <= 19)
    {
      if (x <= i * 30)
	break;
      i++;
    }
  int j = 1;
  while (j <= 19)
    {
      if (y <= j * 30)
	break;
      j++;
    }
  if (action)
    {
      this->_x = i - 1;
      this->_y = j - 1;
      Arbitre::Event	event = this->arbitre.play(i - 1, j - 1, true);
      if (event == Arbitre::WIN)
	this->isPlaying = false;
      this->playerLog.setString("Joueur : " + logstr[event]);
      if (this->arbitre.getWhoseTurn() == 2 && this->isPlaying && this->ai)
	{
	  uint8_t	playTime;
	  event = this->bot.play(this->arbitre, i - 1, j - 1, playTime, this->simulation, this->timeLimit, this->_x, this->_y);
	  this->botLog.setString("Bot : " + logstr[event] + " (a joue en " + std::to_string(playTime) + "ms)");
	  if (event == Arbitre::WIN)
	    this->isPlaying = false;
	}
    }
  else if (this->arbitre.getCaseContent(i - 1, j - 1) == 0)
    {
      this->preview.setPosition(this->goban.getPosition().x + (i - 1) * 30,
				this->goban.getPosition().y + (j - 1) * 30);
      this->displayPreview = true;
    }
  else
    this->displayPreview = false;
}

void	Goban::input(int x, int y, bool action)
{
  if (GameScene::onMouseOver(this->menu, x, y) && action)
    this->returnScene = new Menu;

  if (GameScene::onMouseOver(this->findAPlay, x, y) && action)
    {
      Arbitre	b(this->arbitre);
      uint8_t	playTime;
      uint8_t	savedX;
      uint8_t	savedY;

      this->bot.play(b, this->_x, this->_y, playTime, 100, 0.150, savedX, savedY, this->arbitre.getWhoseTurn());
      sf::Mouse	m;
      m.setPosition(sf::Vector2i(this->goban.getPosition().x + savedX * 30 + 30,
				 this->goban.getPosition().y + savedY * 30 + 30));
    }
  if (this->ai && GameScene::onMouseOver(this->ten, x, y) && action)
    {
      this->botSpeed.setString("Vitesse du Bot : " + this->ten.getString());
      this->simulation = 10;
      this->timeLimit = 0;
    }
  if (this->ai && GameScene::onMouseOver(this->twenty, x, y) && action)
    {
      this->botSpeed.setString("Vitesse du Bot : " + this->twenty.getString());
      this->simulation = 20;
      this->timeLimit = 0.001;
    }
  if (this->ai && GameScene::onMouseOver(this->fifty, x, y) && action)
    {
      this->botSpeed.setString("Vitesse du Bot : " + this->fifty.getString());
      this->simulation = 20;
      this->timeLimit = 0.020;
    }
  if (this->ai && GameScene::onMouseOver(this->takeYourTime, x, y) && action)
    {
      this->botSpeed.setString("Vitesse du Bot : -");
      this->simulation = 100;
      this->timeLimit = 0.150;
    }
  if (GameScene::onMouseOver(this->replay, x, y) && action)
    {
      this->arbitre.reset();
      this->_x = 9;
      this->_y = 9;
      this->isPlaying = true;
      this->displayPreview = true;
      this->playerLog.setString(logstr[Arbitre::NONE]);
      this->botLog.setString(logstr[Arbitre::NONE]);
    }
  if (this->isPlaying && GameScene::onMouseOver(this->goban, x, y) && (!this->ai || this->arbitre.getWhoseTurn() == 1))
    this->onMouseOver(x - this->goban.getPosition().x, y - this->goban.getPosition().y, action);
  else
    this->displayPreview = false;
}

void	Goban::updateBoard()
{
  for (uint8_t i = 0; i < 19; i++)
    {
      for (uint8_t j = 0; j < 19; j++)
	{
	  this->board[i][j] = this->arbitre.getCaseContent(i, j);
	}
    }
}
