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

sf::Sprite SpriteFactory::CreateSprite(int x, int y) const
{
  sf::Sprite sprite(m_Texture, sf::IntRect(x * 8, y * 8, 8, 8));
  sprite.setScale(2, 2);
  return sprite;
}

SpriteFactory& SpriteFactory::Get()
{
  if (!m_Instance)
    m_Instance = new SpriteFactory();
  return *m_Instance;
}

SpriteFactory* SpriteFactory::m_Instance = nullptr;
