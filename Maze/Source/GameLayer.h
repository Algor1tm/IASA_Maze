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
	virtual void OnRender(Renderer* renderer) override;

private:
	void RenderCell(Renderer* renderer, int x, int y, Vector2 pos, Vector2 size);
	void Restart();
	Color Lerp(const Color& color1, const Color& color2, float t);

private:
	Maze* m_Maze = nullptr;
	Vector2 m_MazeSize;
	GameState m_GameState;
	float m_TimeToMazeStep = 0;
	std::unordered_map<Robot*, Color> m_RobotsColorMap;
};
