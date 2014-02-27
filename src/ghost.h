#pragma once

#include "actor.h"
#include "ghost_modes.h"

class Ghost : public Actor
{
public:
  Ghost(Game& game, const sf::Vector2i& startPosition,
    const sf::Vector2i& target, int spritesIndex);
  virtual ~Ghost();

  GhostMode::Mode GetMode() const;

  const sf::Vector2i& GetTargetTile() const;
  const sf::Vector2i& GetStartTile() const;
  const sf::Vector2i& GetScatterTargetTile() const;

  void ChangeMode(GhostMode::Mode mode, float startTime);
  void SetDefaultSprites();
  void SetRunModeSprites();
  void SetResetModeSprites();
  void Flicker();

private:
  int GetDistanceToTarget(const sf::Vector2i& position) const;
  bool IsMovePossible(const sf::Vector2i& position) const;
  virtual void UpdatePosition(float elapsedTime);

  sf::Vector2i m_CameFrom;
  sf::Vector2i m_ScatterTargetTile;

  GhostMode* m_Modes[GhostMode::MODES_COUNT];
  GhostMode* m_Mode;

  ActorSprites m_RunModeSprites;
  ActorSprites m_AboutToStopRunModeSprites;
  ActorSprites m_ResetModeSprites;
};
