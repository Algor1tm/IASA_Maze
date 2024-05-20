#include "Robot.h"
#include "Maze.h"
#include "Application.h"

#include <iostream>


PathFinder::PathFinder(const Maze* maze, int currentX, int currentY)
{
	m_FindPath = false;
	m_Maze = maze;
	m_CoordX = currentX;
	m_CoordY = currentY;

	m_VisitedCellsMap.reserve(maze->GetWidth() * maze->GetHeight());

	for (int y = 0; y < maze->GetHeight(); ++y)
	{
		for (int x = 0; x < maze->GetWidth(); ++x)
		{
			m_VisitedCellsMap[{x, y}] = false;
		}
	}

	m_DFSStack.push({ currentX, currentY });
	m_Path.push({ currentX, currentY });
}

bool PathFinder::HasPath() const
{
	return !m_FindPath && !m_DFSStack.empty();
}

bool PathFinder::FindPath() const
{
	return m_FindPath;
}

std::pair<int, int> PathFinder::FindNextCell(RobotBehaviour* behaviour)
{
	if (m_FindPath)
		return { m_CoordX, m_CoordY };

	std::pair<int, int> coords;

	// Go back to next neighbour
	if (m_Path.top() != m_DFSStack.top())
	{
		coords = m_Path.top();
		m_CoordX = coords.first;
		m_CoordY = coords.second;
		m_Path.pop();
		return coords;
	}

	// Choose random neighbour and go till dead end or finish
	coords = m_DFSStack.top();
	m_CoordX = coords.first;
	m_CoordY = coords.second;
	m_DFSStack.pop();

	m_VisitedCellsMap.at({ m_CoordX, m_CoordY }) = true;

	CheckNeighbours(behaviour);

	return coords;
}

void PathFinder::CheckNeighbours(RobotBehaviour* behaviour)
{
	for (auto dir : behaviour->GetAllPossibleMoves())
	{
		TryAddNeighbour(dir.first, dir.second);
	}
}

void PathFinder::TryAddNeighbour(int offsetX, int offsetY)
{
	int coordX = m_CoordX + offsetX;
	int coordY = m_CoordY + offsetY;

	if (!m_Maze->IsValid(coordX, coordY))
	{
		return;
	}

	if (m_Maze->GetCell(coordX, coordY).Type == CellType::Finish)
	{
		m_FindPath = true;
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

bool PathFinder::IsVisited(int x, int y) const
{
	return m_VisitedCellsMap.at({ x, y });
}


Robot::Robot(RobotBehaviour* behaviour, Maze* maze, int startX, int startY)
	: m_PathFinder(m_Maze, m_CoordX, m_CoordY), m_Behaviour(behaviour), m_Maze(maze), m_CoordX(startX), m_CoordY(startY)
{
	
}

Robot::~Robot()
{
	delete m_Behaviour;
}

void Robot::Step()
{
	if (!m_PathFinder.HasPath())
	{
		std::cout << "Failed to find path!\n";
		return;
	}

	std::pair<int, int> coords = m_PathFinder.FindNextCell(m_Behaviour);
	m_CoordX = coords.first;
	m_CoordY = coords.second;
}

bool Robot::IsFinished()
{
	return m_PathFinder.FindPath();
}

int Robot::GetCoordX() const
{
	return m_CoordX;
}

int Robot::GetCoordY() const
{
	return m_CoordY;
}


DefaultRobotBehaviour::DefaultRobotBehaviour()
{
	m_Moves = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
}

const std::vector<std::pair<int, int>>& DefaultRobotBehaviour::GetAllPossibleMoves()
{
	std::shuffle(m_Moves.begin(), m_Moves.end(), Application::Get().GetRandomEngine());
	return m_Moves;
}

DiagonalRobotBehaviour::DiagonalRobotBehaviour()
{
	m_Moves = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1} };
}

const std::vector<std::pair<int, int>>& DiagonalRobotBehaviour::GetAllPossibleMoves()
{
	std::shuffle(m_Moves.begin(), m_Moves.end(), Application::Get().GetRandomEngine());
	return m_Moves;
}

JumperRobotBehaviour::JumperRobotBehaviour()
{
	m_NoJumpMoves = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
	m_AllMoves = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {0, 2}, {0, -2}, {2, 0}, {-2, 0} };
	m_DelayBeforeJump = m_DefaultDelay;
}

const std::vector<std::pair<int, int>>& JumperRobotBehaviour::GetAllPossibleMoves()
{
	if (m_DelayBeforeJump <= 0)
	{
		std::shuffle(m_AllMoves.begin(), m_AllMoves.begin() + 4, Application::Get().GetRandomEngine());
		std::shuffle(m_AllMoves.begin() + 4, m_AllMoves.end(), Application::Get().GetRandomEngine());
		m_DelayBeforeJump = m_DefaultDelay;
		return m_AllMoves;
	}

	m_DelayBeforeJump--;
	return m_NoJumpMoves;
}
