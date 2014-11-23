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

  virtual void ProcessInput(const sf::Event::KeyEvent& key);
  virtual void Update();
  virtual void Draw();
  virtual void ResetScreen();

private:
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
