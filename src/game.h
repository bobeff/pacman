#pragma once

#include "screen.h"
#include "maze.h"
#include "pacman.h"
#include "ghost.h"

class Game : public Screen
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
  Game(Application& app);
  virtual ~Game();

  virtual void ProcessInput(const sf::Event& event);
  virtual void Update();
  virtual void Draw();
  virtual void ResetScreen();

private:
  enum State
  {
    STATE_ABOUT_TO_START,
    STATE_RUNNING,
    STATE_PACMAN_EATEN,
    STATE_PAUSED,
    STATE_GAME_OVER,
    STATE_WINNING,
    STATE_EXIT,
  };

  void Reset();
  void SetGhostsToRunMode();
  void OnPacmanEaten();
  void DrawGameInfo();
  sf::RenderWindow& GetRenderWindow() const;

  void DrawText(const char* text, const sf::Vector2f& position,
    const sf::Color& color);

  sf::Clock m_Clock;

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
