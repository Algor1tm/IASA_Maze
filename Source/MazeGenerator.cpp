#include "MazeGenerator.h"
#include <random>
#include<time.h>
#include "Application.h"


MazeGenerator::MazeGenerator()
{
	m_Directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
}

void MazeGenerator::SetFinish(int x, int y)
{
	m_FinishPosX = x;
	m_FinishPosY = y;
}

void MazeGenerator::SetStartPos(int x, int y)
{
	m_StartPosX = x;
	m_StartPosY = y;
}

void MazeGenerator::SetSize(int width, int height)
{
	m_Width = width;
	m_Height = height;
}



std::vector<std::vector<Cell>> DefaultMazeFactory::CreateMaze(int width, int height, int startX, int startY, int finishX, int finishY)
{

    std::vector<std::vector<Cell>> maze(width, std::vector<Cell>(height, Cell(CellType::Blocked)));

    maze[startX][startY].Type = CellType::Free;
    maze[finishX][finishY].Type = CellType::Finish;

    std::stack<std::pair<int, int>> dfsStack;
    dfsStack.push({ startX, startY });

    while (!dfsStack.empty())
    {
        int x, y;
        std::tie(x, y) = dfsStack.top();
        dfsStack.pop();

        std::vector<std::pair<int, int>> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
        std::shuffle(directions.begin(), directions.end(), Application::Get().GetRandomEngine());

        for (const auto& direction : directions)
        {
            int nx = x + 2 * direction.first;
            int ny = y + 2 * direction.second;

            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
            {
                if (maze[nx][ny].Type == CellType::Blocked)
                {
                    maze[nx][ny].Type = CellType::Free;
                    maze[x + direction.first][y + direction.second].Type = CellType::Free;
                    dfsStack.push({ nx, ny });
                }
            }
        }
    }
    maze[finishX][finishY].Type = CellType::Finish;
    return maze;
}



std::vector<std::vector<Cell>> RandomMazeFactory::CreateMaze(int width, int height, int startX, int startY, int finishX, int finishY)
{
    srand(time(NULL));

    std::vector<std::vector<Cell>> maze(width, std::vector<Cell>(height, Cell(CellType::Blocked)));

    maze[startX][startY].Type = CellType::Free;

    int finishX1 = std::rand() % width;
    int finishY1 = std::rand() % height;
    maze[finishX1][finishY1].Type = CellType::Finish;

    int finishX2 = std::rand() % width;
    int finishY2 = std::rand() % height;

    while ((finishX2 == finishX1 && finishY2 == finishY1) ||
        (finishX2 == startX && finishY2 == startY)) 
    {
        finishX2 = std::rand() % width;
        finishY2 = std::rand() % height;
    }

    maze[finishX2][finishY2].Type = CellType::Finish;

    std::stack<std::pair<int, int>> dfsStack;
    dfsStack.push({ startX, startY });

    while (!dfsStack.empty())
    {
        int x, y;
        std::tie(x, y) = dfsStack.top();
        dfsStack.pop();

        std::vector<std::pair<int, int>> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
        std::shuffle(directions.begin(), directions.end(), Application::Get().GetRandomEngine());

        std::shuffle(directions.begin(), directions.end(), Application::Get().GetRandomEngine());

        for (const auto& direction : directions)
        {
            int nx = x + 2 * direction.first;
            int ny = y + 2 * direction.second;

            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
            {
                if (maze[nx][ny].Type == CellType::Blocked)
                {
                    maze[nx][ny].Type = CellType::Free;

                    if (std::rand() % 5 != 0)
                    {
                        maze[x + direction.first][y + direction.second].Type = CellType::Free;
                        dfsStack.push({ nx, ny });
                    }
                }
            }
        }
    }

    return maze;
    
}

void MazeGenerator::SetMazeFactory(MazeFactory* factory)
{
    m_MazeFactory = factory;
}

std::vector<std::vector<Cell>> MazeGenerator::BuildMaze()
{

    return m_MazeFactory->CreateMaze(m_Width, m_Height, m_StartPosX, m_StartPosY, m_FinishPosX, m_FinishPosY);
}



