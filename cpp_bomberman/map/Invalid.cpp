//
// Invalid.cpp for bomberman in /home/liron_b/rendu/cpp_bomberman/map
//
// Made by liron_b
// Login   <liron_b@epitech.net>
//
// Started on  Wed May 21 12:16:05 2014 liron_b
// Last update Fri May 30 13:32:00 2014 amina ourouba
//

#include	"Invalid.hh"

Invalid	Invalid::instance;

Invalid::Invalid()
{}

Invalid::~Invalid()
{}

Invalid::operator bool() const
{
  return (false);
}
