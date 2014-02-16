#include "pch.h"
#include "sprite_factory.h"

SpriteFactory::SpriteFactory()
{
  m_Texture.loadFromFile("assets/spritesheet.png");
}

sf::Sprite SpriteFactory::CreateDotSprite() const
{
  return CreateSprite(0, 8);
}

sf::Sprite SpriteFactory::CreateEnergizerSprite() const
{
  return CreateSprite(1, 8);
}

sf::Sprite SpriteFactory::CreatePacmanInitialSprite() const
{
  return CreateSprite(8, 0);
}

void SpriteFactory::CreateActorSprites(int actorIndex, sf::Sprite sprites[4][2]) const
{
  for (int i = 0; i < 8; ++i)
    sprites[i / 2][i % 2] = CreateSprite(i, actorIndex);
}

sf::Sprite SpriteFactory::CreateSprite(int x, int y) const
{
  sf::Sprite sprite(m_Texture, sf::IntRect(x * 8, y * 8, 8, 8));
  sprite.setScale(2, 2);
  return sprite;
}

SpriteFactory& SpriteFactory::Get()
{
  if (!s_Instance)
    s_Instance = new SpriteFactory();
  return *s_Instance;
}

SpriteFactory* SpriteFactory::s_Instance = nullptr;
