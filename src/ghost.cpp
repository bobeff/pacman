#include "pch.h"
#include "ghost.h"
#include "game.h"

Ghost::Ghost(Game& game, sf::Vector2i& startPosition, int spritesIndex)
  : Actor(game, startPosition, spritesIndex, .15f)
  , m_CameFrom(startPosition)
{
}

int Ghost::GetDistanceToTarget(const sf::Vector2i& position) const
{
  const sf::Vector2i& target = m_Game.m_Pacman.GetPosition();
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

void Ghost::UpdatePosition()
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

  int minDistance = std::numeric_limits<int>::max();
  for (int i = 0; i < 4; ++i)
  {
    sf::Vector2i position = m_Position + STEP[i];

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

  ++m_AnimationStage %= 2;
  SetCurrentSprite();
}
