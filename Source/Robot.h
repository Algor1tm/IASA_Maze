#pragma once

#include <stack>
#include <unordered_map>


class Maze;


namespace std
{
	template<>
	struct hash<pair<int, int>>
	{
		size_t operator()(const pair<int, int>& coords)
		{

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
	bool IsVisited(int x, int y);
	void AddToStack(int offsetX, int offsetY);

private:
	Maze* m_Maze;
	int m_CoordX, m_CoordY;
	std::stack<std::pair<int, int>> m_Stack;
	std::unordered_map<std::pair<int, int>, bool> m_VisitedCellsMap;
};
