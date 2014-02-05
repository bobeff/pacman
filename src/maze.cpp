#include "pch.h"
#include "maze.h"
#include "game.h"
#include "sprite_factory.h"

Maze::Maze(Game& game) : m_Game(game)
{
  m_Texture.loadFromFile("assets/maze.png");
  m_Sprite.setTexture(m_Texture);
  m_Sprite.scale(2, 2);
  SpriteFactory& factory = SpriteFactory::Get();
  m_DotSprite = factory.CreateDotSprite();
  m_EnergizerSprite = factory.CreateEnergizerSprite();
  LoadTiles();
}

void Maze::LoadTiles()
{
  FILE* finp = fopen("assets/maze.txt", "r");
  for (int y = 0; y < Y_SIZE; ++y)
  {
    for (int x = 0; x < X_SIZE; ++x)
      fscanf(finp, "%c", &m_Tiles[y][x]);
    // skip new line
    char newLine;
    fscanf(finp, "%c", &newLine);
  }
  fclose(finp);
}

void Maze::Draw()
{
  m_Game.m_Window.draw(m_Sprite);

  sf::Sprite* sprite;
  for (int y = 0; y < Y_SIZE; ++y)
  {
    for (int x = 0; x < X_SIZE; ++x)
    {
      switch (m_Tiles[y][x])
      {
      case '.': sprite = &m_DotSprite; break;
      case '@': sprite = &m_EnergizerSprite; break;
      default: sprite = nullptr;
      }

      if (!sprite) continue;
      sprite->setPosition(float(x * 16), float(y * 16));
      m_Game.m_Window.draw(*sprite);
    }
  }
}
