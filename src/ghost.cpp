#include "pch.h"
#include "ghost.h"
#include "game.h"
#include "sprite_factory.h"
#include "gameplay_constants.h"

Ghost::Ghost(Game& game,
             const sf::Vector2i& startPosition,
             const sf::Vector2i& scatterTarget,
             GhostStrategy strategy,
             Color color,
             int spritesIndex)
  : Actor(game, startPosition, spritesIndex)
  , m_CameFrom(startPosition)
  , m_ScatterTargetTile(scatterTarget)
  , m_IsModeChanged(false)
  , m_Strategy(strategy)
  , m_Color(color)
{
  m_Modes[GhostMode::Chase] = new ChaseMode(*this);
  m_Modes[GhostMode::Scatter] = new ScatterMode(*this);
  m_Modes[GhostMode::Run] = new RunMode(*this);
  m_Modes[GhostMode::AboutToStopRun] = new AboutToStopRunMode(*this);
  m_Modes[GhostMode::GoToReset] = new GoToResetMode(*this);
  m_Mode = m_Modes[GhostMode::Chase];

  SpriteFactory& factory = SpriteFactory::Get();
  factory.CreateActorSprites(5, m_RunModeSprites);
  factory.CreateActorSprites(6, m_AboutToStopRunModeSprites);
  factory.CreateActorSprites(7, m_ResetModeSprites);
}

Ghost::~Ghost()
{
  for (int i = 0; i < GhostMode::ModesCount; ++i)
  {
    delete m_Modes[i];
  }
}

//#define ENABLE_DEBUG_VISUALIZATIONS

void Ghost::Draw() const
{
  Actor::Draw();

#ifdef ENABLE_DEBUG_VISUALIZATIONS
  static sf::RectangleShape square(
    sf::Vector2f(Maze::TILE_SIZE, Maze::TILE_SIZE));
  sf::Vector2i targetTile = m_Mode->GetTargetTile();
  Maze::SetPosition(square, targetTile);
  square.setFillColor(GetColor());
  m_Game.m_Window.draw(square);
#endif
}

const sf::Color& Ghost::GetColor() const
{
  static const sf::Color COLORS[Ghost::COUNT] =
  {
    sf::Color(255,   0,   0, 127), // red
    sf::Color(  0, 128, 255, 127), // blue
    sf::Color(255,  74, 255, 127), // pink
    sf::Color(255, 170,   0, 127), // orange
  };

  return COLORS[m_Color];
}

void Ghost::ChangeMode(GhostMode::Mode mode, float startTime)
{
  if (m_Mode->GetModeID() != mode)
  {
    m_Mode = m_Modes[mode];
    m_IsModeChanged = true;
  }
  m_Mode->Reset(startTime);
}

void Ghost::ReverseDirection()
{
  m_NextPosition = m_CameFrom;
  m_Direction = Direction((int(m_Direction) + 2) % 4);
}

void Ghost::SetDefaultSprites()
{
  m_CurrentSpritesArray = &m_Sprites;
}

void Ghost::SetRunModeSprites()
{
  m_CurrentSpritesArray = &m_RunModeSprites;
}

void Ghost::SetResetModeSprites()
{
  m_CurrentSpritesArray = &m_ResetModeSprites;
}

void Ghost::Flicker()
{
  m_CurrentSpritesArray = m_CurrentSpritesArray == &m_RunModeSprites ?
    &m_AboutToStopRunModeSprites : &m_RunModeSprites;
}

void Ghost::OnGhostEaten()
{
  // The first ghost captured after an energizer has been eaten is always
  // worth 200 points. Each additional ghost captured from the same energizer
  // will then be worth twice as many points as the one before it - 400, 800,
  // and 1600 points, respectively. 
  ++m_Game.m_EatenGhostsCount;
  m_Game.m_Score += 100 * (1 << m_Game.m_EatenGhostsCount);
  ChangeMode(GhostMode::GoToReset, 0);
}

void Ghost::OnPacmanEaten()
{
  m_Game.m_State = Game::State::GAME_OVER;
}

GhostMode::Mode Ghost::GetMode() const
{
  return m_Mode->GetModeID();
}

sf::Vector2i Ghost::GetTargetTile() const
{
  // if the ghost is in the house then first escape from it
  if (IsInHouse()) return GHOSTS_OUT_OF_HOUSE_TARGET;
  return m_Strategy(m_Game);
}

const sf::Vector2i& Ghost::GetScatterTargetTile() const
{
  return m_ScatterTargetTile;
}

int Ghost::GetDistanceToTarget(const sf::Vector2i& position) const
{
  sf::Vector2i target = m_Mode->GetTargetTile();
#define SQR(X) ((X) * (X))
  return SQR(target.x - position.x) + SQR(target.y - position.y);
#undef SQR
}

bool Ghost::IsMovePossible(const sf::Vector2i& position) const
{
  char tile = m_Game.m_Maze.GetTile(position);
  char tileCameFrom = m_Game.m_Maze.GetTile(m_CameFrom);
  if (tile == '-')
  {
    return tileCameFrom == '-' || GetMode() == GhostMode::GoToReset;
  }
  return tile != '#';
}

bool Ghost::IsInHouse() const
{
  return m_Game.m_Maze.GetTile(m_Position) == '-';
}

float Ghost::GetMoveTimeInterval() const
{
  return m_Mode->GetMoveTimeInterval();
}

void Ghost::UpdatePosition(float elapsedTime)
{
  const sf::Vector2i& pacmanPosition = m_Game.m_Pacman.GetPosition();
  if (pacmanPosition == m_Position || pacmanPosition == m_NextPosition)
  {
    m_Mode->OnCollisionWithPacman();
  }

  m_CameFrom = m_Position;
  m_Position = m_NextPosition;

  static const sf::Vector2i STEP[4] =
  {
    sf::Vector2i( 1,  0), // east
    sf::Vector2i( 0,  1), // south
    sf::Vector2i(-1,  0), // west
    sf::Vector2i( 0, -1), // north
  };

  m_Mode->TryToChange(elapsedTime);

  if (m_IsModeChanged)
  {
    m_Mode->ReverseDirection();
    m_IsModeChanged = false;
  }
  else
  {
    int bestDistance = m_Mode->GetInitialDistance();
    for (int i = 0; i < 4; ++i)
    {
      sf::Vector2i position = m_Position + STEP[i];
      Maze::TruncatePosition(position);

      // if the new position is unpassable tile or
      // it is the same tile from which we previously came from
      if (!IsMovePossible(position) || position == m_CameFrom)
        continue;

      int distance = GetDistanceToTarget(position);
      if (m_Mode->CompareDistances(bestDistance, distance))
      {
        bestDistance = distance;
        m_NextPosition = position;
        m_Direction = Direction(i);
      }
    }
  }

  if (pacmanPosition == m_NextPosition)
  {
    m_Mode->OnCollisionWithPacman();
  }

  ++m_AnimationStage %= 2;
}
