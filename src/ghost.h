#pragma once

#include "actor.h"

class Ghost : public Actor
{
public:
  Ghost(Game& game, const sf::Vector2i& startPosition, const sf::Vector2i& target, int spritesIndex);

private:
  enum class Mode
  {
    CHASE,
    SCATTER,
  };

  const sf::Vector2i& GetTargetTile() const;
  int GetDistanceToTarget(const sf::Vector2i& position) const;
  bool IsMovePossible(const sf::Vector2i& position) const;
  virtual void UpdatePosition(float elapsedTime);
  bool CheckModeChange(float elapsedTime);

  sf::Vector2i m_CameFrom;
  sf::Vector2i m_ScatterTargetTile;

  Mode m_Mode;

  float m_ModeStartTime;
};
