#pragma once

class Application;

class MenuItem
{
public:
  MenuItem(Application& app,
           const char* text,
           const sf::Vector2f& position,
           float boxWidth,
           float selectedBoxWidth);

  void Draw();
  bool IsMouseOver(float x, float y);

  bool IsSelected;

private:
  void SetRectShapeProperties(sf::RectangleShape& rect);

  Application& m_App;
  const char* m_Text;
  const sf::Vector2f m_Position;
  sf::RectangleShape m_Rect;
  sf::RectangleShape m_SelectedRect;
};
