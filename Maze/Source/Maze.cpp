#include "Maze.h"
#include "MazeGenerator.h"


Maze::Maze(unsigned int width, unsigned int height)
{
	MazeGenerator generator;
	generator.SetStartPos(0, 0);
	generator.SetFinish(width / 2, height / 2);
	generator.SetSize(width, height);

	m_Cells = generator.Build();

	m_Robot = new Robot(new DefaultRobotBehaviour(), this, 0, 0);
}

Maze::~Maze()
{
	delete m_Robot;
}

void Maze::Step()
{
	m_Robot->Step();
}

bool Maze::IsFinished()
{
	return m_Robot->IsFinished();
}

bool Maze::IsValid(int x, int y) const
{
	return x >= 0 && x < GetWidth() && y >= 0 && y < GetHeight();
}
