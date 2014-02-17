#include "pch.h"
#include "ghost_mode.h"
#include "ghost.h"

static const float CHASE_TIME = 20.f;
static const float SCATTER_TIME = 10.f;

GhostMode::GhostMode(Ghost& ghost)
  : m_Ghost(ghost)
  , StartTime(0.f)
{
}

bool ChaseMode::Change(float elapsedTime)
{
  float deltaTime = elapsedTime - StartTime;
  if (deltaTime < CHASE_TIME) return false;
  m_Ghost.m_Mode = m_Ghost.m_Modes[SCATTER];
  m_Ghost.m_Mode->StartTime = elapsedTime;
  return true;
}

const sf::Vector2i& ChaseMode::GetTargetTile() const
{
  return m_Ghost.GetTargetTile();
}

bool ScatterMode::Change(float elapsedTime)
{
  float deltaTime = elapsedTime - StartTime;
  if (deltaTime < SCATTER_TIME) return false;
  m_Ghost.m_Mode = m_Ghost.m_Modes[CHASE];
  m_Ghost.m_Mode->StartTime = elapsedTime;
  return true;
}

const sf::Vector2i& ScatterMode::GetTargetTile() const
{
  return m_Ghost.m_ScatterTargetTile;
}
