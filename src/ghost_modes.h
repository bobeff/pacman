#pragma once

class Ghost;

class GhostMode
{
public:
  enum Mode
  {
    CHASE,
    SCATTER,
    ABOUT_TO_RUN,
    RUN,
    ABOUT_TO_STOP_RUN,
    MODES_COUNT,
  };

  GhostMode(Ghost& ghost);

  virtual void Reset(float startTime) = 0;
  virtual bool Change(float elapsedTime) = 0;
  virtual const sf::Vector2i& GetTargetTile() const = 0;
  virtual int GetInitialDistance() const = 0;
  virtual bool CompareDistances(int dist1, int dist2) const = 0;

protected:
  Ghost& m_Ghost;
  float m_StartTime;
};

#define DECLARE_MODE_CLASS(ModeName) \
  class ModeName : public GhostMode { \
  public: \
    ModeName(Ghost& ghost) : GhostMode(ghost) {} \
    virtual void Reset(float startTime); \
    virtual bool Change(float elapsedTime); \
    virtual const sf::Vector2i& GetTargetTile() const; \
    virtual int GetInitialDistance() const; \
    virtual bool CompareDistances(int dist1, int dist2) const; \
  };

DECLARE_MODE_CLASS(ChaseMode)
DECLARE_MODE_CLASS(ScatterMode)
DECLARE_MODE_CLASS(AboutToRunMode)
DECLARE_MODE_CLASS(RunMode)
DECLARE_MODE_CLASS(AboutToStopRunMode);

#undef DECLARE_MODE_CLASS
