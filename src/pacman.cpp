#include "pch.h"
#include "pacman.h"
#include "game.h"
#include "sprite_factory.h"

static const sf::Vector2i START_TILE(14, 26);
static const float MOVE_TIME = .14f;

Pacman::Pacman(Game& game)
  : Actor(game, START_TILE, 0, MOVE_TIME)
{
  NewDirection = Direction::NONE;
  m_Direction = Direction::NONE;
  m_InitialSprite = SpriteFactory::Get().CreatePacmanInitialSprite();
  SetInitialSpriteAsCurrent();
}

void Pacman::SetInitialSpriteAsCurrent()
{
  m_CurrentSprite = &m_InitialSprite;
  Maze::SetSpritePosition(*m_CurrentSprite, m_Position);
}

static void UpdatePosition(Direction direction, sf::Vector2i& position)
{
  switch (direction)
  {
    case Direction::WEST:  --position.x; break;
    case Direction::EAST:  ++position.x; break;
    case Direction::NORTH: --position.y; break;
    case Direction::SOUTH: ++position.y; break;
    default: assert(0);
  }

  Maze::TruncatePosition(position);
}

bool Pacman::IsMovePossible(const sf::Vector2i& position) const
{
  char tile = m_Game.m_Maze.GetTile(position);
  return tile != '#' && tile != '-';
}

void Pacman::UpdatePosition(float elapsedTime)
{
  if (NewDirection == Direction::NONE)
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
    SetCurrentSprite();
  }
  else
  {
    NewDirection = Direction::NONE;
    SetInitialSpriteAsCurrent();
  }
}
