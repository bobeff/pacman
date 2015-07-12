#include "pch.h"
#include "main_menu.h"
#include "application.h"

#define DEBUG_VISUALIZATIONS_ENABLED 

class MenuItem
{
public:
  MenuItem(Application& app,
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

  void Draw()
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

  bool IsSelected;

  bool IsMouseOver(float x, float y)
  {
    sf::RectangleShape& rect = IsSelected ? m_SelectedRect : m_Rect;
    const sf::Vector2f& position = rect.getPosition();
    const sf::Vector2f& size = rect.getSize();

    return x >= position.x && x <= position.x + size.x &&
           y >= position.y && y <= position.y + size.y;
  }

private:
  void SetRectShapeProperties(sf::RectangleShape& rect)
  {
    rect.setPosition(m_Position + sf::Vector2f(0, 8));
#ifdef DEBUG_VISUALIZATIONS_ENABLED
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(1);
#endif
  }

  Application& m_App;
  const char* m_Text;
  const sf::Vector2f m_Position;
  sf::RectangleShape m_Rect;
  sf::RectangleShape m_SelectedRect;
};

MainMenu::MainMenu(Application& app) : Screen(app)
{
  m_Items[ITEM_NEW_GAME] = new MenuItem(
    m_App, "NEW GAME", sf::Vector2f(110, 230), 165, 173);

  m_Items[ITEM_HIGH_SCORES] = new MenuItem(
    m_App, "HIGH SCORES", sf::Vector2f(110, 270), 207, 219);

  m_Items[ITEM_CONTROLS] = new MenuItem(
    m_App, "CONTROLS", sf::Vector2f(110, 310), 166, 175);

  m_Items[ITEM_SETTINGS] = new MenuItem(
    m_App, "SETTINGS", sf::Vector2f(110, 350), 150, 157);

  m_Items[ITEM_EXIT] = new MenuItem(
    m_App, "EXIT", sf::Vector2f(110, 390), 63, 68);

  m_Items[ITEM_NEW_GAME]->IsSelected = true;

  ResetScreen();
}

MainMenu::~MainMenu()
{
  for (int i = 0; i < ITEMS_COUNT; ++i)
  {
    delete m_Items[i];
  }
}

void MainMenu::ProcessInput(const sf::Event& event)
{
  switch (event.type)
  {
  case sf::Event::KeyPressed:
    ProcessKeyboardInput(event.key);
    break;
  case sf::Event::MouseMoved:
    ProcessMouseMove(event.mouseMove);
    break;
  case sf::Event::MouseButtonPressed:
    ProcessMousePress(event.mouseButton);
    break;
  }
}

void MainMenu::changeSelectedItem(int newItemIndex)
{
  assert(newItemIndex >= 0 && newItemIndex < ITEMS_COUNT);
  assert(m_Items[m_CurrentItemIndex]->IsSelected);

  m_Items[m_CurrentItemIndex]->IsSelected = false;
  m_CurrentItemIndex = newItemIndex;
  m_Items[m_CurrentItemIndex]->IsSelected = true;
}

void MainMenu::ProcessMouseMove(const sf::Event::MouseMoveEvent& event)
{
  for (int i = 0; i < ITEMS_COUNT; ++i)
  {
    if (m_Items[i]->IsMouseOver(float(event.x), float(event.y)))
    {
      changeSelectedItem(i);
      break;
    }
  }
}

void MainMenu::ProcessMousePress(const sf::Event::MouseButtonEvent& event)
{
  if (sf::Mouse::Left != event.button)
    return;

#ifdef _DEBUG
  printf("(%d, %d)\n", event.x, event.y);
#endif

  for (int i = 0; i < ITEMS_COUNT; ++i)
  {
    if (m_Items[i]->IsMouseOver(float(event.x), float(event.y)))
    {
      m_IsItemChoosed = true;
    }
  }
}

void MainMenu::ProcessKeyboardInput(const sf::Event::KeyEvent& keyEvent)
{
  switch (keyEvent.code)
  {
  case sf::Keyboard::Down:
  case sf::Keyboard::S:
    if (m_CurrentItemIndex < ITEMS_COUNT - 1)
      changeSelectedItem(m_CurrentItemIndex + 1);
    break;
  case sf::Keyboard::Up:
  case sf::Keyboard::W:
    if (m_CurrentItemIndex > 0)
      changeSelectedItem(m_CurrentItemIndex - 1);
    break;
  case sf::Keyboard::Return:
  case sf::Keyboard::Space:
    m_IsItemChoosed = true;
    break;
  case sf::Keyboard::Escape:
    m_App.Exit();
    break;
  }
}

void MainMenu::Update()
{
  if (!m_IsItemChoosed)
    return;

  switch (m_CurrentItemIndex)
  {
  case ITEM_NEW_GAME:
    m_App.NewGame();
    break;
  case ITEM_EXIT:
    m_App.Exit();
    break;
  }

  m_IsItemChoosed = false;
}

void MainMenu::Draw()
{
  m_App.DrawText("PACMAN", sf::Vector2f(30, 30), sf::Color::Blue,
    sf::Text::Bold | sf::Text::Underlined, 90);

  for (int i = 0; i < ITEMS_COUNT; ++i)
  {
    m_Items[i]->Draw();
  }
}

void MainMenu::ResetScreen()
{
  m_CurrentItemIndex = ITEM_NEW_GAME;
  m_IsItemChoosed = false;
}
