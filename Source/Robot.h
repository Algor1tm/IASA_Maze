#pragma once


class Maze;

// For now only 1 Robot, later extend to 4 type of robots and 1 abstract
class Robot
{
public:
	Robot(Maze* maze);

	void Step();

private:
	Maze* m_Maze;
};
