#pragma once

#include "Vector2i.h"

#include <stack>
#include <unordered_map>

class Maze;
class RobotStrategy;

class PathFinder
{
public:
	PathFinder(const Maze* maze, int currentX, int currentY);

	bool HasPath() const;
	bool IsFound() const;

	Vector2i FindNextCell(RobotStrategy* strategy);
	bool IsVisited(int x, int y) const;

private:
	void CheckNeighbours(RobotStrategy* strategy);

private:
	const Maze* m_Maze;
	std::stack<Vector2i> m_DFSStack;
	std::stack<Vector2i> m_Path;
	std::unordered_map<Vector2i, bool> m_VisitedCellsMap;
	int m_CoordX, m_CoordY;
	bool m_FindPath;
};


class Robot
{
public:
	Robot(RobotStrategy* strategy, Maze* maze, int startX, int startY);
	~Robot();

	int GetCoordX() const;
	int GetCoordY() const;
	int GetStepsCount() const; 

	void Step();
	bool IsFinished() const;
	bool IsCellVisited(int x, int y) const;

private:
	Maze* m_Maze;
	PathFinder m_PathFinder;
	RobotStrategy* m_Strategy;
	int m_CoordX, m_CoordY;
	int m_StepsCount;
};


class RobotStrategy
{
public:
	virtual const std::vector<Vector2i>& GetAllPossibleMoves() = 0;
};


class DefaultRobotStrategy : public RobotStrategy
{
public:
	DefaultRobotStrategy();
	virtual const std::vector<Vector2i>& GetAllPossibleMoves() override;

private:
	std::vector<Vector2i> m_Moves;
};


class DiagonalRobotStrategy : public RobotStrategy
{
public:
	DiagonalRobotStrategy();
	virtual const std::vector<Vector2i>& GetAllPossibleMoves() override;

private:
	std::vector<Vector2i> m_Moves;
};


class JumperRobotStrategy : public RobotStrategy
{
public:
	JumperRobotStrategy();
	virtual const std::vector<Vector2i>& GetAllPossibleMoves() override;

private:
	const int m_DefaultDelay = 5;

private:
	int m_DelayBeforeJump;
	std::vector<Vector2i> m_NoJumpMoves;
	std::vector<Vector2i> m_AllMoves;
};
