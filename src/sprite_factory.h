#pragma once

class SpriteFactory
{
public:
  SpriteFactory();
  static SpriteFactory& Get();

  sf::Sprite CreateDotSprite() const;
  sf::Sprite CreateEnergizerSprite() const;
  sf::Sprite CreatePacmanInitialSprite() const;
  void CreateActorSprites(int actorIndex, sf::Sprite sprites[4][2]) const;

private:
  sf::Sprite CreateSprite(int x, int y) const;

  static SpriteFactory* m_Instance;

  sf::Texture m_Texture;
};
