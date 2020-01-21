#include	"Arbitre.hpp"
#include	<iostream>

void	bleu_test1()
{
  // Ligne droite 1:bleu  2:red
  Arbitre               swag = 0;
  Arbitre::Event        test = Arbitre::NONE;

  swag.init();
  test = swag.played(0, 1);
  test = swag.played(1, 1);

  test = swag.played(0, 2);
  test = swag.played(2, 1);

  test = swag.played(0, 3);
  test = swag.played(3, 1);

  test = swag.played(0, 4);
  test = swag.played(4, 1);

  test = swag.played(0, 5);

  if (test == Arbitre::BLUE_WINS)
    std::cout << "Sucess test 1 (Bleu win ligne droite)" << std::endl;
  if (test == Arbitre::NONE)
    std::cout << "None" << std::endl;
}

void	red_test1()
{
  //Diagonal
  Arbitre               swag = 0;
  Arbitre::Event        test = Arbitre::NONE;

  swag.init();
  test = swag.played(9, 1);
  test = swag.played(0, 0);

  test = swag.played(8, 8);
  test = swag.played(1, 1);

  test = swag.played(0, 3);
  test = swag.played(2, 2);

  test = swag.played(0, 4);
  test = swag.played(3, 3);

  test = swag.played(0, 5);
  test = swag.played(4, 4);

  if (test == Arbitre::ORANGE_WINS)
    std::cout << "Sucess test 2 (Red win en Diagonal)" << std::endl;
  if (test == Arbitre::NONE)
    std::cout << "None" << std::endl;
}

void	bleu_test2()
{
  // test vertical
  Arbitre               swag = 0;
  Arbitre::Event        test = Arbitre::NONE;

  swag.init();
  test = swag.played(1, 0);
  test = swag.played(1, 10);

  test = swag.played(2, 0);
  test = swag.played(6, 1);

  test = swag.played(3, 0);
  test = swag.played(3, 1);

  test = swag.played(4, 0);
  test = swag.played(4, 1);

  test = swag.played(5, 0);

  if (test == Arbitre::BLUE_WINS)
    std::cout << "Sucess test 3 (Bleu win en vertical)" << std::endl;
  if (test == Arbitre::NONE)
    std::cout << "None" << std::endl;
}

void    bleu_test3()
{
  // test vertical
  Arbitre               swag = 1;
  Arbitre::Event        test = Arbitre::NONE;

  swag.init();
  test = swag.played(1, 2);
  test = swag.played(1, 3);

  test = swag.played(2, 2);
  test = swag.played(2, 3);

  test = swag.played(3, 2);
  test = swag.played(3, 3);

  test = swag.played(4, 2);
  test = swag.played(4, 3);

  test = swag.played(3, 1);
  test = swag.played(9, 3);

  test = swag.played(5, 2);

  if (test == Arbitre::BLUE_WINS)
    std::cout << "Failed test 4 (5 cassable)" << std::endl;
  if (test == Arbitre::WIN_PREVENTED)
    std::cout << "Sucess test 4 (5 cassable)" << std::endl;
  if (test == Arbitre::NONE)
    std::cout << "None" << std::endl;
}


int	main()
{
  bleu_test1();
  red_test1();
  bleu_test2();
  bleu_test3();
}
