#include "pch.h"
#include "application.h"
#include "game.h"
#include "main_menu.h"

Application::Application()
{
  m_Screens[SCREEN_GAME] = new Game(*this);
  m_Screens[SCREEN_MAIN_MENU] = new MainMenu(*this);
  m_CurrentScreen = m_Screens[SCREEN_MAIN_MENU];

  static const int WINDOW_WIDTH  = 448;
  static const int WINDOW_HEIGHT = 576;

  m_Window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
    "Pacman", sf::Style::Titlebar | sf::Style::Close);
  m_Window.setVerticalSyncEnabled(true);

  sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

  // center the window on the screen
  m_Window.setPosition(sf::Vector2i(
    videoMode.width  / 2 - WINDOW_WIDTH  / 2,
    videoMode.height / 2 - WINDOW_HEIGHT / 2));

  m_Font.loadFromFile("assets/arial.ttf");
  m_Text.setFont(m_Font);
}

Application::~Application()
{
  for (int i = 0; i < SCREEN_COUNT; ++i)
  {
    delete m_Screens[i];
  }
}

void Application::NewGame()
{
  ChangeScreen(SCREEN_GAME);
}

void Application::BackToMainMenu()
{
  ChangeScreen(SCREEN_MAIN_MENU);
}

void Application::Exit()
{
  m_CurrentScreen = 0;
}

void Application::ChangeScreen(AppScreen screen)
{
  m_CurrentScreen = m_Screens[screen];
  m_CurrentScreen->ResetScreen();
}

int Application::Run()
{
  while (m_Window.isOpen())
  {
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
      switch (event.type)
      {
      case sf::Event::Closed:
        m_Window.close();
        break;
      case sf::Event::KeyPressed:
        m_CurrentScreen->ProcessInput(event.key);
        break;
      }
    }

    m_CurrentScreen->Update();
    if (m_CurrentScreen == 0)
      goto end_game;

    m_Window.clear(sf::Color::Black);
    m_CurrentScreen->Draw();
    m_Window.display();
  }

end_game:
  return 0;
}

void Application::DrawText(const char* text,
                           const sf::Vector2f& position,
                           const sf::Color& color,
                           sf::Uint32 style,
                           unsigned size)
{
  m_Text.setString(text);
  m_Text.setPosition(position);
  m_Text.setColor(color);
  m_Text.setStyle(style);
  m_Text.setCharacterSize(size);
  m_Window.draw(m_Text);
}
