#include "pch.h"
#include "game.h"
#include "ghost_startegies.h"

static const sf::Vector2i RED_GHOST_START_TILE(14, 14);
static const sf::Vector2i RED_GHOST_SCATTER_TARGET(25, 0);
static const sf::Vector2i PINK_GHOST_START_TILE(13, 14);
static const sf::Vector2i PINK_GHOST_SCATTER_TARGET(4, 0);

Game::Game()
  : m_Maze(*this)
  , m_Pacman(*this)
  , m_TilesConsumed(0)
  , m_Score(0)
{
  // the red ghost
  m_Ghosts[0] = new Ghost(*this, RED_GHOST_START_TILE,
    RED_GHOST_SCATTER_TARGET, new RedGhostStrategy(m_Pacman), 1);

  // the pink ghost
  m_Ghosts[1] = new Ghost(*this, PINK_GHOST_START_TILE,
    PINK_GHOST_SCATTER_TARGET, new PinkGhostStrategy(m_Pacman), 3);

  m_Window.create(sf::VideoMode(448, 576),
    "Pacman", sf::Style::Titlebar | sf::Style::Close);
  m_Window.setVerticalSyncEnabled(true);

  m_Font.loadFromFile("assets/arial.ttf");
  m_Text.setFont(m_Font);
  m_Text.setCharacterSize(Maze::TILE_SIZE);
  m_Text.setColor(sf::Color::Yellow);
  m_Text.setStyle(sf::Text::Bold);
}

void Game::DrawText(const char* str, float x, float y)
{
  m_Text.setString(str);
  m_Text.setPosition(x, y);
  m_Window.draw(m_Text);
}

void Game::SetGhostsToRunMode()
{
  for (int i = 0; i < GHOSTS_COUNT; ++i)
  {
    if (m_Ghosts[i]->GetMode() != GhostMode::GoToReset)
    {
      m_Ghosts[i]->ChangeMode(GhostMode::Run,
        m_Clock.getElapsedTime().asSeconds());
    }
  }
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
    for (int i = 0; i < GHOSTS_COUNT; ++i)
      m_Ghosts[i]->Update(elapsedTime);

    m_Window.clear(sf::Color::Black);
    m_Maze.Draw();
    m_Pacman.Draw();
    for (int i = 0; i < GHOSTS_COUNT; ++i)
      m_Ghosts[i]->Draw();

    char scoreStr[16];
    sprintf(scoreStr, "Score: %d", m_Score);
    static const float GAME_INFO_Y_POSITION = 34.5f * Maze::TILE_SIZE;
    DrawText(scoreStr, Maze::TILE_SIZE, GAME_INFO_Y_POSITION);

    m_Window.display();
  }

end_game:
  return 0;
}
