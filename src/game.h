#pragma once

#include "maze.h"

class Game
{
  friend class Maze;
public:
  Game();
  int Run();

private:
  sf::RenderWindow m_Window;
  Maze m_Maze;
};
