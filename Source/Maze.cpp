#include "Maze.h"


Maze::Maze()
{
	m_Robot = new Robot(this, 0, 0);

	// TODO: Generate random Maze
	// Find algorithm in the Internet


	// Example of maze, you can use it for check UI and path finder correctness

	// maze 5x5
	// #   # # #
	// #   # # #
	// #       #
	// # # #   ! 
	// # # # # # 

	unsigned int height = 5;
	unsigned int width = 5;

	m_Cells.resize(height);
	for (std::vector<Cell>& row : m_Cells)
	{
		row.resize(width);
		for (Cell& cell : row)
		{
			cell.Type = CellType::Blocked;
		}
	}

	m_Cells[0][1].Type = CellType::Free;
	m_Cells[1][1].Type = CellType::Free;
	m_Cells[2][1].Type = CellType::Free;
	m_Cells[2][2].Type = CellType::Free;
	m_Cells[2][3].Type = CellType::Free;
	m_Cells[3][3].Type = CellType::Free;
	m_Cells[3][4].Type = CellType::Finish;
}

Maze::~Maze()
{
	delete m_Robot;
}

void Maze::Step()
{
	m_Robot->Step();
}