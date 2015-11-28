#include "pch.h"
#include "menu_item.h"
#include "application.h"

#define DEBUG_VISUALIZATIONS_ENABLED

MenuItem::MenuItem(Application& app,
                   const char* text,
                   const sf::Vector2f& position,
                   float boxWidth,
                   float selectedBoxWidth)
  : IsSelected(false)
  , m_App(app)
  , m_Text(text)
  , m_Position(position)
  , m_Rect(sf::Vector2f(boxWidth, 22.f))
  , m_SelectedRect(sf::Vector2f(selectedBoxWidth, 22.f))
{
  SetRectShapeProperties(m_Rect);
  SetRectShapeProperties(m_SelectedRect);
}

void MenuItem::Draw()
{
  static const sf::Color GRAY(127, 127, 127);

  const sf::Color& color = IsSelected ? sf::Color::White : GRAY;
  sf::Text::Style style = IsSelected ? sf::Text::Bold : sf::Text::Regular;
  m_App.DrawText(m_Text, m_Position, color, style, 30);

#ifdef DEBUG_VISUALIZATIONS_ENABLED
  sf::RenderWindow& window = m_App.GetRenderWindow();
  window.draw(m_Rect);
  window.draw(m_SelectedRect);
#endif
}

bool MenuItem::IsMouseOver(float x, float y)
{
  sf::RectangleShape& rect = IsSelected ? m_SelectedRect : m_Rect;
  const sf::Vector2f& position = rect.getPosition();
  const sf::Vector2f& size = rect.getSize();

  return x >= position.x && x <= position.x + size.x &&
         y >= position.y && y <= position.y + size.y;
}

void MenuItem::SetRectShapeProperties(sf::RectangleShape& rect)
{
  rect.setPosition(m_Position + sf::Vector2f(0, 8));
#ifdef DEBUG_VISUALIZATIONS_ENABLED
  rect.setFillColor(sf::Color::Transparent);
  rect.setOutlineColor(sf::Color::White);
  rect.setOutlineThickness(1);
#endif
}
