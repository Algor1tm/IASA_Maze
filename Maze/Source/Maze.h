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
};


class Maze
{
public:
	Maze();
	~Maze();

	int GetWidth() const { return (int)m_Cells.size(); }
	int GetHeight() const { return (int)m_Cells[0].size(); }

	Cell GetCell(int x, int y) const { return m_Cells[x][y]; };
	const Robot* GetRobot() const { return m_Robot; }

	void Start();
	void Step();

	bool IsValid(int x, int y) const;

private:
	// 2 dimensional table of cells
	std::vector<std::vector<Cell>> m_Cells;
	// For now only 1 Robot, later extend to 4 robots
	Robot* m_Robot;
};
