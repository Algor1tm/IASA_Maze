#pragma once

#include "Robot.h"

#include <vector>


enum class CellType
{
	Blocked, Free, Finish
};

struct Cell
{
	CellType Type;
	// Maybe add color
};


class Maze
{
public:
	Maze();
	~Maze();

	unsigned int GetWidth() { return (unsigned int)m_Cells[0].size(); }
	unsigned int GetHeight() { return (unsigned int)m_Cells.size(); }

	Cell GetCell(unsigned int x, unsigned int y) { return m_Cells[y][x]; };

	void Step();

private:
	// 2 dimensional table of cells
	std::vector<std::vector<Cell>> m_Cells;
	// For now only 1 Robot, later extend to 4 robots
	Robot* m_Robot;
};
