#include "pch.h"
#include "maze.h"
#include "game.h"

Maze::Maze(Game& game) : m_Game(game)
{
  m_Texture.loadFromFile("assets/maze.png");
  m_Sprite.setTexture(m_Texture);
  m_Sprite.scale(2, 2);
}

void Maze::Draw() const
{
  m_Game.m_Window.draw(m_Sprite);
}
