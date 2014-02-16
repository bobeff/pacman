#pragma once

class Game;

enum class Direction
{
  EAST,
  SOUTH,
  WEST,
  NORTH,
  NONE,
};

class Actor
{
public:
  Actor(Game& game, const sf::Vector2i& startPosition,
    int imagesIndex, float moveTimeInterval);
  void Draw() const;
  void Update(float elapsedTime);
  const sf::Vector2i& GetPosition() const;

protected:
  void SetCurrentSprite();
  void UpdateAnimation(float deltaTime);
  virtual void UpdatePosition(float elapsedTime) = 0;

  Game& m_Game;

  sf::Sprite m_CurrentSprite;
  // for each direction and each animation state
  typedef sf::Sprite ActorSprites[4][2];
  ActorSprites m_Sprites;

  float m_PreviousTime;
  float m_MoveTimeInterval;

  sf::Vector2i m_Position;
  sf::Vector2i m_NextPosition;

  Direction m_Direction;
  sf::Uint8 m_AnimationStage;
};
