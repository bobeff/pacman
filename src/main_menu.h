#pragma once

#include "screen.h"

class Application;
class MenuItem;

class MainMenu : public Screen
{
  friend class MenuItem;

public:
  MainMenu(Application& app);
  virtual ~MainMenu();

  virtual void ProcessInput(const sf::Event& event);
  virtual void Update();
  virtual void Draw();
  virtual void ResetScreen();

private:
  void ProcessKeyboardInput(const sf::Event::KeyEvent& keyEvent);
  void ProcessMouseMove(const sf::Event::MouseMoveEvent& event);
  void ProcessMousePress(const sf::Event::MouseButtonEvent& event);

  void ChangeSelectedItem(int newItemIndex);

  enum Item
  {
    ITEM_NEW_GAME,
    ITEM_HIGH_SCORES,
    ITEM_CONTROLS,
    ITEM_SETTINGS,
    ITEM_EXIT,
    ITEMS_COUNT,
  };

  MenuItem* m_Items[ITEMS_COUNT];
  sf::Uint8 m_CurrentItemIndex;
  bool m_IsItemChoosed;
};
