#pragma once

class Game;

enum class Direction
{
  EAST,
  SOUTH,
  WEST,
  NORTH,
};

class Pacman
{
public:
  Pacman(Game& game);
  void Draw() const;
  void Update(float elapsedTime);
 
  Direction NewDirection;

private:
  Game& m_Game;

  sf::Sprite m_CurrentSprite;
  sf::Sprite m_InitialSprite;
  // for each direction and each animation state
  sf::Sprite m_Sprites[4][2];

  float m_PreviousTime;

  sf::Vector2i m_Position;
  sf::Vector2i m_NextPosition;
  
  Direction m_Direction;
  sf::Uint8 m_AnimationStage;
};
