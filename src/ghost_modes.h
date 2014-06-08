#pragma once

class Ghost;

class GhostMode
{
public:
  enum Mode
  {
    Chase,
    Scatter,
    Run,
    AboutToStopRun,
    GoToReset,
    ModesCount,
  };

  GhostMode(Ghost& ghost, Mode mode);
  virtual ~GhostMode() {}

  Mode GetModeID() const { return m_Mode; }

  virtual void Reset(float startTime) = 0;
  virtual void TryToChange(float elapsedTime) = 0;
  virtual sf::Vector2i GetTargetTile() const = 0;
  virtual int GetInitialDistance() const = 0;
  virtual bool CompareDistances(int dist1, int dist2) const = 0;
  virtual void OnCollisionWithPacman() const = 0;
  virtual void ReverseDirection() const = 0;
  virtual float GetMoveTimeInterval() const = 0;

protected:
  Ghost& m_Ghost;
  Mode m_Mode;
  float m_StartTime;
};

#define DECLARE_MODE_CLASS(ModeName) \
class ModeName##Mode : public GhostMode { \
  public: \
    ModeName##Mode(Ghost& ghost) : GhostMode(ghost, ModeName) {} \
    virtual void Reset(float startTime); \
    virtual void TryToChange(float elapsedTime); \
    virtual sf::Vector2i GetTargetTile() const; \
    virtual int GetInitialDistance() const; \
    virtual bool CompareDistances(int dist1, int dist2) const; \
    virtual void OnCollisionWithPacman() const; \
    virtual void ReverseDirection() const; \
    virtual float GetMoveTimeInterval() const; \
  };

DECLARE_MODE_CLASS(Chase)
DECLARE_MODE_CLASS(Scatter)
DECLARE_MODE_CLASS(Run)
DECLARE_MODE_CLASS(AboutToStopRun)
DECLARE_MODE_CLASS(GoToReset)

#undef DECLARE_MODE_CLASS
