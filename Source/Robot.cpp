#include "Robot.h"
#include "Maze.h"
#include "Application.h"

#include <iostream>


Robot::Robot(Maze* maze, int startX, int startY)
	: m_Maze(maze), m_CoordX(startX), m_CoordY(startY)
{
	m_Directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
}

void Robot::Start()
{
	m_VisitedCellsMap.reserve(m_Maze->GetWidth() * m_Maze->GetHeight());

	for (int y = 0; y < m_Maze->GetHeight(); ++y)
	{
		for (int x = 0; x < m_Maze->GetWidth(); ++x)
		{
			m_VisitedCellsMap[{x, y}] = false;
		}
	}

	m_DFSStack.push({ m_CoordX, m_CoordY });
	m_Path.push({ m_CoordX, m_CoordY });
}

void Robot::Step()
{
	if (m_DFSStack.empty())
	{
		std::cout << "Failed to find path!\n";
		return;
	}

	// Go back to next neighbour
	if (m_Path.top() != m_DFSStack.top())
	{
		std::pair<int, int> coords = m_Path.top();
		m_CoordX = coords.first;
		m_CoordY = coords.second;
		m_Path.pop();
	}
	// Choose random neighbour and go till dead end or finish
	else
	{
		std::pair<int, int> coords = m_DFSStack.top();
		m_CoordX = coords.first;
		m_CoordY = coords.second;
		m_DFSStack.pop();

		m_VisitedCellsMap.at({ m_CoordX, m_CoordY }) = true;

		CheckNeighbours();
	}
}

void Robot::CheckNeighbours()
{
	std::shuffle(m_Directions.begin(), m_Directions.end(), Application::Get().GetRandomEngine());

	for (auto dir : m_Directions)
	{
		TryAddNeighbour(dir.first, dir.second);
	}
}

void Robot::TryAddNeighbour(int offsetX, int offsetY)
{
	int coordX = m_CoordX + offsetX;
	int coordY = m_CoordY + offsetY;

	if (!m_Maze->IsValid(coordX, coordY))
	{
		return;
	}

	if (m_Maze->GetCell(coordX, coordY).Type == CellType::Finish)
	{
		Application::Get().QueueGameEvent(GameEvent::Finish);
		return;
	}

	if (!IsVisited(coordX, coordY))
	{
		if (m_Maze->GetCell(coordX, coordY).Type == CellType::Free)
		{
			m_DFSStack.push({ coordX, coordY });

			m_Path.push({ coordX, coordY });
			m_Path.push({ m_CoordX, m_CoordY });
		}
	}
}

bool Robot::IsVisited(int x, int y) const
{
	return m_VisitedCellsMap.at({ x, y });
}
