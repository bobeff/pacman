#pragma once

#include "actor.h"

class Ghost : public Actor
{
public:
  Ghost(Game& game, sf::Vector2i& startPosition, int spritesIndex);

private:
  int GetDistanceToTarget(const sf::Vector2i& position) const;
  bool IsMovePossible(const sf::Vector2i& position) const;
  virtual void UpdatePosition();

  sf::Vector2i m_CameFrom;
};
