#include "UILayer.h"
#include "Application.h"

#include <iostream>


UILayer::UILayer()
{

}

UILayer::~UILayer()
{

}

void UILayer::OnUpdate()
{
	const Robot* robot = m_Maze->GetRobot();
	int robotX = robot->GetCoordX();
	int robotY = robot->GetCoordY();

	for (int x = 0; x < m_Maze->GetWidth(); ++x)
	{
		for (int y = 0; y < m_Maze->GetHeight(); ++y)
		{
			if (robotX == x && robotY == y)
			{
				std::cout << "@";
			}
			else
			{
				Cell cell = m_Maze->GetCell(x, y);
				std::cout << CellToChar(cell);
			}
		}

		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;
}


char UILayer::CellToChar(Cell cell)
{
	switch (cell.Type)
	{
	case CellType::Blocked: return '#';
	case CellType::Free: return ' ';
	case CellType::Finish: return '?';
	}

	return '~';
}