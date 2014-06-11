#include "pch.h"
#include "actor.h"
#include "game.h"
#include "sprite_factory.h"

Actor::Actor(Game& game, const sf::Vector2i& startPosition, int spritesIndex)
  : m_Game(game)
  , m_PreviousTime(0.f)
  , m_StartPosition(startPosition)
  , m_Position(m_StartPosition)
  , m_NextPosition(m_Position)
  , m_Direction(Direction::WEST)
  , m_AnimationStage(1)
  , m_CurrentSpritesArray(&m_Sprites)
{
  SpriteFactory::Get().CreateActorSprites(spritesIndex, m_Sprites);
  SetCurrentSprite();
}

void Actor::Draw() const
{
  m_Game.m_Window.draw(*m_CurrentSprite);
}

void Actor::SetCurrentSprite()
{
  assert(m_Direction != Direction::NONE);
  m_CurrentSprite =
    &((*m_CurrentSpritesArray)[int(m_Direction)][m_AnimationStage]);
  Maze::SetPosition(*m_CurrentSprite, m_Position);
}

const sf::Vector2i& Actor::GetPosition() const
{
  return m_Position;
}

const sf::Vector2f& Actor::GetSpritePosition() const
{
  return m_CurrentSprite->getPosition();
}

Direction Actor::GetDirection() const
{
  return m_Direction;
}

const sf::Vector2i& Actor::GetStartTile() const
{
  return m_StartPosition;
}

void Actor::UpdateAnimation(float deltaTime)
{
  if (m_Position == m_NextPosition)
    return;

  float deltaMove = deltaTime / GetMoveTimeInterval();
  sf::Vector2f position(m_Position);

  switch (m_Direction)
  {
    case Direction::WEST:  position.x -= deltaMove; break;
    case Direction::EAST:  position.x += deltaMove; break;
    case Direction::NORTH: position.y -= deltaMove; break;
    case Direction::SOUTH: position.y += deltaMove; break;
    default: assert(0);
  }

  Maze::SetPosition(*m_CurrentSprite, position);
}

void Actor::Update(float elapsedTime)
{
  float deltaTime = elapsedTime - m_PreviousTime;

  if (deltaTime < GetMoveTimeInterval())
  {
    UpdateAnimation(deltaTime);
  }
  else
  {
    m_PreviousTime = elapsedTime;
    UpdatePosition(elapsedTime);
    SetCurrentSprite();
  }
}
