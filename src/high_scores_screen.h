#pragma once

#include "screen.h"

class HighScoresGrid;

class HighScoresScreen : public Screen
{
public:
  HighScoresScreen(Application& app);
  ~HighScoresScreen();

  virtual void ProcessInput(const sf::Event& event);
  virtual void Update();
  virtual void Draw();
  virtual void ResetScreen();

private:
  HighScoresGrid* m_Grid;
};
