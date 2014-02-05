#pragma once

class Game;

class Maze
{
public:
  Maze(Game& game);
  void Draw();

private:
  void LoadTiles();

  Game& m_Game;

  sf::Texture m_Texture;
  sf::Sprite m_Sprite;
  sf::Sprite m_DotSprite;
  sf::Sprite m_EnergizerSprite;

  static const uint8_t X_SIZE = 28;
  static const uint8_t Y_SIZE = 36;

  char m_Tiles[Y_SIZE][X_SIZE];
};
