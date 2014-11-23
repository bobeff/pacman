#pragma once

class Screen;

class Application
{
  friend class Game;

public:
  Application();
  ~Application();

  int Run();

  void NewGame();
  void BackToMainMenu();
  void Exit();

  void DrawText(const char* text,
                const sf::Vector2f& position,
                const sf::Color& color,
                sf::Uint32 style,
                unsigned size);

private:
  enum AppScreen
  {
    SCREEN_MAIN_MENU,
    SCREEN_GAME,
    SCREEN_COUNT,
  };

  void ChangeScreen(AppScreen screen);

  sf::RenderWindow m_Window;
  sf::Font m_Font;
  sf::Text m_Text;

  Screen* m_Screens[SCREEN_COUNT];
  Screen* m_CurrentScreen;
};
