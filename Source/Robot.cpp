#include "Robot.h"
#include "Maze.h"

#include <iostream>


Robot::Robot(Maze* maze)
	: m_Maze(maze)
{

}

void Robot::Step()
{
	// TODO: implement path finder
	// Most likely it will be based on DFS(Depth first search) algorithm
}
