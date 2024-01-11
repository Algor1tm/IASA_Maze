#include "UILayer.h"
#include "Application.h"

#include <iostream>
#include <thread>


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

	for (int y = 0; y < m_Maze->GetHeight(); ++y)
	{
		for (int x = 0; x < m_Maze->GetWidth(); ++x)
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

	std::cout << std::endl << std::endl << std::endl;
}

void UILayer::OnGameEvent(GameEvent event)
{
	using namespace std::chrono;

	if (event == GameEvent::Start)
	{
		const Robot* robot = m_Maze->GetRobot();

		std::cout << "--------------------MAZE SIMULATION--------------------\n";
		std::cout << "Maze: width = " << m_Maze->GetWidth() << ", height = " << m_Maze->GetHeight() << std::endl;
		std::cout << "Robot 1: start pos = (" << robot->GetCoordX() << ", " << robot->GetCoordY() << ")\n";

		const int seconds = 5;
		std::cout << "Start in " << seconds << " seconds!\n\n\n";

		steady_clock::time_point timePoint = high_resolution_clock::now() + std::chrono::seconds(seconds);
		std::this_thread::sleep_until(timePoint);
	}
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
