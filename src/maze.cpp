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
  Reset();
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

  if (tile == '.')
  {
    ++m_TilesConsumed;
    m_Game.m_Score += 10;
  }
  else if (tile == '@')
  {
    ++m_TilesConsumed;
    m_Game.m_Score += 100;
    m_Game.SetGhostsToRunMode();
    m_Game.m_EatenGhostsCount = 0;
  }

  tile = ' ';

  if (m_TilesConsumed == m_ConsumableTilesCount)
  {
    m_Game.m_State = Game::STATE_WINNING;
  }
}

char Maze::GetTile(const sf::Vector2i& position) const
{
  AssertPositionInRange(position);
  return m_Tiles[position.y][position.x];
}

void Maze::Reset()
{
  m_TilesConsumed = 0;
  memcpy(m_Tiles, m_InitialTiles, sizeof(Tiles));
}

void Maze::LoadTiles()
{
  FILE* finp = fopen("assets/maze.txt", "r");

  m_ConsumableTilesCount = 0;

  for (int y = 0; y < Y_SIZE; ++y)
  {
    for (int x = 0; x < X_SIZE; ++x)
    {
      fscanf(finp, "%c", &m_InitialTiles[y][x]);

      if (m_InitialTiles[y][x] == '.' || m_InitialTiles[y][x] == '@')
      {
        ++m_ConsumableTilesCount;
      }
    }

    // skip new line
    char newLine;
    fscanf(finp, "%c", &newLine);
  }

  fclose(finp);
}

void Maze::Draw()
{
  sf::RenderWindow& window = m_Game.GetRenderWindow();

  window.draw(m_Sprite);

  sf::Sprite* sprite;
  for (int y = 0; y < Y_SIZE; ++y)
  {
    for (int x = 0; x < X_SIZE; ++x)
    {
      switch (m_Tiles[y][x])
      {
        case '.': sprite = &m_DotSprite; break;
        case '@': sprite = &m_EnergizerSprite; break;
        default: sprite = 0;
      }

      if (!sprite) continue;
      SetPosition(*sprite, x, y);
      window.draw(*sprite);
    }
  }
}

void Maze::SetPosition(sf::Transformable& object, float x, float y)
{
  object.setPosition(x * TILE_SIZE, y * TILE_SIZE);
}

void Maze::SetPosition(sf::Transformable& object, int x, int y)
{
  SetPosition(object, float(x), float(y));
}

void Maze::SetPosition(sf::Transformable& object, const sf::Vector2i& position)
{
  SetPosition(object, position.x, position.y);
}

void Maze::SetPosition(sf::Transformable& object, const sf::Vector2f& position)
{
  SetPosition(object, position.x, position.y);
}

void Maze::TruncatePosition(sf::Vector2i& position)
{
  if (position.x < 0) position.x = Maze::X_SIZE - 1;
  if (position.x >= Maze::X_SIZE) position.x = 0;
}
