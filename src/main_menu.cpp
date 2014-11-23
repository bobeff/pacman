#include "pch.h"
#include "main_menu.h"
#include "application.h"

class MenuItem
{
public:
  MenuItem(MainMenu& menu,
           MainMenu::Item item,
           const char* text,
           const sf::Vector2f& position)
    : m_Menu(menu)
    , m_Item(item)
    , m_Text(text)
    , m_Position(position)
  {
  }

  void Draw()
  {
    static const sf::Color GRAY(127, 127, 127);

    bool isSelected = m_Item == m_Menu.m_CurrentItemIndex;
    const sf::Color& color = isSelected ? sf::Color::White : GRAY;
    sf::Text::Style style = isSelected ? sf::Text::Bold : sf::Text::Regular;
    m_Menu.m_App.DrawText(m_Text, m_Position, color, style, 30);
  }

protected:
  MainMenu& m_Menu;
  MainMenu::Item m_Item;
  const char* m_Text;
  const sf::Vector2f m_Position;
};

MainMenu::MainMenu(Application& app) : Screen(app)
{
  m_Items[ITEM_NEW_GAME] = new MenuItem(
    *this, ITEM_NEW_GAME, "NEW GAME", sf::Vector2f(110, 230));

  m_Items[ITEM_HIGH_SCORES] = new MenuItem(
    *this, ITEM_HIGH_SCORES, "HIGH SCORES", sf::Vector2f(110, 270));

  m_Items[ITEM_CONTROLS] = new MenuItem(
    *this, ITEM_CONTROLS, "CONTROLS", sf::Vector2f(110, 310));

  m_Items[ITEM_SETTINGS] = new MenuItem(
    *this, ITEM_SETTINGS, "SETTINGS", sf::Vector2f(110, 350));

  m_Items[ITEM_EXIT] = new MenuItem(
    *this, ITEM_EXIT, "EXIT", sf::Vector2f(110, 390));

  ResetScreen();
}

MainMenu::~MainMenu()
{
  for (int i = 0; i < ITEMS_COUNT; ++i)
  {
    delete m_Items[i];
  }
}

void MainMenu::ProcessInput(const sf::Event::KeyEvent& key)
{
  switch (key.code)
  {
  case sf::Keyboard::Down:
  case sf::Keyboard::S:
    if (m_CurrentItemIndex < ITEMS_COUNT - 1)
      ++m_CurrentItemIndex;
    m_IsItemChoosed = false;
    break;
  case sf::Keyboard::Up:
  case sf::Keyboard::W:
    if (m_CurrentItemIndex > 0)
      --m_CurrentItemIndex;
    m_IsItemChoosed = false;
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
