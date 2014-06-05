#pragma once

#include "maze.h"
#include "pacman.h"
#include "ghost.h"

class Game
{
  friend class Maze;
  friend class Actor;
  friend class Pacman;
  friend class Ghost;

public:
  Game();
  int Run();

private:
  void DrawText(const char* str, float x, float y);
  void SetGhostsToRunMode();

  sf::RenderWindow m_Window;
  sf::Clock m_Clock;

  sf::Font m_Font;
  sf::Text m_Text;

  Maze m_Maze;
  Pacman m_Pacman;

  Ghost* m_Ghosts[Ghost::GHOSTS_COUNT];

  sf::Uint8  m_TilesConsumed;
  sf::Uint16 m_Score;
};
