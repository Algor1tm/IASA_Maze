#include "MazeGenerator.h"

#include "Application.h"


MazeGenerator::MazeGenerator()
{
	m_Directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
}

void MazeGenerator::SetFinish(int x, int y)
{
	if (IsValid(x, y))
	{
		m_FinishPosX = x;
		m_FinishPosY = y;
	}
}

void MazeGenerator::AddStartPos(int x, int y)
{
	if (IsValid(x, y))
	{
		m_StartPositions.push_back({ x, y });
	}
}

void MazeGenerator::SetSize(int width, int height)
{
	m_Width = width;
	m_Height = height;
}

std::vector<std::vector<Cell>> MazeGenerator::Build()
{
	// Initialize maze with walls
	m_Cells.resize(m_Width);
	for (std::vector<Cell>& row : m_Cells)
	{
		row.resize(m_Height);
		for (Cell& cell : row)
		{
			cell = Cell::Wall;
		}
	}

	for (Vector2i startPos : m_StartPositions)
	{
		m_Cells[startPos.x][startPos.y] = Cell::Path;
		DFS(startPos.x, startPos.y);
	}

	m_Cells[m_FinishPosX][m_FinishPosY] = Cell::Finish;

	return m_Cells;
}

bool MazeGenerator::IsValid(int x, int y) const
{
	return x >= 0 && x < m_Width && y >= 0 && y < m_Height;
}

int MazeGenerator::CountVisitedNeighbors(int x, int y)
{
	int count = 0;

	for (auto [offsetX, offsetY] : m_Directions)
	{
		int nx = x + offsetX;
		int ny = y + offsetY;

		if (!IsValid(nx, ny))
			continue;

		if(m_Cells[nx][ny] != Cell::Wall)
			count++;
	}

	return count;
}

void MazeGenerator::DFS(int x, int y)
{
	std::shuffle(m_Directions.begin(), m_Directions.end(), Application::Get().GetRandomEngine());

	for (auto [offsetX, offsetY] : m_Directions)
	{
		// Get random neighbour not visited cell
		int nx = x + offsetX;
		int ny = y + offsetY;

		if (!IsValid(nx, ny))
			continue;

		if (m_Cells[nx][ny] != Cell::Wall)
			continue;

		// prevent cycles
		if (CountVisitedNeighbors(nx, ny) > 1)
			continue;

		// Carve path
		m_Cells[nx][ny] = Cell::Path;

		// Recursively visit next cell
		DFS(nx, ny);
	}
}
