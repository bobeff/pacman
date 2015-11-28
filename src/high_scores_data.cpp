#include "pch.h"
#include "high_scores_data.h"

static const char* HIGH_SCORES_FILE_NAME = "scores.txt";

HighScoresData::HighScoresData() : m_ItemsCount(0)
{
  FILE* file = fopen(HIGH_SCORES_FILE_NAME, "r");
  if (!file) return;

  char name[16];
  unsigned score;
  while (fscanf(file, "%15s %u\n", &name, &score) == 2)
  {
#ifdef _DEBUG
    printf("%s %u\n", name, score);
#endif
    strcpy(m_Names[m_ItemsCount], name);
    m_Scores[m_ItemsCount] = score;
    ++m_ItemsCount;
    if (MAX_HIGH_SCORES_ITEMS == m_ItemsCount) break;
  }
}

HighScoresData::~HighScoresData()
{
  FILE* file = fopen(HIGH_SCORES_FILE_NAME, "w");
  if (!file) return;
  for (sf::Uint8 i = 0; i < m_ItemsCount; ++i)
  {
    fprintf(file, "%s %d\n", m_Names[i], m_Scores[i]);
  }
}

sf::Uint8 HighScoresData::GetItemsCount() const
{
  return m_ItemsCount;
}

const char* HighScoresData::GetName(int index) const
{
  return m_Names[index];
}

sf::Uint16 HighScoresData::GetScore(int index) const
{
  return m_Scores[index];
}
