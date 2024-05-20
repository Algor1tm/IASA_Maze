#include "GameLayer.h"
#include "Application.h"

#include <raylib.h>


GameLayer::GameLayer()
{
	m_MazeSize = { 30, 22 };

	m_Maze = new Maze((unsigned int)m_MazeSize.x, (unsigned int)m_MazeSize.y);
	m_GameState = GameState::Pause;
}

GameLayer::~GameLayer()
{
	delete m_Maze;
}

void GameLayer::OnUpdate(float frameTime)
{
	Renderer& renderer = Application::Get().GetRenderer();

	if (m_GameState == GameState::Play)
	{
		m_TimeToMazeStep -= frameTime;
		m_TimeToMazeStep = std::max(0.f, m_TimeToMazeStep);

		if (m_TimeToMazeStep == 0.f)
		{
			m_Maze->Step();
			m_TimeToMazeStep = 30.f;

			if (m_Maze->IsFinished())
			{
				m_GameState = GameState::Finish;
			}
		}
	}

	renderer.Clear(SKYBLUE);

	if (m_GameState == GameState::Finish)
	{
		renderer.SetFontSize(55.f);
		renderer.RenderText("Maze is Finished!", { 115, 10 }, WHITE);
	}

	renderer.SetFontSize(42.f);

	std::string label;
	switch (m_GameState)
	{
	case GameState::Play:   label = "Pause"; break;
	case GameState::Pause:   label = "Play"; break;
	case GameState::Finish: label = "Restart"; break;
	}

	if (renderer.Button(label, { 125, 30 }, { 20, 10 }, GREEN))
	{
		if (m_GameState == GameState::Play)
		{
			m_GameState = GameState::Pause;
		}
		else if (m_GameState == GameState::Pause)
		{
			m_GameState = GameState::Play;
		}
		else if (m_GameState == GameState::Finish)
		{
			delete m_Maze;
			m_Maze = new Maze((unsigned int)m_MazeSize.x, (unsigned int)m_MazeSize.y);
			m_GameState = GameState::Play;
		}
	}

	if (renderer.Button("Exit", { 125, 50 }, { 20, 10 }, GREEN))
	{
		Application::Get().Close();
	}

	// Grid
	renderer.RenderQuad(DARKBLUE, { 9, 4 }, { 100, 80 });

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
			RenderCell(x, y, pos, cellSize);
			pos.x += cellSize.x + cellPadding.x;
		}

		pos.x = gridStart.x;
		pos.y += cellSize.y + cellPadding.y;
	}
}

void GameLayer::RenderCell(int x, int y, Vector2 pos, Vector2 size)
{
	Renderer& renderer = Application::Get().GetRenderer();

	const Robot* robot = m_Maze->GetRobot();

	if (x == robot->GetCoordX() && y == robot->GetCoordY())
	{
		renderer.RenderQuad(MAGENTA, pos, size);
	}
	else
	{
		CellType cellType = m_Maze->GetCell(x, y).Type;

		Color color = WHITE;
		switch (cellType)
		{
		case CellType::Free:	color = WHITE; break;
		case CellType::Blocked: color = BLACK; break;
		case CellType::Finish:  color = RED; break;
		}

		renderer.RenderQuad(color, pos, size);
	}
}
