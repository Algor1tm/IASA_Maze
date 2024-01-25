#include "Maze.h"
#include "MazeGenerator.h"


Maze::Maze()
{
	m_Robot = new Robot(new JumperRobotBehaviour(), this, 0, 0);

	unsigned int width = 20;
	unsigned int height = 10;

	MazeGenerator generator;
	generator.SetStartPos(m_Robot->GetCoordX(), m_Robot->GetCoordY());
	generator.SetFinish(width / 2, height / 2);
	generator.SetSize(width, height);

	MazeFactory* factory = new RandomMazeFactory();
	//MazeFactory* factory = new DefaultMazeFactory();
	generator.SetMazeFactory(factory);

	m_Cells = generator.BuildMaze();
}

Maze::~Maze()
{
	delete m_Robot;
}

void Maze::Start()
{
	m_Robot->Start();
}

void Maze::Step()
{
	m_Robot->Step();
}

bool Maze::IsValid(int x, int y) const
{
	return x >= 0 && x < GetWidth() && y >= 0 && y < GetHeight();
}
