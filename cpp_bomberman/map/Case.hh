//
// Case.hh for bomberman in /home/liron_b/rendu/cpp_bomberman/map
//
// Made by liron_b
// Login   <liron_b@epitech.net>
//
// Started on  Tue May 13 15:01:38 2014 liron_b
// Last update Sun Jun 15 22:43:10 2014 liron_b
// Last update Wed Jun 11 14:44:11 2014 liron_b
//

#ifndef		CASE_HH_
# define	CASE_HH_

# include	<list>
# include	<string>
# include	"AElement.hh"

class	Case
{
private:
  std::list<AElement*>			_content;
  std::list<AElement*>::iterator	_nextIt;

  static bool				_cantWalkThrough(const AElement* element);
  Case(const Case& src);
  Case&					operator=(const Case& src);

public:
  Case();
  virtual				~Case();

  virtual				operator bool() const;
  bool					init(unsigned int rgbType, int x, int y);
  bool					walkThrough() const;
  void					addElement(AElement* element);
  void					removeElement(AElement* element);
  bool					hasElement(AElement::Type elem) const;
  AElement*				getElement(AElement::Type elem) const;

  std::list<AElement*>::iterator	begin();
  std::list<AElement*>::iterator	end();
  void					nextIterator(std::list<AElement*>::iterator& it);
};

#endif	/* !CASE_HH_ */
