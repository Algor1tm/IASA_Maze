#include "Maze.h"
#include "MazeGenerator.h"


Maze::Maze()
{
	m_Robot = new Robot(this, 0, 0);

	unsigned int width = 40;
	unsigned int height = 20;

	MazeGenerator generator;
	generator.SetStartPos(m_Robot->GetCoordX(), m_Robot->GetCoordY());
	generator.SetFinish(width / 2, height / 2);

	m_Cells = generator.Build(width, height);
}

Maze::~Maze()
{
	delete m_Robot;
}

void Maze::Step()
{
	m_Robot->Step();
}
