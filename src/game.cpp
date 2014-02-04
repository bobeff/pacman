#include "pch.h"
#include "game.h"

Game::Game() : m_Maze(*this)
{
  m_Window.create(sf::VideoMode(448, 576), "Pacman", sf::Style::Titlebar | sf::Style::Close);
  m_Window.setVerticalSyncEnabled(true);
}

int Game::Run()
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
        goto end_game;
      }
    }

    m_Window.clear(sf::Color::Black);
    m_Maze.Draw();
    m_Window.display();
  }

end_game:
  return 0;
}
