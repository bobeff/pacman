#pragma once

class Application;

class Screen
{
public:
  Screen(Application& app) : m_App(app) {}
  virtual ~Screen() {}

  virtual void ProcessInput(const sf::Event::KeyEvent& key) = 0;
  virtual void Update() = 0;
  virtual void Draw() = 0;
  virtual void ResetScreen() = 0;

protected:
  Application& m_App;
};
