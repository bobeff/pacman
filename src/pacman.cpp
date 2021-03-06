#include "pch.h"
#include "pacman.h"
#include "game.h"
#include "sprite_factory.h"
#include "gameplay_constants.h"

Pacman::Pacman(Game& game)
  : Actor(game, PACMAN_START_TILE, 0)
  , NewDirection(DIRECTION_NONE)
  , m_MoveTimeInterval(PACMAN_MOVE_TIME)
{
  m_Direction = DIRECTION_NONE;
  m_InitialSprite = SpriteFactory::Get().CreatePacmanInitialSprite();
  SetCurrentSprite();
}

void Pacman::Reset()
{
  Actor::Reset();
  NewDirection = DIRECTION_NONE;
  m_Direction = DIRECTION_NONE;
  SetCurrentSprite();
}

sf::Vector2i Pacman::GetPositionAhead(int tilesCount) const
{
  sf::Vector2i position = m_Position;

  switch (m_Direction)
  {
  case DIRECTION_EAST:  position += sf::Vector2i(tilesCount, 0); break;
  case DIRECTION_WEST:  position -= sf::Vector2i(tilesCount, 0); break;
  case DIRECTION_NORTH: position -= sf::Vector2i(0, tilesCount); break;
  case DIRECTION_SOUTH: position += sf::Vector2i(0, tilesCount); break;
  }

  return position;
}

void Pacman::SetCurrentSprite()
{
  if (m_Direction == DIRECTION_NONE)
  {
    m_CurrentSprite = &m_InitialSprite;
    Maze::SetPosition(*m_CurrentSprite, m_Position);
  }
  else
  {
    Actor::SetCurrentSprite();
  }
}

static void UpdatePosition(Direction direction, sf::Vector2i& position)
{
  switch (direction)
  {
  case DIRECTION_WEST:  --position.x; break;
  case DIRECTION_EAST:  ++position.x; break;
  case DIRECTION_NORTH: --position.y; break;
  case DIRECTION_SOUTH: ++position.y; break;
  }

  Maze::TruncatePosition(position);
}

float Pacman::GetMoveTimeInterval() const
{
  return m_MoveTimeInterval;
}

bool Pacman::IsMovePossible(const sf::Vector2i& position) const
{
  char tile = m_Game.m_Maze.GetTile(position);
  return tile != '#' && tile != '-';
}

void Pacman::UpdatePosition(float elapsedTime)
{
  if (NewDirection == DIRECTION_NONE)
    return;

  if (m_Position != m_NextPosition)
  {
    m_Position = m_NextPosition;
    m_Game.m_Maze.ConsumeTile(m_Position);
  }

  sf::Vector2i newPosition = m_Position;
  ::UpdatePosition(NewDirection, newPosition);
  if (IsMovePossible(newPosition))
    m_Direction = NewDirection;

  newPosition = m_Position;
  ::UpdatePosition(m_Direction, newPosition);

  if (IsMovePossible(newPosition))
  {
    m_NextPosition = newPosition;
    ++m_AnimationStage %= 2;
  }
  else
  {
    NewDirection = DIRECTION_NONE;
  }
}
