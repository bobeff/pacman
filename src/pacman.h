#pragma once

#include "actor.h"

class Pacman : public Actor
{
public:
  Pacman(Game& game);
  sf::Vector2i GetPositionAhead(int tilesCount) const;
  Direction NewDirection;

private:
  bool IsMovePossible(const sf::Vector2i& position) const;
  virtual void SetCurrentSprite();
  virtual void UpdatePosition(float elapsedTime);
  virtual float GetMoveTimeInterval() const;

  float m_MoveTimeInterval;
  sf::Sprite m_InitialSprite;
};
