#pragma once

#include "Robot.h"

#include <vector>


enum class Cell
{
	Path,
	Wall,
	Finish
};


class Maze
{
public:
	Maze(int width, int height);
	~Maze();

	int GetWidth() const { return (int)m_Cells.size(); }
	int GetHeight() const { return (int)m_Cells[0].size(); }

	Cell GetCell(int x, int y) const { return m_Cells[x][y]; };
	const std::vector<Robot*>& GetRobots() const { return m_Robots; }

	void Step();
	bool IsFinished();

	bool IsValid(int x, int y) const;

private:
	// 2 dimensional table of cells
	std::vector<std::vector<Cell>> m_Cells;
	// For now only 1 Robot, later extend to 4 robots
	std::vector<Robot*> m_Robots;
};
