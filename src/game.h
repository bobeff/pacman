#pragma once

#include "maze.h"
#include "pacman.h"

class Game
{
  friend class Maze;
  friend class Pacman;
public:
  Game();
  int Run();

private:
  sf::RenderWindow m_Window;
  sf::Clock m_Clock;
  Maze m_Maze;
  Pacman m_Pacman;
};
