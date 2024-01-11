#include "MazeGenerator.h"


MazeGenerator::MazeGenerator()
{
	m_RandomEngine = std::mt19937(std::random_device()());
	m_Directions = { 0, 1, 2, 3 };
	m_Width = 0;
	m_Height = 0;
}

void MazeGenerator::SetFinish(int x, int y)
{
	m_FinishPosX = x;
	m_FinishPosY = y;
}

void MazeGenerator::SetStartPos(int x, int y)
{
	m_StartPosX = x;
	m_StartPosY = y;
}

std::vector<std::vector<Cell>> MazeGenerator::Build(int width, int height)
{
	m_Width = width;
	m_Height = height;
	// Initialize maze with walls
	m_Cells.resize(width);
	for (std::vector<Cell>& row : m_Cells)
	{
		row.resize(height);
		for (Cell& cell : row)
		{
			cell.Type = CellType::Blocked;
		}
	}

	m_Cells[m_StartPosX][m_StartPosY].Type = CellType::Free;

	DFS(m_StartPosX, m_StartPosY);

	m_Cells[m_FinishPosX][m_FinishPosY].Type = CellType::Finish;

	return m_Cells;
}

bool MazeGenerator::IsValid(int x, int y) const
{
	return x >= 0 && x < m_Width && y >= 0 && y < m_Height;
}

int MazeGenerator::CountVisitedNeighbors(int x, int y)
{
	const int dX[] = { 0, 0, 1, -1 };
	const int dY[] = { 1, -1, 0, 0 };

	int count = 0;

	for (int dir : m_Directions)
	{
		int nx = x + dX[dir];
		int ny = y + dY[dir];

		if (!IsValid(nx, ny))
			continue;

		if(m_Cells[nx][ny].Type != CellType::Blocked)
			count++;
	}

	return count;
}

void MazeGenerator::DFS(int x, int y)
{
	const int dX[] = { 0, 0, 1, -1 };
	const int dY[] = { 1, -1, 0, 0 };

	std::shuffle(m_Directions.begin(), m_Directions.end(), m_RandomEngine);

	for (int dir : m_Directions)
	{
		// Get random neighbour not visited cell
		int nx = x + dX[dir];
		int ny = y + dY[dir];

		if (!IsValid(nx, ny))
			continue;

		if (m_Cells[nx][ny].Type != CellType::Blocked)
			continue;

		// prevent cycles
		if (CountVisitedNeighbors(nx, ny) > 1)
			continue;

		// Carve path
		m_Cells[nx][ny].Type = CellType::Free;

		// Recursively visit next cell
		DFS(nx, ny);
	}
}
