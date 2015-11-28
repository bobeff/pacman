#pragma once

class HighScoresData
{
public:
  static const sf::Uint8 MAX_HIGH_SCORES_ITEMS = 10;
  static const sf::Uint8 MAX_NAME_LENGTH = 16;

  HighScoresData();
  ~HighScoresData();

  sf::Uint8 GetItemsCount() const;
  const char* GetName(int index) const;
  sf::Uint16 GetScore(int index) const;

private:
  char m_Names[MAX_HIGH_SCORES_ITEMS][MAX_NAME_LENGTH];
  sf::Uint16 m_Scores[MAX_HIGH_SCORES_ITEMS];
  sf::Uint8 m_ItemsCount;
};
