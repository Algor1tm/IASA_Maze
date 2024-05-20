#pragma once

#include "Layer.h"
#include "Maze.h"

#include <raylib.h>


enum class GameState
{
	Pause,
	Play, 
	Finish
};

class GameLayer : public Layer
{
public:
	GameLayer();
	~GameLayer();

	virtual void OnUpdate(float frameTime) override;

private:
	void RenderCell(int x, int y, Vector2 pos, Vector2 size);

private:
	Maze* m_Maze;
	Vector2 m_MazeSize;
	GameState m_GameState;
	float m_TimeToMazeStep = 0;
};
