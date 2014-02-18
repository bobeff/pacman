#include "pch.h"
#include "ghost.h"
#include "game.h"
#include "sprite_factory.h"

static const float MOVE_TIME = .15f;

Ghost::Ghost(Game& game, const sf::Vector2i& startPosition, const sf::Vector2i& target, int spritesIndex)
  : Actor(game, startPosition, spritesIndex, MOVE_TIME)
  , m_CameFrom(startPosition)
  , m_ScatterTargetTile(target)
{
  m_Modes[GhostMode::CHASE] = new ChaseMode(*this);
  m_Modes[GhostMode::SCATTER] = new ScatterMode(*this);
  m_Modes[GhostMode::ABOUT_TO_RUN] = new AboutToRunMode(*this);
  m_Modes[GhostMode::RUN] = new RunMode(*this);
  m_Modes[GhostMode::ABOUT_TO_STOP_RUN] = new AboutToStopRunMode(*this);
  m_Mode = m_Modes[GhostMode::CHASE];

  SpriteFactory& factory = SpriteFactory::Get();
  factory.CreateActorSprites(5, m_RunModeSprites);
  factory.CreateActorSprites(6, m_AboutToStopRunModeSprites);
}

Ghost::~Ghost()
{
  for (int i = 0; i < GhostMode::MODES_COUNT; ++i)
    delete m_Modes[i];
}

void Ghost::ChangeMode(GhostMode::Mode mode, float startTime)
{
  m_Mode = m_Modes[mode];
  m_Mode->Reset(startTime);
}

void Ghost::SetToRunMode()
{
  m_Mode = m_Modes[GhostMode::ABOUT_TO_RUN];
}

void Ghost::SetDefaultSprites()
{
  m_CurrentSpritesArray = &m_Sprites;
}

void Ghost::SetRunModeSprites()
{
  m_CurrentSpritesArray = &m_RunModeSprites;
}

void Ghost::Flicker()
{
  m_CurrentSpritesArray = m_CurrentSpritesArray == &m_RunModeSprites ?
    &m_AboutToStopRunModeSprites : &m_RunModeSprites;
}

const sf::Vector2i& Ghost::GetTargetTile() const
{
  return m_Game.m_Pacman.GetPosition();
}

const sf::Vector2i& Ghost::GetScatterTargetTile() const
{
  return m_ScatterTargetTile;
}

int Ghost::GetDistanceToTarget(const sf::Vector2i& position) const
{
  const sf::Vector2i& target = m_Mode->GetTargetTile();
#define SQR(X) ((X) * (X))
  return SQR(target.x - position.x) + SQR(target.y - position.y);
#undef SQR
}

bool Ghost::IsMovePossible(const sf::Vector2i& position) const
{
  char tile = m_Game.m_Maze.GetTile(position);
  char tileCameFrom = m_Game.m_Maze.GetTile(m_CameFrom);
  return tile != '#' && (tile != '-' || tile == '-' && tileCameFrom == '-');
}

void Ghost::UpdatePosition(float elapsedTime)
{
  m_CameFrom = m_Position;
  m_Position = m_NextPosition;

  static const sf::Vector2i STEP[4] =
  {
    sf::Vector2i( 1,  0), // east
    sf::Vector2i( 0,  1), // south
    sf::Vector2i(-1,  0), // west
    sf::Vector2i( 0, -1), // north
  };

  if (m_Mode->Change(elapsedTime))
  {
    m_NextPosition = m_CameFrom;
    m_Direction = Direction((int(m_Direction) + 2) % 4);
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

  ++m_AnimationStage %= 2;
  SetCurrentSprite();
}