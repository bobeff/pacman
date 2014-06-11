#pragma once

class Game;

enum Direction
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
  Actor(Game& game, const sf::Vector2i& startPosition, int spritesIndex);
  virtual ~Actor() {}

  virtual void Draw() const;
  virtual void Update(float elapsedTime);

  const sf::Vector2i& GetPosition() const;
  const sf::Vector2f& GetSpritePosition() const;
  Direction GetDirection() const;
  const sf::Vector2i& GetStartTile() const;

protected:
  void UpdateAnimation(float deltaTime);
  virtual void SetCurrentSprite();
  virtual void UpdatePosition(float elapsedTime) = 0;
  virtual float GetMoveTimeInterval() const = 0;

  Game& m_Game;

  sf::Sprite* m_CurrentSprite;

  // for each direction and each animation state
  typedef sf::Sprite ActorSprites[4][2];
  ActorSprites m_Sprites;
  ActorSprites* m_CurrentSpritesArray;

  float m_PreviousTime;

  sf::Vector2i m_StartPosition;
  sf::Vector2i m_Position;
  sf::Vector2i m_NextPosition;

  Direction m_Direction;
  sf::Uint8 m_AnimationStage;
};
