#pragma once

#include <stack>
#include <unordered_map>
#include <xhash>


class Maze;

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


// For now only 1 Robot, later extend to 4 type of robots and 1 abstract
class Robot
{
public:
	Robot(Maze* maze, int startX, int startY);

	int GetCoordX() const { return m_CoordX; }
	int GetCoordY() const { return m_CoordY; }

	void Start();
	void Step();

private:
	void CheckNeighbours();
	void TryAddNeighbour(int offsetX, int offsetY);
	bool IsVisited(int x, int y) const;

private:
	Maze* m_Maze;
	int m_CoordX, m_CoordY;
	std::vector<std::pair<int, int>> m_Directions;
	std::stack<std::pair<int, int>> m_DFSStack;
	std::stack<std::pair<int, int>> m_Path;
	std::unordered_map<std::pair<int, int>, bool> m_VisitedCellsMap;
};
