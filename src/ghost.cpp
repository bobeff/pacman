#include "pch.h"
#include "ghost.h"
#include "game.h"

static const float MOVE_TIME = .15f;
static const float CHASE_TIME = 20.f;
static const float SCATTER_TIME = 10.f;

Ghost::Ghost(Game& game, const sf::Vector2i& startPosition, const sf::Vector2i& target, int spritesIndex)
  : Actor(game, startPosition, spritesIndex, MOVE_TIME)
  , m_CameFrom(startPosition)
  , m_ScatterTargetTile(target)
  , m_Mode(Mode::CHASE)
  , m_ModeStartTime(0.f)
{
}

const sf::Vector2i& Ghost::GetTargetTile() const
{
  switch (m_Mode)
  {
    case Mode::CHASE: return m_Game.m_Pacman.GetPosition();
    case Mode::SCATTER: return m_ScatterTargetTile;
    default: assert(0);
  }

  static const sf::Vector2i ZERO;
  return ZERO;
}

int Ghost::GetDistanceToTarget(const sf::Vector2i& position) const
{
  const sf::Vector2i& target = GetTargetTile();
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

bool Ghost::CheckModeChange(float elapsedTime)
{
  float deltaTime = elapsedTime - m_ModeStartTime;
  
  switch (m_Mode)
  {
    case Mode::CHASE:
      if (deltaTime >= CHASE_TIME)
      {
        m_Mode = Mode::SCATTER;
        m_ModeStartTime = elapsedTime;
        return true;
      }
      break;
    case Mode::SCATTER:
      if (deltaTime >= SCATTER_TIME)
      {
        m_Mode = Mode::CHASE;
        m_ModeStartTime = elapsedTime;
        return true;
      }
      break;
    default: assert(0);
  }

  return false;
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

  if (CheckModeChange(elapsedTime))
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
