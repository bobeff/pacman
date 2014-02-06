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

static void AssertPositionInRange(const sf::Vector2i& position)
{
  assert(position.x >= 0 && position.x < Maze::X_SIZE);
  assert(position.y >= 0 && position.y < Maze::Y_SIZE);
}

void Maze::ConsumeTile(const sf::Vector2i& position)
{
  AssertPositionInRange(position);
  char& tile = m_Tiles[position.y][position.x];
  assert(tile != '#');
  tile = ' ';
}

bool Maze::IsMovePossible(const sf::Vector2i& position) const
{
  AssertPositionInRange(position);
  return m_Tiles[position.y][position.x] != '#';
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
      SetSpritePosition(*sprite, x, y);
      m_Game.m_Window.draw(*sprite);
    }
  }
}

void Maze::SetSpritePosition(sf::Sprite& sprite, float x, float y)
{
  sprite.setPosition(x * 16, y * 16);
}

void Maze::SetSpritePosition(sf::Sprite& sprite, int x, int y)
{
  SetSpritePosition(sprite, float(x), float(y));
}

void Maze::SetSpritePosition(sf::Sprite& sprite, const sf::Vector2i& position)
{
  SetSpritePosition(sprite, position.x, position.y);
}

void Maze::SetSpritePosition(sf::Sprite& sprite, const sf::Vector2f& position)
{
  SetSpritePosition(sprite, position.x, position.y);
}
