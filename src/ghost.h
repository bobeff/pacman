#pragma once

#include "actor.h"
#include "ghost_mode.h"

class Ghost : public Actor
{
  friend class ChaseMode;
  friend class ScatterMode;
public:
  Ghost(Game& game, const sf::Vector2i& startPosition,
    const sf::Vector2i& target, int spritesIndex);
  virtual ~Ghost();

private:
  const sf::Vector2i& GetTargetTile() const;
  int GetDistanceToTarget(const sf::Vector2i& position) const;
  bool IsMovePossible(const sf::Vector2i& position) const;
  virtual void UpdatePosition(float elapsedTime);

  sf::Vector2i m_CameFrom;
  sf::Vector2i m_ScatterTargetTile;

  GhostMode* m_Modes[GhostMode::MODES_COUNT];
  GhostMode* m_Mode;
};
