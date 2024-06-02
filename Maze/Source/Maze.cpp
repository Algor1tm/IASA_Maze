#include "Maze.h"
#include "MazeGenerator.h"


Maze::Maze(int width, int height)
{
	MazeGenerator generator;
	generator.SetSize(width, height);
	generator.SetFinish(width / 2, height / 2);

	generator.AddStartPos(0, 0);
	generator.AddStartPos(width - 1, 0);
	generator.AddStartPos(width - 1, height - 1);
	generator.AddStartPos(0, height - 1);

	m_Cells = generator.Build();

	m_Robots.push_back(new Robot(new DefaultRobotStrategy(), this, 0, 0));
	m_Robots.push_back(new Robot(new DiagonalRobotStrategy(), this, width - 1, 0));
	m_Robots.push_back(new Robot(new JumperRobotStrategy(), this, width - 1, height - 1));
	m_Robots.push_back(new Robot(new DefaultRobotStrategy(), this, 0, height - 1));
}

Maze::~Maze()
{
	for (Robot* robot : m_Robots)
		delete robot;
}

void Maze::Step()
{
	for(Robot* robot : m_Robots)
		robot->Step();
}

bool Maze::IsFinished()
{
	bool isAllFinished = true;

	for(const Robot* robot : m_Robots)
		isAllFinished = isAllFinished && robot->IsFinished();

	return isAllFinished;
}

bool Maze::IsValid(int x, int y) const
{
	return x >= 0 && x < GetWidth() && y >= 0 && y < GetHeight();
}
