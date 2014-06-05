#pragma once

#include "actor.h"
#include "ghost_modes.h"

class GhostStrategy;

class Ghost : public Actor
{
public:
  Ghost(Game& game,
        const sf::Vector2i& startPosition,
        const sf::Vector2i& target,
        const GhostStrategy* strategy,
        int spritesIndex);

  virtual ~Ghost();

  GhostMode::Mode GetMode() const;

  const sf::Vector2i& GetTargetTile() const;
  const sf::Vector2i& GetStartTile() const;
  const sf::Vector2i& GetScatterTargetTile() const;

  void ChangeMode(GhostMode::Mode mode, float startTime);
  void ReverseDirection();
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

  GhostMode* m_Modes[GhostMode::ModesCount];
  GhostMode* m_Mode;

  bool m_IsModeChanged;

  const GhostStrategy* m_Strategy;

  ActorSprites m_RunModeSprites;
  ActorSprites m_AboutToStopRunModeSprites;
  ActorSprites m_ResetModeSprites;
};
