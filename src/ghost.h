#pragma once

#include "actor.h"
#include "ghost_modes.h"

typedef sf::Vector2i(*GhostStrategy)(const Game& game);

class Ghost : public Actor
{
public:
  enum Color
  {
    RED,
    BLUE,
    PINK,
    ORANGE,
    COUNT,
  };

  Ghost(Game& game,
        const sf::Vector2i& startPosition,
        const sf::Vector2i& scatterTarget,
        GhostStrategy strategy,
        Color color,
        int spritesIndex);

  virtual ~Ghost();
  virtual void Reset();
  virtual void Draw() const;
  virtual void Update(float elapsedTime);

  GhostMode::Mode GetMode() const;

  sf::Vector2i GetTargetTile() const;
  const sf::Vector2i& GetScatterTargetTile() const;

  void ChangeMode(GhostMode::Mode mode, float startTime);
  void ReverseDirection();
  void SetDefaultSprites();
  void SetRunModeSprites();
  void SetResetModeSprites();
  void Flicker();
  void OnGhostEaten();
  void OnPacmanEaten() const;
  void CheckForCollisionWithPacman() const;

private:
  int GetDistanceToTarget(const sf::Vector2i& position) const;
  bool IsMovePossible(const sf::Vector2i& position) const;
  bool IsInHouse() const;
  const sf::Color& GetColor() const;
  virtual void UpdatePosition(float elapsedTime);
  virtual float GetMoveTimeInterval() const;

  sf::Vector2i m_CameFrom;
  sf::Vector2i m_ScatterTargetTile;

  GhostMode* m_Modes[GhostMode::ModesCount];
  GhostMode* m_Mode;

  bool m_IsModeChanged;

  GhostStrategy m_Strategy;
  Color m_Color;

  ActorSprites m_RunModeSprites;
  ActorSprites m_AboutToStopRunModeSprites;
  ActorSprites m_ResetModeSprites;
};
