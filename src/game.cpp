#include "pch.h"
#include "game.h"

Game::Game()
  : m_Maze(*this)
  , m_Pacman(*this)
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
        switch (event.key.code)
        {
        case sf::Keyboard::Escape:
          goto end_game;
        case sf::Keyboard::Left:
        case sf::Keyboard::A:
          m_Pacman.NewDirection = Direction::WEST;
          break;
        case sf::Keyboard::Right:
        case sf::Keyboard::D:
          m_Pacman.NewDirection = Direction::EAST;
          break;
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
          m_Pacman.NewDirection = Direction::NORTH;
          break;
        case sf::Keyboard::Down:
        case sf::Keyboard::S:
          m_Pacman.NewDirection = Direction::SOUTH;
          break;
        }
      }
    }

    float elapsedTime = m_Clock.getElapsedTime().asSeconds();
    m_Pacman.Update(elapsedTime);

    m_Window.clear(sf::Color::Black);
    m_Maze.Draw();
    m_Pacman.Draw();
    m_Window.display();
  }

end_game:
  return 0;
}
