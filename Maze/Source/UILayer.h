#pragma once

#include "Layer.h"
#include "Maze.h"


class UILayer: public Layer
{
public:
	UILayer();
	~UILayer();

	virtual void OnUpdate() override;
	virtual void OnGameEvent(GameEvent event) override;

	void SetContext(const Maze* maze) { m_Maze = maze; }

private:
	char CellToChar(Cell cell);

private:
	const Maze* m_Maze = nullptr;
	bool m_GameFinished;
};
