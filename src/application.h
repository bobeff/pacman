#pragma once

#include "high_scores_data.h"

class Screen;

class Application
{
public:
  Application();
  ~Application();

  int Run();

  void NewGame();
  void BackToMainMenu();
  void ShowHighScores();
  void Exit();

  void DrawText(const char* text,
                const sf::Vector2f& position,
                const sf::Color& color,
                sf::Uint32 style,
                unsigned size);

  sf::RenderWindow& GetRenderWindow();
  HighScoresData& GetHighScores();

private:
  enum AppScreen
  {
    SCREEN_MAIN_MENU,
    SCREEN_GAME,
    SCREEN_HIGH_SCORES,
    SCREEN_COUNT,
  };

  void ChangeScreen(AppScreen screen);

  sf::RenderWindow m_Window;
  sf::Font m_Font;
  sf::Text m_Text;

  HighScoresData m_HighScores;

  Screen* m_Screens[SCREEN_COUNT];
  Screen* m_CurrentScreen;
};
