#pragma once

class Pacman;

class GhostStrategy
{
public:
  GhostStrategy(const Pacman& pacman);
  virtual ~GhostStrategy() {}
  virtual sf::Vector2i GetTargetTile() const = 0;

protected:
  const Pacman& m_Pacman;
};

class RedGhostStrategy : public GhostStrategy
{
public:
  RedGhostStrategy(const Pacman& pacman);
  virtual sf::Vector2i GetTargetTile() const;
};

class PinkGhostStrategy : public GhostStrategy
{
public:
  PinkGhostStrategy(const Pacman& pacman);
  virtual sf::Vector2i GetTargetTile() const;
};
