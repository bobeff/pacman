#include "pch.h"
#include "main_menu.h"
#include "application.h"
#include "menu_item.h"

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

void MainMenu::ChangeSelectedItem(int newItemIndex)
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
      ChangeSelectedItem(i);
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
      ChangeSelectedItem(m_CurrentItemIndex + 1);
    break;
  case sf::Keyboard::Up:
  case sf::Keyboard::W:
    if (m_CurrentItemIndex > 0)
      ChangeSelectedItem(m_CurrentItemIndex - 1);
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
  case ITEM_HIGH_SCORES:
    m_App.ShowHighScores();
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
