#include "pch.h"
#include "game.h"
#include "gameplay_constants.h"
#include "sprite_factory.h"
#include "application.h"

sf::Vector2i RedGhostStrategy(const Game& game);
sf::Vector2i BlueGhostStrategy(const Game& game);
sf::Vector2i PinkGhostStrategy(const Game& game);
sf::Vector2i OrangeGhostStrategy(const Game& game);

Game::Game(Application& app)
  : Screen(app)
  , m_Maze(*this)
  , m_Pacman(*this)
{
  m_Ghosts[Ghost::RED] = new Ghost(*this, RED_GHOST_START_TILE,
    RED_GHOST_SCATTER_TARGET, RedGhostStrategy, Ghost::RED, 1);

  m_Ghosts[Ghost::BLUE] = new Ghost(*this, BLUE_GHOST_START_TILE,
    BLUE_GHOST_SCATTER_TARGET, BlueGhostStrategy, Ghost::BLUE, 2);

  m_Ghosts[Ghost::PINK] = new Ghost(*this, PINK_GHOST_START_TILE,
    PINK_GHOST_SCATTER_TARGET, PinkGhostStrategy, Ghost::PINK, 3);

  m_Ghosts[Ghost::ORANGE] = new Ghost(*this, ORANGE_GHOST_START_TILE,
    ORANGE_GHOST_SCATTER_TARGET, OrangeGhostStrategy, Ghost::ORANGE, 4);

  ResetScreen();
}

Game::~Game()
{
  for (int i = 0; i < Ghost::COUNT; ++i)
  {
    delete m_Ghosts[i];
  }
}

void Game::ProcessInput(const sf::Event& event)
{
  if (event.type != sf::Event::KeyPressed)
    return;

  switch (event.key.code)
  {
  case sf::Keyboard::Escape:
    m_State = STATE_EXIT;
    break;
  case sf::Keyboard::Left:
  case sf::Keyboard::A:
    m_Pacman.NewDirection = DIRECTION_WEST;
    break;
  case sf::Keyboard::Right:
  case sf::Keyboard::D:
    m_Pacman.NewDirection = DIRECTION_EAST;
    break;
  case sf::Keyboard::Up:
  case sf::Keyboard::W:
    m_Pacman.NewDirection = DIRECTION_NORTH;
    break;
  case sf::Keyboard::Down:
  case sf::Keyboard::S:
    m_Pacman.NewDirection = DIRECTION_SOUTH;
    break;
  case sf::Keyboard::Pause:
  case sf::Keyboard::P:
    if (m_State == STATE_PAUSED)
    {
      m_State = m_OldState;
    }
    else if (m_State != STATE_WINNING && m_State != STATE_GAME_OVER)
    {
      m_OldState = m_State;
      m_State = STATE_PAUSED;
    }
    break;
  }
}

void Game::Update()
{
  float elapsedTime = m_Clock.getElapsedTime().asSeconds();

  switch (m_State)
  {
  case STATE_RUNNING:
    m_Pacman.Update(elapsedTime);
    for (int i = 0; i < Ghost::COUNT; ++i)
    {
      m_Ghosts[i]->Update(elapsedTime);
    }
    break;
  case STATE_ABOUT_TO_START:
    if (elapsedTime > GAME_START_DELAY)
    {
      m_State = STATE_RUNNING;
    }
    break;
  case STATE_PACMAN_EATEN:
    if (elapsedTime > m_PacmanEatenTime + PACMAN_EATEN_DELAY)
    {
      m_State = STATE_ABOUT_TO_START;
      Reset();
    }
    break;
  case STATE_EXIT:
    m_App.BackToMainMenu();
    break;
  }
}

void Game::Draw()
{
  m_Maze.Draw();
  m_Pacman.Draw();

  for (int i = 0; i < Ghost::COUNT; ++i)
  {
    m_Ghosts[i]->Draw();
  }

  DrawGameInfo();
}

void Game::SetGhostsToRunMode()
{
  for (int i = 0; i < Ghost::COUNT; ++i)
  {
    if (m_Ghosts[i]->GetMode() != GhostMode::GoToReset)
    {
      m_Ghosts[i]->ChangeMode(GhostMode::Run,
        m_Clock.getElapsedTime().asSeconds());
    }
  }
}

void Game::Reset()
{
  m_Pacman.Reset();

  for (int i = 0; i < Ghost::COUNT; ++i)
  {
    m_Ghosts[i]->Reset();
  }

  m_Clock.restart();
}

void Game::OnPacmanEaten()
{
  if (0 == --m_PacmanLivesCount)
  {
    m_State = STATE_GAME_OVER;
  }
  else
  {
    m_PacmanEatenTime = m_Clock.getElapsedTime().asSeconds();
    m_State = STATE_PACMAN_EATEN;
  }
}

void Game::DrawGameInfo()
{
  static const sf::Vector2f SCORE_TEXT_POSITION(
    1.0f * Maze::TILE_SIZE, 34.5f * Maze::TILE_SIZE);

  static const sf::Vector2f LIVES_TEXT_POSITION(
    20.0f * Maze::TILE_SIZE, 34.5f * Maze::TILE_SIZE);

  static const sf::Vector2f PAUSE_TEXT_POSITION(
    12.0f * Maze::TILE_SIZE, 1.0f * Maze::TILE_SIZE);

  static const sf::Vector2f GAME_OVER_TEXT_POSITION(
    10.5f * Maze::TILE_SIZE, 1.0f * Maze::TILE_SIZE);

  static const sf::Vector2f WINNING_TEXT_POSITION(
    11.5f * Maze::TILE_SIZE, 1.0f * Maze::TILE_SIZE);

  static sf::Sprite liveSprite =
    SpriteFactory::Get().CreatePacmanInitialSprite();

  char scoreStr[16];
  sprintf(scoreStr, "Score: %d", m_Score);

  DrawText(scoreStr, SCORE_TEXT_POSITION, sf::Color::Yellow);
  DrawText("Lives: ", LIVES_TEXT_POSITION, sf::Color::Yellow);

  sf::RenderWindow& window = m_App.GetRenderWindow();

  for (int i = 0; i < m_PacmanLivesCount - 1; ++i)
  {
    liveSprite.setPosition(
      LIVES_TEXT_POSITION.x + (i * 1.25f + 3.5f) * Maze::TILE_SIZE,
      LIVES_TEXT_POSITION.y);

    window.draw(liveSprite);
  }

  switch (m_State)
  {
  case STATE_PAUSED:
    DrawText("PAUSE", PAUSE_TEXT_POSITION, sf::Color::Red);
    break;
  case STATE_GAME_OVER:
    DrawText("GAME OVER", GAME_OVER_TEXT_POSITION, sf::Color::Red);
    break;
  case STATE_WINNING:
    DrawText("YOU WIN", WINNING_TEXT_POSITION, sf::Color::Yellow);
    break;
  }
}

void Game::ResetScreen()
{
  m_EatenGhostsCount = 0;
  m_PacmanLivesCount = 3;
  m_Score = 0;
  m_State = STATE_ABOUT_TO_START;
  m_OldState = STATE_ABOUT_TO_START;
  m_PacmanEatenTime = 0.0f;
  m_Maze.Reset();

  Reset();
}

sf::RenderWindow& Game::GetRenderWindow() const
{
  return m_App.GetRenderWindow();
}

void Game::DrawText(const char* text, const sf::Vector2f& position,
  const sf::Color& color)
{
  m_App.DrawText(text, position, color, sf::Text::Bold, Maze::TILE_SIZE);
}
