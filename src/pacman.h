#pragma once

#include "actor.h"

class Pacman : public Actor
{
public:
  Pacman(Game& game);
 
  Direction NewDirection;

private:
  void SetInitialSpriteAsCurrent();
  bool IsMovePossible(const sf::Vector2i& position) const;
  virtual void UpdatePosition(float elapsedTime);
  virtual float GetMoveTimeInterval() const;

  float m_MoveTimeInterval;
  sf::Sprite m_InitialSprite;
};
