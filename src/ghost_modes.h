#pragma once

class Ghost;

class GhostMode
{
public:
  enum Mode
  {
    CHASE,
    SCATTER,
    RUN,
    ABOUT_TO_STOP_RUN,
    RESET,
    MODES_COUNT,
  };

  GhostMode(Ghost& ghost, Mode mode);

  Mode GetModeID() const { return m_Mode; }

  virtual void Reset(float startTime) = 0;
  virtual bool Change(float elapsedTime) = 0;
  virtual const sf::Vector2i& GetTargetTile() const = 0;
  virtual int GetInitialDistance() const = 0;
  virtual bool CompareDistances(int dist1, int dist2) const = 0;
  virtual void OnCollisionWithPacman() const = 0;

protected:
  Ghost& m_Ghost;
  Mode m_Mode;
  float m_StartTime;
};

#define DECLARE_MODE_CLASS(ModeName, ModeID) \
  class ModeName : public GhostMode { \
  public: \
    ModeName(Ghost& ghost) : GhostMode(ghost, ModeID) {} \
    virtual void Reset(float startTime); \
    virtual bool Change(float elapsedTime); \
    virtual const sf::Vector2i& GetTargetTile() const; \
    virtual int GetInitialDistance() const; \
    virtual bool CompareDistances(int dist1, int dist2) const; \
    virtual void OnCollisionWithPacman() const; \
  };

DECLARE_MODE_CLASS(ChaseMode, CHASE)
DECLARE_MODE_CLASS(ScatterMode, SCATTER)
DECLARE_MODE_CLASS(RunMode, RUN)
DECLARE_MODE_CLASS(AboutToStopRunMode, ABOUT_TO_STOP_RUN);
DECLARE_MODE_CLASS(ResetMode, RESET);

#undef DECLARE_MODE_CLASS
