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

  friend sf::Vector2i RedGhostStrategy(const Game& game);
  friend sf::Vector2i BlueGhostStrategy(const Game& game);
  friend sf::Vector2i PinkGhostStrategy(const Game& game);
  friend sf::Vector2i OrangeGhostStrategy(const Game& game);

public:
  Game();
  ~Game();

  int Run();

private:
  enum State
  {
    ABOUT_TO_START,
    RUNNING,
    PACMAN_EATEN,
    PAUSED,
    GAME_OVER,
    WINNING,
  };

  void DrawText(const char* str, const sf::Vector2f& position,
    const sf::Color& color);

  void Reset();
  void Update();
  void SetGhostsToRunMode();
  void OnPacmanEaten();
  void DrawGameInfo();

  sf::RenderWindow m_Window;
  sf::Clock m_Clock;

  sf::Font m_Font;
  sf::Text m_Text;

  Maze m_Maze;
  Pacman m_Pacman;

  Ghost* m_Ghosts[Ghost::COUNT];

  sf::Uint8  m_EatenGhostsCount;
  sf::Uint8  m_PacmanLivesCount;
  sf::Uint16 m_Score;

  State m_State;
  State m_OldState;

  float m_PacmanEatenTime;
};
