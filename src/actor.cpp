#include "pch.h"
#include "actor.h"
#include "game.h"
#include "sprite_factory.h"

Actor::Actor(Game& game, const sf::Vector2i& startPosition, int spritesIndex)
  : m_Game(game)
  , m_CurrentSpritesArray(&m_Sprites)
  , m_StartPosition(startPosition)
  , m_Position(m_StartPosition)
  , m_NextPosition(m_Position)
  , m_Direction(DIRECTION_NORTH)
  , m_AnimationStage(1)
{
  SpriteFactory::Get().CreateActorSprites(spritesIndex, m_Sprites);
  SetCurrentSprite();
}

void Actor::Reset()
{
  m_PreviousTime = 0.0f;
  m_Position = m_StartPosition;
  m_NextPosition = m_Position;
  m_Direction = DIRECTION_NORTH;
  m_AnimationStage = 1;
  m_CurrentSpritesArray = &m_Sprites;
  SetCurrentSprite();
}

void Actor::Draw() const
{
  m_Game.m_Window.draw(*m_CurrentSprite);
}

void Actor::SetCurrentSprite()
{
  assert(m_Direction != DIRECTION_NONE);
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
    case DIRECTION_WEST:  position.x -= deltaMove; break;
    case DIRECTION_EAST:  position.x += deltaMove; break;
    case DIRECTION_NORTH: position.y -= deltaMove; break;
    case DIRECTION_SOUTH: position.y += deltaMove; break;
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
