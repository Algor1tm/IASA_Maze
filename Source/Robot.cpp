#include "Robot.h"
#include "Maze.h"

#include <iostream>


Robot::Robot(Maze* maze, int startX, int startY)
	: m_Maze(maze), m_CoordX(startX), m_CoordY(startY)
{

}

void Robot::Step()
{
	// TODO: implement path finder
	// Most likely it will be based on DFS(Depth first search) algorithm
}