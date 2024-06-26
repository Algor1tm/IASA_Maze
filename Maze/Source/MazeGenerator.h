#pragma once 

#include "Maze.h"


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
	void AddStartPos(int x, int y);
	void SetSize(int width, int height);

	std::vector<std::vector<Cell>> Build();

private:
	void DFS(int x, int y);
	bool IsValid(int x, int y) const;
	int CountVisitedNeighbors(int x, int y);

private:
	std::vector<Vector2i> m_Directions;
	std::vector<std::vector<Cell>> m_Cells;
	int m_Width, m_Height;

	std::vector<Vector2i> m_StartPositions;
	int m_FinishPosX, m_FinishPosY;
};
