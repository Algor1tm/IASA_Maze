#pragma once

#include <stack>
#include <unordered_map>
#include <xhash>


class Maze;
class RobotBehaviour;

namespace std
{
	// Cantor pairing used for hashing two integers
	//https://stackoverflow.com/questions/919612/mapping-two-integers-to-one-in-a-unique-and-deterministic-way

	template<>
	struct hash<pair<int, int>>
	{
		size_t operator()(const pair<int, int>& p) const
		{
			int integer = (p.first + p.second) * (p.first + p.second + 1) / 2 + p.first;
			return hash<int>()(integer);
		}
	};
}

class PathFinder
{
public:
	PathFinder();

	void Start(const Maze* maze, int currentX, int currentY);

	bool HasPath() const;
	bool FindPath() const;

	std::pair<int, int> FindNextCell(RobotBehaviour* behaviour);
	bool IsVisited(int x, int y) const;

private:
	void CheckNeighbours(RobotBehaviour* behaviour);
	void TryAddNeighbour(int offsetX, int offsetY);

private:
	const Maze* m_Maze;
	std::stack<std::pair<int, int>> m_DFSStack;
	std::stack<std::pair<int, int>> m_Path;
	std::unordered_map<std::pair<int, int>, bool> m_VisitedCellsMap;
	int m_CoordX, m_CoordY;
	bool m_FindPath;
};


class Robot
{
public:
	Robot(RobotBehaviour* behaviour, Maze* maze, int startX, int startY);
	~Robot();

	int GetCoordX() const;
	int GetCoordY() const;

	void Start();
	void Step();

private:
	Maze* m_Maze;
	PathFinder m_PathFinder;
	RobotBehaviour* m_Behaviour;
	int m_CoordX, m_CoordY;
};


class RobotBehaviour
{
public:
	virtual const std::vector<std::pair<int, int>>& GetAllPossibleMoves() = 0;
};


class DefaultRobotBehaviour : public RobotBehaviour
{
public:
	DefaultRobotBehaviour();
	virtual const std::vector<std::pair<int, int>>& GetAllPossibleMoves() override;

private:
	std::vector<std::pair<int, int>> m_Moves;
};


class DiagonalRobotBehaviour : public RobotBehaviour
{
public:
	DiagonalRobotBehaviour();
	virtual const std::vector<std::pair<int, int>>& GetAllPossibleMoves() override;

private:
	std::vector<std::pair<int, int>> m_Moves;
};


class JumperRobotBehaviour : public RobotBehaviour
{
public:
	JumperRobotBehaviour();
	virtual const std::vector<std::pair<int, int>>& GetAllPossibleMoves() override;

private:
	const int m_DefaultDelay = 5;

private:
	int m_DelayBeforeJump;
	std::vector<std::pair<int, int>> m_NoJumpMoves;
	std::vector<std::pair<int, int>> m_AllMoves;
};
