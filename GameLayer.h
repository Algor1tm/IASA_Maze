#pragma once

#include "Layer.h"
#include "Maze.h"


class GameLayer : public Layer
{
public:
	GameLayer();
	~GameLayer();

	virtual void OnUpdate() override;

	Maze* GetMaze() { return m_Maze; }

private:
	Maze* m_Maze;
};
