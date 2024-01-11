#include "Robot.h"
#include "Maze.h"
#include "Application.h"

#include <iostream>


Robot::Robot(Maze* maze, int startX, int startY)
	: m_Maze(maze), m_CoordX(startX), m_CoordY(startY)
{

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

	m_Stack.push({ m_CoordX, m_CoordY });
}

void Robot::Step()
{
	if (m_Stack.empty())
	{
		std::cout << "Failed to find path!\n";
		return;
	}

	auto [m_CoordX, m_CoordY] = m_Stack.top();
	
	if (m_Maze->GetCell(m_CoordX, m_CoordY).Type == CellType::Finish)
	{
		Application::Get().QueueGameEvent(GameEvent::Finish);
		return;
	}

	m_VisitedCellsMap[{m_CoordX, m_CoordY}] = true;

	AddToStack(0, -1);
	AddToStack(-1, 0);
	AddToStack(0, 1);
	AddToStack(1, 0);

	m_Stack.pop();
}

bool Robot::IsVisited(int x, int y)
{
	return m_VisitedCellsMap[{x, y}];
}

void Robot::AddToStack(int offsetX, int offsetY)
{
	int coordX = m_CoordX + offsetX;
	int coordY = m_CoordX + offsetY;

	if (m_Maze->IsValid(coordX, coordY))
	{
		if (m_Maze->GetCell(coordX, coordY).Type == CellType::Free)
		{
			m_Stack.push({ coordX, coordY });
		}
	}
}
