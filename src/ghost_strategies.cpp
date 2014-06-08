#include "pch.h"
#include "game.h"
#include "gameplay_constants.h"

static sf::Vector2i GetPositionBefore(const Pacman& pacman, int tilesCount)
{
  sf::Vector2i result = pacman.GetPosition();
  Direction dir = pacman.GetDirection();

  switch (dir)
  {
  case Direction::EAST:  result += sf::Vector2i(tilesCount, 0); break;
  case Direction::WEST:  result -= sf::Vector2i(tilesCount, 0); break;
  case Direction::NORTH: result -= sf::Vector2i(0, tilesCount); break;
  case Direction::SOUTH: result += sf::Vector2i(0, tilesCount); break;
  }

  return result;
}

sf::Vector2i RedGhostStrategy(const Game& game)
{
  return game.m_Pacman.GetPosition();
}

sf::Vector2i BlueGhostStrategy(const Game& game)
{
  sf::Vector2i twoTilesBeforePacman = GetPositionBefore(game.m_Pacman, 2);
  sf::Vector2i redGhostPosition = game.m_Ghosts[Ghost::RED]->GetPosition();
  // this is double of the vector between red ghost
  // and two tiles before pacman
  return 2 * twoTilesBeforePacman - redGhostPosition;
}

sf::Vector2i PinkGhostStrategy(const Game& game)
{
  return GetPositionBefore(game.m_Pacman, 4);
}

static double length(const sf::Vector2i& v)
{
  return sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2i OrangeGhostStrategy(const Game& game)
{
  const sf::Vector2i& ghostPosition =
    game.m_Ghosts[Ghost::ORANGE]->GetPosition();
  const sf::Vector2i& pacmanPosition = game.m_Pacman.GetPosition();
  double dist = length(ghostPosition - pacmanPosition);
  // if distance from ghost to pacman in smaller then 8 tiles the ghost target
  // tile is its scatter target or the pacman itself otherwise.
  return dist <= 8 ? ORANGE_GHOST_SCATTER_TARGET : pacmanPosition;
}
