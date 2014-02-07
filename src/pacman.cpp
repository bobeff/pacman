#include "pch.h"
#include "pacman.h"
#include "game.h"
#include "sprite_factory.h"

Pacman::Pacman(Game& game)
  : m_Game(game)
  , m_PreviousTime(0.f)
  , m_Position(14, 26)
  , m_NextPosition(m_Position)
  , m_Direction(Direction::NONE)
  , NewDirection(Direction::NONE)
  , m_AnimationStage(1)
{
  SpriteFactory& factory = SpriteFactory::Get();
  m_InitialSprite = factory.CreatePacmanInitialSprite();
  factory.CreateActorSprites(0, m_Sprites);
  m_CurrentSprite = m_InitialSprite;
  Maze::SetSpritePosition(m_CurrentSprite, m_Position);
}

void Pacman::Draw() const
{
  m_Game.m_Window.draw(m_CurrentSprite);
}

static void UpdatePosition(Direction direction, sf::Vector2i& position)
{
  switch (direction)
  {
    case Direction::WEST: --position.x; break;
    case Direction::EAST: ++position.x; break;
    case Direction::NORTH: --position.y; break;
    case Direction::SOUTH: ++position.y; break;
    default: assert(0);
  }

  if (position.x < 0) position.x = Maze::X_SIZE - 1;
  if (position.x >= Maze::X_SIZE) position.x = 0;
}

void Pacman::Update(float elapsedTime)
{
  static const float MOVE_TIME_INTERVAL = .15f;

  if (NewDirection == Direction::NONE) return;

  float deltaTime = elapsedTime - m_PreviousTime;
  if (deltaTime < MOVE_TIME_INTERVAL)
  {
    if (m_Position == m_NextPosition)
      return;

    float deltaMove = deltaTime / MOVE_TIME_INTERVAL;
    sf::Vector2f position(m_Position);
    
    switch (m_Direction)
    {
      case Direction::WEST: position.x -= deltaMove; break;
      case Direction::EAST: position.x += deltaMove; break;
      case Direction::NORTH: position.y -= deltaMove; break;
      case Direction::SOUTH: position.y += deltaMove; break;
      default: assert(0);
    }

    Maze::SetSpritePosition(m_CurrentSprite, position);
  }
  else
  {
    m_PreviousTime = elapsedTime;

    if (m_Position != m_NextPosition)
    {
      m_Position = m_NextPosition;
      m_Game.m_Maze.ConsumeTile(m_Position);
    }

    sf::Vector2i newPosition = m_Position;
    UpdatePosition(NewDirection, newPosition);
    if (m_Game.m_Maze.IsMovePossible(newPosition))
      m_Direction = NewDirection;

    newPosition = m_Position;
    UpdatePosition(m_Direction, newPosition);
    
    if (m_Game.m_Maze.IsMovePossible(newPosition))
    {
      m_NextPosition = newPosition;
      ++m_AnimationStage %= 2;
      m_CurrentSprite = m_Sprites[int(m_Direction)][m_AnimationStage];
    }
    else
    {
      NewDirection = Direction::NONE;
      m_CurrentSprite = m_InitialSprite;
    }

    Maze::SetSpritePosition(m_CurrentSprite, m_Position);
  }
}
