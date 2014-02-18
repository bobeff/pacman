#pragma once

class SpriteFactory
{
public:
  static SpriteFactory& Get();

  sf::Sprite CreateDotSprite() const;
  sf::Sprite CreateEnergizerSprite() const;
  sf::Sprite CreatePacmanInitialSprite() const;
  void CreateActorSprites(int actorIndex, sf::Sprite sprites[4][2]) const;

private:
  SpriteFactory();
  sf::Sprite CreateSprite(int x, int y) const;

  // make SpriteFactory non copyable
  SpriteFactory(const SpriteFactory&);
  SpriteFactory& operator=(const SpriteFactory&);

  static SpriteFactory* s_Instance;

  sf::Texture m_Texture;
};
