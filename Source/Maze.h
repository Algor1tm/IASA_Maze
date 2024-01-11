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

	int GetWidth() const { return (int)m_Cells[0].size(); }
	int GetHeight() const { return (int)m_Cells.size(); }

	bool IsValid(int x, int y) const;
	bool IsWall(int x, int y) const;

	Cell GetCell(int x, int y) const { return m_Cells[x][y]; };
	const Robot* GetRobot() const { return m_Robot; }

	void Step();

private:
	// 2 dimensional table of cells
	std::vector<std::vector<Cell>> m_Cells;
	// For now only 1 Robot, later extend to 4 robots
	Robot* m_Robot;
};