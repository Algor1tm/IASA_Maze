#pragma once

#include "Layer.h"
#include "Maze.h"


class GameLayer : public Layer
{
public:
	GameLayer();
	~GameLayer();

	virtual void OnUpdate() override;
	virtual void OnGameEvent(GameEvent event) override;

	const Maze* GetMaze() const { return m_Maze; }

private:
	Maze* m_Maze;
};
