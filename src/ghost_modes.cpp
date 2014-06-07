#include "pch.h"
#include "ghost_modes.h"
#include "ghost.h"

static const float CHASE_TIME = 20.f;
static const float SCATTER_TIME = 10.f;
static const float RUN_TIME = 15.f;
static const float ABOUT_TO_STOP_RUN_TIME = 5.f;

GhostMode::GhostMode(Ghost& ghost, Mode mode)
  : m_Ghost(ghost)
  , m_Mode(mode)
  , m_StartTime(0.f)
{
}

// ------------------- ChaseMode methods -------------------------------------

void ChaseMode::Reset(float startTime)
{
  m_StartTime = startTime;
  m_Ghost.SetDefaultSprites();
}

void ChaseMode::TryToChange(float elapsedTime)
{
  float deltaTime = elapsedTime - m_StartTime;
  if (deltaTime < CHASE_TIME) return;
  m_Ghost.ChangeMode(Scatter, elapsedTime);
}

const sf::Vector2i& ChaseMode::GetTargetTile() const
{
  return m_Ghost.GetTargetTile();
}

int ChaseMode::GetInitialDistance() const
{
  return INT_MAX;
}

bool ChaseMode::CompareDistances(int dist1, int dist2) const
{
  return dist1 > dist2;
}

void ChaseMode::OnCollisionWithPacman() const
{
}

void ChaseMode::ReverseDirection() const
{
  m_Ghost.ReverseDirection();
}

// ------------------- ScatterMode methods -----------------------------------

void ScatterMode::Reset(float startTime)
{
  m_StartTime = startTime;
}

void ScatterMode::TryToChange(float elapsedTime)
{
  float deltaTime = elapsedTime - m_StartTime;
  if (deltaTime < SCATTER_TIME) return;
  m_Ghost.ChangeMode(Chase, elapsedTime);
}

const sf::Vector2i& ScatterMode::GetTargetTile() const
{
  return m_Ghost.GetScatterTargetTile();
}

int ScatterMode::GetInitialDistance() const
{
  return INT_MAX;
}

bool ScatterMode::CompareDistances(int dist1, int dist2) const
{
  return dist1 > dist2;
}

void ScatterMode::OnCollisionWithPacman() const
{
}

void ScatterMode::ReverseDirection() const
{
  m_Ghost.ReverseDirection();
}

// ------------------- RunMode methods ---------------------------------------

void RunMode::Reset(float startTime)
{
  m_StartTime = startTime;
  m_Ghost.SetRunModeSprites();
}

void RunMode::TryToChange(float elapsedTime)
{
  float deltaTime = elapsedTime - m_StartTime;
  if (deltaTime < RUN_TIME) return;
  m_Ghost.ChangeMode(AboutToStopRun, elapsedTime);
}

const sf::Vector2i& RunMode::GetTargetTile() const
{
  return m_Ghost.GetTargetTile();
}

int RunMode::GetInitialDistance() const
{
  return INT_MIN;
}

bool RunMode::CompareDistances(int dist1, int dist2) const
{
  return dist1 < dist2;
}

void RunMode::OnCollisionWithPacman() const
{
  m_Ghost.ChangeMode(GoToReset, 0);
}

void RunMode::ReverseDirection() const
{
  m_Ghost.ReverseDirection();
}

// ------------------- AboutToStopRunMode methods ----------------------------

void AboutToStopRunMode::Reset(float startTime)
{
  m_StartTime = startTime;
}

void AboutToStopRunMode::TryToChange(float elapsedTime)
{
  m_Ghost.Flicker();
  float deltaTime = elapsedTime - m_StartTime;
  if (deltaTime < ABOUT_TO_STOP_RUN_TIME) return;
  m_Ghost.ChangeMode(Chase, elapsedTime);
}

const sf::Vector2i& AboutToStopRunMode::GetTargetTile() const
{
  return m_Ghost.GetTargetTile();
}

int AboutToStopRunMode::GetInitialDistance() const
{
  return INT_MIN;
}

bool AboutToStopRunMode::CompareDistances(int dist1, int dist2) const
{
  return dist1 < dist2;
}

void AboutToStopRunMode::OnCollisionWithPacman() const
{
  m_Ghost.ChangeMode(GoToReset, 0);
}

void AboutToStopRunMode::ReverseDirection() const
{
}

// ------------------- ResetMode methods -------------------------------------

void GoToResetMode::Reset(float startTime)
{
  m_Ghost.SetResetModeSprites();
}

void GoToResetMode::TryToChange(float elapsedTime)
{
  if (m_Ghost.GetPosition() != m_Ghost.GetStartTile()) return;
  m_Ghost.ChangeMode(Chase, elapsedTime);
}

const sf::Vector2i& GoToResetMode::GetTargetTile() const
{
  return m_Ghost.GetStartTile();;
}

int GoToResetMode::GetInitialDistance() const
{
  return INT_MAX;
}

bool GoToResetMode::CompareDistances(int dist1, int dist2) const
{
  return dist1 > dist2;
}

void GoToResetMode::OnCollisionWithPacman() const
{
}

void GoToResetMode::ReverseDirection() const
{
}
