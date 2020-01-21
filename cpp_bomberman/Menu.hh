//
// Menu.hh for bomberman in /home/liron_b/rendu/cpp_bomberman
// 
// Made by liron_b
// Login   <liron_b@epitech.net>
// 
// Started on  Thu Jun  5 13:17:11 2014 liron_b
// Last update Sun Jun 15 18:21:21 2014 virgile prideaux
//

#ifndef		MENU_HH_
# define	MENU_HH_

#include	"Plan.hh"

class	Engine;
class	Menu;

class	Screen
{
private:
  Screen(const Screen&);
  Screen&	operator=(const Screen&);

public:
  Screen(const char* plan, glm::vec3* cursorPos, int size, int (Menu::*func)(Engine&));
  ~Screen();

  Plan*		_plan;
  glm::vec3*	_cursors;
  int		_size;
  int		(Menu::*_func)(Engine&);
};

class	Menu
{
private:
  Plan*			_arrow;
  int			_cursorIdx;
  bool			_keyPressed;
  bool			_isDisplayed;
  std::vector<Screen*>	_screens;
  Screen*		_curScreen;

  void			_updateCursor(int newPos);
  int			_updateMenu(Engine& engine);
  int			_update2(Engine& engine);

  Menu(const Menu&);
  Menu&			operator=(const Menu&);

public:
  Menu();
  ~Menu();

  bool	initialize();
  int	update(Engine& engine);
  void	draw(Engine& engine) const;
  bool	isDisplayed() const;
  void	setDisplayed(bool newState);
  bool	getDisplayed() const;
  void	setScreen(int n);
};

#endif	/* !MENU_HH_ */
