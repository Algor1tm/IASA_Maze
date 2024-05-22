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
	return !m_DFSStack.empty();
}

bool PathFinder::IsFound() const
{
	return m_FindPath;
}

Vector2i PathFinder::FindNextCell(RobotStrategy* strategy)
{
	Vector2i dfsTop = m_DFSStack.top();

	if (m_Maze->GetCell(dfsTop.x, dfsTop.y) == Cell::Finish)
	{
		m_FindPath = true;
		m_CoordX = dfsTop.x;
		m_CoordY = dfsTop.y;
		return dfsTop;
	}

	// Go back to next neighbour
	if(m_Path.top() != dfsTop)
	{
		Vector2i pathTop = m_Path.top();
		m_CoordX = pathTop.x;
		m_CoordY = pathTop.y;
		m_Path.pop();
		return pathTop;
	}
	
	m_CoordX = dfsTop.x;
	m_CoordY = dfsTop.y;
	m_DFSStack.pop();

	m_VisitedCellsMap.at({ m_CoordX, m_CoordY }) = true;

	CheckNeighbours(strategy);

	return dfsTop;
}

void PathFinder::CheckNeighbours(RobotStrategy* strategy)
{
	std::vector<Vector2i> neighbours;
	std::vector<Vector2i> moves = strategy->GetAllPossibleMoves();

	for (auto dir : moves)
	{
		int coordX = m_CoordX + dir.x;
		int coordY = m_CoordY + dir.y;

		if (!m_Maze->IsValid(coordX, coordY))
			continue;

		if (m_Maze->GetCell(coordX, coordY) == Cell::Finish)
		{
			m_DFSStack.push({ coordX, coordY });
			return;
		}

		if (m_Maze->GetCell(coordX, coordY) == Cell::Wall)
			continue;

		if (IsVisited(coordX, coordY))
			continue;

		neighbours.push_back({ coordX, coordY });
	}

	if (neighbours.empty())
		m_Path.pop();

 	for (size_t i = 0; i < neighbours.size(); ++i)
	{
		int coordX = neighbours[i].x;
		int coordY = neighbours[i].y;

		if (i > 0)
			m_Path.push({ m_CoordX, m_CoordY });

		m_Path.push({ coordX, coordY });
		m_DFSStack.push({ coordX, coordY });
	}
}

bool PathFinder::IsVisited(int x, int y) const
{
	return m_VisitedCellsMap.at({ x, y });
}

Robot::Robot(RobotStrategy* strategy, Maze* maze, int startX, int startY)
	: m_PathFinder(maze, startX, startY), m_Strategy(strategy)
{
	m_Maze = maze;
	m_CoordX = startX;
	m_CoordY = startY;
	m_StepsCount = 0;
}

Robot::~Robot()
{
	delete m_Strategy;
}

void Robot::Step()
{
	if (!m_PathFinder.HasPath())
	{
		std::cout << "Failed to find path!\n";
		return;
	}

	if (m_PathFinder.IsFound())
		return;

	Vector2i coords = m_PathFinder.FindNextCell(m_Strategy);
	m_CoordX = coords.x;
	m_CoordY = coords.y;

	m_StepsCount++;
}

bool Robot::IsFinished() const
{
	return m_PathFinder.IsFound();
}

int Robot::GetCoordX() const
{
	return m_CoordX;
}

int Robot::GetCoordY() const
{
	return m_CoordY;
}

int Robot::GetStepsCount() const
{
	return m_StepsCount;
}

bool Robot::IsCellVisited(int x, int y) const
{
	return m_PathFinder.IsVisited(x, y);
}


DefaultRobotStrategy::DefaultRobotStrategy()
{
	m_Moves = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
}

const std::vector<Vector2i>& DefaultRobotStrategy::GetAllPossibleMoves()
{
	std::shuffle(m_Moves.begin(), m_Moves.end(), Application::Get().GetRandomEngine());
	return m_Moves;
}

DiagonalRobotStrategy::DiagonalRobotStrategy()
{
	m_Moves = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1} };
}

const std::vector<Vector2i>& DiagonalRobotStrategy::GetAllPossibleMoves()
{
	std::shuffle(m_Moves.begin(), m_Moves.end(), Application::Get().GetRandomEngine());
	return m_Moves;
}

JumperRobotStrategy::JumperRobotStrategy()
{
	m_NoJumpMoves = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
	m_AllMoves = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {0, 2}, {0, -2}, {2, 0}, {-2, 0} };
	m_DelayBeforeJump = m_DefaultDelay;
}

const std::vector<Vector2i>& JumperRobotStrategy::GetAllPossibleMoves()
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
