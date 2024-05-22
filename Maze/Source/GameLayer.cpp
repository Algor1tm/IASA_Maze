#include "GameLayer.h"
#include "Application.h"

#include <raylib.h>
#include <raymath.h>


GameLayer::GameLayer()
{
	m_MazeSize = { 30, 22 };

	Restart();
}

GameLayer::~GameLayer()
{
	delete m_Maze;
}

void GameLayer::OnUpdate(float frameTime)
{
	// MAZE STEP
	if (m_GameState == GameState::Play)
	{
		m_TimeToMazeStep -= frameTime;
		m_TimeToMazeStep = std::max(0.f, m_TimeToMazeStep);

		if (m_TimeToMazeStep == 0.f)
		{
			m_Maze->Step();
			m_TimeToMazeStep = 100.f;

			if (m_Maze->IsFinished())
			{
				m_GameState = GameState::Finish;
			}
		}
	}
}

void GameLayer::OnRender(Renderer* renderer)
{
	renderer->Clear(SKYBLUE);

	if (m_GameState == GameState::Finish)
	{
		renderer->SetFontSize(55.f);
		renderer->RenderText("Maze is Finished!", { 115, 5 }, WHITE);

		renderer->SetFontSize(32.f);

		float yOffset = 0;
		std::vector<Robot*> robots = m_Maze->GetRobots();
		std::sort(robots.begin(), robots.end(), [](Robot* left, Robot* right) { return left->GetStepsCount() < right->GetStepsCount(); });

		for (int i = 0; i < (int)robots.size(); ++i)
		{
			renderer->RenderQuad(m_RobotsColorMap[robots[i]], { 120.f, 15.f + yOffset }, { 2.f, 2.f });

			std::string text = std::format("Steps count: {}", robots[i]->GetStepsCount());
			renderer->RenderText(text, { 123.f, 14.f + yOffset }, WHITE);

			yOffset += 7.f;
		}
	}
	else
	{
		renderer->SetFontSize(42.f);

		std::string label = m_GameState == GameState::Play ? "Pause" : "Play";
		if (renderer->Button(label, { 125, 27 }, { 20, 10 }, GREEN))
		{
			if (m_GameState == GameState::Play)
				m_GameState = GameState::Pause;

			else if (m_GameState == GameState::Pause)
				m_GameState = GameState::Play;
		}
	}


	renderer->SetFontSize(42.f);

	if (renderer->Button("Restart", { 125, 42 }, { 20, 10 }, GREEN))
	{
		Restart();
	}

	if (renderer->Button("Exit", { 125, 57 }, { 20, 10 }, GREEN))
	{
		Application::Get().Close();
	}

	// GRID
	renderer->RenderQuad(DARKBLUE, { 9, 4 }, { 100, 80 });

	const Vector2 gridStart = { 9, 4 };
	const Vector2 gridSize = { 100, 80 };

	const Vector2 cellPadding = { 0.3f, 0.3f };

	Vector2 cellSize = {
		(gridSize.x - cellPadding.x * (m_MazeSize.x - 1)) / m_MazeSize.x,
		(gridSize.y - cellPadding.y * (m_MazeSize.y - 1)) / m_MazeSize.y };

	Vector2 pos = gridStart;

	for (int y = 0; y < m_MazeSize.y; ++y)
	{
		for (int x = 0; x < m_MazeSize.x; ++x)
		{
			RenderCell(renderer, x, y, pos, cellSize);
			pos.x += cellSize.x + cellPadding.x;
		}

		pos.x = gridStart.x;
		pos.y += cellSize.y + cellPadding.y;
	}
}

void GameLayer::RenderCell(Renderer* renderer, int x, int y, Vector2 pos, Vector2 size)
{
	Cell cellType = m_Maze->GetCell(x, y);

	if (cellType == Cell::Finish)
	{
		renderer->RenderQuad(RED, pos, size);
		renderer->SetFontSize(32.f);
		renderer->RenderCenteredText("?", pos, size, WHITE);
		return;
	}
	else if (cellType == Cell::Wall)
	{
		renderer->RenderQuad(BLACK, pos, size);
		return;
	}

	Color cellColor = WHITE;
	const std::vector<Robot*>& robots = m_Maze->GetRobots();

	for (int i = 0; i < (int)robots.size(); ++i)
	{
		if (x == robots[i]->GetCoordX() && y == robots[i]->GetCoordY())
		{
			cellColor = m_RobotsColorMap[robots[i]];
			break;
		}

		if (robots[i]->IsCellVisited(x, y))
		{
			cellColor = Lerp(m_RobotsColorMap[robots[i]], cellColor, 1.f / 2.f);
		}
	}

	renderer->RenderQuad(cellColor, pos, size);
}

void GameLayer::Restart()
{
	delete m_Maze;
	m_Maze = new Maze((int)m_MazeSize.x, (int)m_MazeSize.y);
	m_GameState = GameState::Pause;

	const std::vector<Robot*>& robots = m_Maze->GetRobots();

	m_RobotsColorMap[robots[0]] = MAGENTA;
	m_RobotsColorMap[robots[1]] = Color(0, 255, 255, 255);
	m_RobotsColorMap[robots[2]] = GOLD;
	m_RobotsColorMap[robots[3]] = GREEN;
}

Color GameLayer::Lerp(const Color& c1, const Color& c2, float t)
{
	Color result;
	result.r = c1.r + (unsigned char)std::round(t * (float)(c2.r - c1.r));
	result.g = c1.g + (unsigned char)std::round(t * (float)(c2.g - c1.g));
	result.b = c1.b + (unsigned char)std::round(t * (float)(c2.b - c1.b));
	result.a = c1.a + (unsigned char)std::round(t * (float)(c2.a - c1.a));

	return result;
}
