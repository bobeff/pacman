#pragma once

class Game;

class Maze
{
public:
  Maze(Game& game);
  void Draw() const;

private:
  Game& m_Game;

  sf::Texture m_Texture;
  sf::Sprite m_Sprite;
};
