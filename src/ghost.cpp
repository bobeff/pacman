#include "pch.h"
#include "ghost.h"
#include "game.h"

static const float MOVE_TIME = .15f;

Ghost::Ghost(Game& game, const sf::Vector2i& startPosition, const sf::Vector2i& target, int spritesIndex)
  : Actor(game, startPosition, spritesIndex, MOVE_TIME)
  , m_CameFrom(startPosition)
  , m_ScatterTargetTile(target)
{
  m_Modes[GhostMode::CHASE] = new ChaseMode(*this);
  m_Modes[GhostMode::SCATTER] = new ScatterMode(*this);
  m_Mode = m_Modes[GhostMode::CHASE];
}

Ghost::~Ghost()
{
  for (int i = 0; i < GhostMode::MODES_COUNT; ++i)
    delete m_Modes[i];
}

const sf::Vector2i& Ghost::GetTargetTile() const
{
  return m_Game.m_Pacman.GetPosition();
}

int Ghost::GetDistanceToTarget(const sf::Vector2i& position) const
{
  const sf::Vector2i& target = m_Mode->GetTargetTile();
#define SQR(X) ((X) * (X))
  return SQR(target.x - position.x) + SQR(target.y - position.y);
#undef SQR
}

bool Ghost::IsMovePossible(const sf::Vector2i& position) const
{
  char tile = m_Game.m_Maze.GetTile(position);
  char tileCameFrom = m_Game.m_Maze.GetTile(m_CameFrom);
  return tile != '#' && (tile != '-' || tile == '-' && tileCameFrom == '-');
}

void Ghost::UpdatePosition(float elapsedTime)
{
  m_CameFrom = m_Position;
  m_Position = m_NextPosition;

  static const sf::Vector2i STEP[4] =
  {
    sf::Vector2i( 1,  0), // east
    sf::Vector2i( 0,  1), // south
    sf::Vector2i(-1,  0), // west
    sf::Vector2i( 0, -1), // north
  };

  if (m_Mode->Change(elapsedTime))
  {
    m_NextPosition = m_CameFrom;
    m_Direction = Direction((int(m_Direction) + 2) % 4);
  }
  else
  {
    int minDistance = std::numeric_limits<int>::max();
    for (int i = 0; i < 4; ++i)
    {
      sf::Vector2i position = m_Position + STEP[i];
      Maze::TruncatePosition(position);

      // if the new position is unpassable tile or
      // it is the same tile from which we previously came from
      if (!IsMovePossible(position) || position == m_CameFrom)
        continue;

      int distance = GetDistanceToTarget(position);
      if (minDistance > distance)
      {
        minDistance = distance;
        m_NextPosition = position;
        m_Direction = Direction(i);
      }
    }
  }

  ++m_AnimationStage %= 2;
  SetCurrentSprite();
}
