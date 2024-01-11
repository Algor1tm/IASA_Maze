#pragma once 

#include "Maze.h"

#include <random>


// Random acyclic maze generator
// 
// Some references
// https://www.geeksforgeeks.org/random-acyclic-maze-generator-with-given-entry-and-exit-point/
// https://www.bo-song.com/how-to-generate-a-maze-with-c/


class MazeGenerator
{
public:
	MazeGenerator();

	void SetFinish(int x, int y);
	void SetStartPos(int x, int y);
	std::vector<std::vector<Cell>> Build(int width, int height);

private:
	void DFS(int x, int y);
	bool IsValid(int x, int y) const;
	int CountVisitedNeighbors(int x, int y);

private:
	std::mt19937 m_RandomEngine;
	std::vector<int> m_Directions;
	std::vector<std::vector<Cell>> m_Cells;
	int m_Width, m_Height;
	int m_StartPosX, m_StartPosY;
	int m_FinishPosX, m_FinishPosY;
};
