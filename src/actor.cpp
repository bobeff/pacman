#include "pch.h"
#include "actor.h"
#include "game.h"
#include "sprite_factory.h"

Actor::Actor(Game& game, const sf::Vector2i& startPosition, int imagesIndex, float moveTimeInterval)
  : m_Game(game)
  , m_PreviousTime(0.f)
  , m_MoveTimeInterval(moveTimeInterval)
  , m_Position(startPosition)
  , m_NextPosition(m_Position)
  , m_Direction(Direction::WEST)
  , m_AnimationStage(1)
{
  SpriteFactory::Get().CreateActorSprites(imagesIndex, m_Sprites);
  SetCurrentSprite();
}

void Actor::Draw() const
{
  m_Game.m_Window.draw(m_CurrentSprite);
}

void Actor::SetCurrentSprite()
{
  m_CurrentSprite = m_Sprites[int(m_Direction)][m_AnimationStage];
  Maze::SetSpritePosition(m_CurrentSprite, m_Position);
}

const sf::Vector2i& Actor::GetPosition() const
{
  return m_Position;
}

void Actor::UpdateAnimation(float deltaTime)
{
  if (m_Position == m_NextPosition)
    return;

  float deltaMove = deltaTime / m_MoveTimeInterval;
  sf::Vector2f position(m_Position);

  switch (m_Direction)
  {
  case Direction::WEST: position.x -= deltaMove; break;
  case Direction::EAST: position.x += deltaMove; break;
  case Direction::NORTH: position.y -= deltaMove; break;
  case Direction::SOUTH: position.y += deltaMove; break;
  default: assert(0);
  }

  Maze::SetSpritePosition(m_CurrentSprite, position);
}

void Actor::Update(float elapsedTime)
{
  float deltaTime = elapsedTime - m_PreviousTime;
  
  if (deltaTime < m_MoveTimeInterval)
    UpdateAnimation(deltaTime);
  else
  {
    m_PreviousTime = elapsedTime;
    UpdatePosition();
  }
}
