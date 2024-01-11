#pragma once


class Maze;

// For now only 1 Robot, later extend to 4 type of robots and 1 abstract
class Robot
{
public:
	Robot(Maze* maze, int startX, int startY);

	int GetCoordX() const { return m_CoordX; }
	int GetCoordY() const { return m_CoordY; }

	void Step();

private:
	Maze* m_Maze;
	int m_CoordX, m_CoordY;
};