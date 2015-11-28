#include "pch.h"
#include "high_scores_screen.h"
#include "application.h"

using namespace sf;

static const unsigned TEXT_SIZE = 30;

class HighScoresGrid : public Drawable
{
public:
  HighScoresGrid() : m_Vertices(Lines, 32)
  {
    static const float MIN_X = 45.0f;
    static const float MAX_X = 395.0f;
    static const float MIN_Y = 120.0f;
    static const float MAX_Y = 450.0f;
    static const float NAME_X = MIN_X + TEXT_SIZE * 1.5f;
    static const float SCORE_X = MIN_X + TEXT_SIZE * 8;

    sf::Uint8 vertexIndex = 0;

    for (float y = MIN_Y; y <= MAX_Y; y += TEXT_SIZE)
    {
      m_Vertices[vertexIndex++] = Vertex(Vector2f(MIN_X, y), Color::White);
      m_Vertices[vertexIndex++] = Vertex(Vector2f(MAX_X, y), Color::White);
    }

    m_Vertices[vertexIndex++] = Vertex(Vector2f(MIN_X, MIN_Y), Color::White);
    m_Vertices[vertexIndex++] = Vertex(Vector2f(MIN_X, MAX_Y), Color::White);
    m_Vertices[vertexIndex++] = Vertex(Vector2f(NAME_X, MIN_Y), Color::White);
    m_Vertices[vertexIndex++] = Vertex(Vector2f(NAME_X, MAX_Y), Color::White);
    m_Vertices[vertexIndex++] = Vertex(Vector2f(SCORE_X, MIN_Y), Color::White);
    m_Vertices[vertexIndex++] = Vertex(Vector2f(SCORE_X, MAX_Y), Color::White);
    m_Vertices[vertexIndex++] = Vertex(Vector2f(MAX_X, MIN_Y), Color::White);
    m_Vertices[vertexIndex++] = Vertex(Vector2f(MAX_X, MAX_Y), Color::White);
  }

  virtual void draw(RenderTarget& target, RenderStates states) const
  {
    target.draw(m_Vertices, states);
  }

private:
  sf::VertexArray m_Vertices;
};

HighScoresScreen::HighScoresScreen(Application& app)
  : Screen(app)
  , m_Grid(new HighScoresGrid)
{
}

HighScoresScreen::~HighScoresScreen()
{
  delete m_Grid;
}

void HighScoresScreen::ProcessInput(const sf::Event& event)
{
}

void HighScoresScreen::Update()
{
}

void HighScoresScreen::Draw()
{
  m_App.DrawText("HIGH SCORES", Vector2f(45, 30), Color::Blue,
    Text::Regular | Text::Underlined, 50);

  static const float GRID_TEXT_MIN_Y = 115.0f;

  m_App.DrawText("N", Vector2f(50.0f, GRID_TEXT_MIN_Y),
    Color::Yellow, Text::Regular, TEXT_SIZE);

  m_App.DrawText("Name", Vector2f(145.0f, GRID_TEXT_MIN_Y),
    Color::Yellow, Text::Regular, TEXT_SIZE);
  
  m_App.DrawText("Score", Vector2f(300.0f, GRID_TEXT_MIN_Y),
    Color::Yellow, Text::Regular, TEXT_SIZE);

  HighScoresData& data = m_App.GetHighScores();
  sf::Uint8 itemsCount = data.GetItemsCount();

  for (Uint8 i = 1; i <= HighScoresData::MAX_HIGH_SCORES_ITEMS; ++i)
  {
    float yPosition = GRID_TEXT_MIN_Y + i * TEXT_SIZE;

    char number[3];
    sprintf(number, "%d", i);

    m_App.DrawText(number, Vector2f(50.0f, yPosition),
      Color::Yellow, Text::Regular, TEXT_SIZE);

    if (i > itemsCount) continue;

    m_App.DrawText(data.GetName(i - 1), Vector2f(92.0f, yPosition),
      Color::White, Text::Regular, TEXT_SIZE);

    char score[8];
    sprintf(score, "%d", data.GetScore(i - 1));

    m_App.DrawText(score, Vector2f(287.0f, yPosition),
      Color::White, Text::Regular, TEXT_SIZE);
  }

  m_App.GetRenderWindow().draw(*m_Grid);
}

void HighScoresScreen::ResetScreen()
{
}
