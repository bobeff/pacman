#include "pch.h"
#include "ghost_startegies.h"
#include "pacman.h"

GhostStrategy::GhostStrategy(const Pacman& pacman)
  : m_Pacman(pacman)
{
}

RedGhostStrategy::RedGhostStrategy(const Pacman& pacman)
  : GhostStrategy(pacman)
{
}

sf::Vector2i RedGhostStrategy::GetTargetTile() const
{
  return m_Pacman.GetPosition();
}

PinkGhostStrategy::PinkGhostStrategy(const Pacman& pacman)
  : GhostStrategy(pacman)
{
}

sf::Vector2i PinkGhostStrategy::GetTargetTile() const
{
  sf::Vector2i result = m_Pacman.GetPosition();
  Direction dir = m_Pacman.GetDirection();

  switch (dir)
  {
  case Direction::EAST:  result -= sf::Vector2i(4, 0);
  case Direction::WEST:  result += sf::Vector2i(4, 0);
  case Direction::NORTH: result -= sf::Vector2i(0, 4);
  case Direction::SOUTH: result += sf::Vector2i(0, 4);
  }

  return result;
}
