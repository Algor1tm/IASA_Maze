#pragma once 

#include "Maze.h"



// Random acyclic maze generator
// 
// Some references
// https://www.geeksforgeeks.org/random-acyclic-maze-generator-with-given-entry-and-exit-point/
// https://www.bo-song.com/how-to-generate-a-maze-with-c/

class MazeFactory
{
public:
   
    virtual std::vector<std::vector<Cell>> CreateMaze(int width, int height, int startX, int startY, int finishX, int finishY) = 0;
    virtual ~MazeFactory() {}
};

class DefaultMazeFactory : public MazeFactory
{
public:
    std::vector<std::vector<Cell>> CreateMaze(int width, int height, int startX, int startY, int finishX, int finishY) override;
};

class RandomMazeFactory : public MazeFactory
{
public:
    std::vector<std::vector<Cell>> CreateMaze(int width, int height, int startX, int startY, int finishX, int finishY) override;
};

class MazeGenerator
{
public:
    MazeGenerator();

    void SetMazeFactory(MazeFactory* factory);
    std::vector<std::vector<Cell>> BuildMaze();

    void SetFinish(int x, int y);
    void SetStartPos(int x, int y);
    void SetSize(int width, int height);

private:
    MazeFactory* m_MazeFactory;
    std::vector<std::pair<int, int>> m_Directions;
    std::vector<std::vector<Cell>> m_Cells;
    int m_Width, m_Height;
    int m_StartPosX, m_StartPosY;
    int m_FinishPosX, m_FinishPosY;
};