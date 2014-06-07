#include "pch.h"
#include "ghost_strategies.h"
#include "game.h"

const sf::Vector2i RED_GHOST_START_TILE(14, 17);
const sf::Vector2i RED_GHOST_SCATTER_TARGET(25, 0);

const sf::Vector2i BLUE_GHOST_START_TILE(13, 17);
const sf::Vector2i BLUE_GHOST_SCATTER_TARGET(27, 35);

const sf::Vector2i PINK_GHOST_START_TILE(12, 17);
const sf::Vector2i PINK_GHOST_SCATTER_TARGET(2, 0);

const sf::Vector2i ORANGE_GHOST_START_TILE(15, 17);
const sf::Vector2i ORANGE_GHOST_SCATTER_TARGET(0, 35);

static sf::Vector2i GetPositionBefore(const Pacman& pacman, int tilesCount)
{
  sf::Vector2i result = pacman.GetPosition();
  Direction dir = pacman.GetDirection();

  switch (dir)
  {
  case Direction::EAST:  result -= sf::Vector2i(tilesCount, 0);
  case Direction::WEST:  result += sf::Vector2i(tilesCount, 0);
  case Direction::NORTH: result -= sf::Vector2i(0, tilesCount);
  case Direction::SOUTH: result += sf::Vector2i(0, tilesCount);
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
