#pragma once

class Game;

class Maze
{
public:
  Maze(Game& game);
  void Draw();
  void ConsumeTile(const sf::Vector2i& position);
  bool IsMovePossible(const sf::Vector2i& position) const;

  static void SetSpritePosition(sf::Sprite& sprite, int x, int y);
  static void SetSpritePosition(sf::Sprite& sprite, float x, float y);
  static void SetSpritePosition(sf::Sprite& sprite, const sf::Vector2i& position);
  static void SetSpritePosition(sf::Sprite& sprite, const sf::Vector2f& position);

  static const sf::Uint8 X_SIZE = 28;
  static const sf::Uint8 Y_SIZE = 36;
  static const sf::Uint8 TILE_SIZE = 16;

private:
  void LoadTiles();

  Game& m_Game;

  sf::Texture m_Texture;
  sf::Sprite m_Sprite;
  sf::Sprite m_DotSprite;
  sf::Sprite m_EnergizerSprite;

  char m_Tiles[Y_SIZE][X_SIZE];
};
