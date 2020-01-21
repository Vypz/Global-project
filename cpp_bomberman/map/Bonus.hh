//
// Bonus.hh for  in /home/ouroub_a/rendu/cpp_bomberman/map
//
// Made by amina ourouba
// Login   <ouroub_a@epitech.net>
//
// Started on  Sun May 25 11:28:13 2014 amina ourouba
// Last update Sun Jun 15 18:28:57 2014 virgile prideaux
//

#ifndef		BONUS_HH_
# define	BONUS_HH_

# include	"AElement.hh"

class Bonus : public AElement
{
public:
  enum	BonType
  {
    ONE_MORE_BOMB,
    SPEED,
    SCOPE,
    NONE
  };

private:
  Bonus(Bonus const& bonus);
  Bonus&	operator=(Bonus const& bonus);

  BonType	_bonType;

public:
  Bonus(int x, int y, Bonus::BonType type);
  ~Bonus();

  Bonus::BonType	getBonType() const;
  bool			walkThrough() const;
};

#endif	/* !BONUS_HH_ */
