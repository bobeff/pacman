#pragma once

#include "actor.h"

class Pacman : public Actor
{
public:
  Pacman(Game& game);
  void Draw() const;
 
  Direction NewDirection;

private:
  void SetInitialSpriteAsCurrent();
  bool IsMovePossible(const sf::Vector2i& position) const;
  virtual void UpdatePosition(float elapsedTime);

  sf::Sprite m_InitialSprite;
};
