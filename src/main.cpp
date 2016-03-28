//
// main.cpp for main.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Tue May 13 15:55:22 2014 CHAUCHET Alan
// Last update Fri Jun 13 15:04:48 2014 Maxime Manzano
//

#include		"GUI/Window.hh"
#include		"GUI/MapGUI.hh"
#include		"GUI/MenuGUI.hh"
#include		"Game/BomberGame.hh"
#include		"Game/Player.hh"
#include		"Thread/Cond.hh"
#include		"Game/Map.hh"
#include		"Game/Bomb.hh"
#include                "Game/ListFiles.hh"

int			main(int ac, char **av)
{
  BomberGame		game;
  std::string opt;

  if (ac == 1)
    game.setAnim(true);
  if (ac == 2)
    {
    opt = av[1];
    if (opt.compare(std::string("--noAnim")) == 0)
      game.setAnim(false);
    else
      {
	std::cout << "Invalid option. USAGE:./bomberman [--noAnim]" << std::endl;
	game.setAnim(true);
      }
    }
  game.start();
  return (0);
}
