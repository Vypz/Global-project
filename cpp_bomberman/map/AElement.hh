//
// AElement.hh for  in /home/ouroub_a/rendu/cpp_bomberman/map
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Tue May 20 11:07:11 2014 amina ourouba
// Last update Sun Jun 15 18:22:36 2014 virgile prideaux
//

#ifndef		AELEMENT_HH_
# define	AELEMENT_HH_


# include	"Coord3.hh"

class	Map;
class	Plan;
class	Engine;

class	AElement : public Coord3
{
public:
  enum	Type
    {
      WALL		= 0xFFFFFF,
      DESTRUCTIBLE_WALL	= 0xFF0000,
      NOTHING		= 0x000000,
      BONUS		= 1,
      BOMB		= 2,
      EXPLOSION		= 3,
      CHARACTER		= 4
    };

private:
  AElement(const AElement&);
  AElement& operator=(const AElement&);

protected:
  int			_posX;
  int			_posY;
  AElement::Type	_type;

public:
  AElement(AElement::Type, int x = 0, int y = 0);
  virtual		~AElement();
  virtual bool		setPos(int x, int y, Map& map);
  int			getXPos() const;
  int			getYPos() const;
  AElement::Type	getType() const;
  void			setType(AElement::Type type);
  virtual bool		walkThrough() const = 0;

  virtual void		update(Engine&);
  virtual int		getAnimation() const;
};

#endif /* !AELEMENT_HH_ */
