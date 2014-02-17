#pragma once

class Ghost;

class GhostMode
{
public:
  enum
  {
    CHASE,
    SCATTER,
    MODES_COUNT,
  };

  GhostMode(Ghost& ghost);
  virtual bool Change(float elapsedTime) = 0;
  virtual const sf::Vector2i& GetTargetTile() const = 0;

  float StartTime;

protected:
  Ghost& m_Ghost;
};

#define DECLARE_MODE_CLASS(ModeName) \
  class ModeName : public GhostMode { \
  public: \
    ModeName(Ghost& ghost) : GhostMode(ghost) {} \
    virtual bool Change(float elapsedTime); \
    virtual const sf::Vector2i& GetTargetTile() const; \
  };

DECLARE_MODE_CLASS(ChaseMode)
DECLARE_MODE_CLASS(ScatterMode)

#undef DECLARE_MODE_CLASS
