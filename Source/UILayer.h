#pragma once

#include "Layer.h"
#include "Maze.h"


class UILayer: public Layer
{
public:
	UILayer();
	~UILayer();

	void SetContext(const Maze* maze) { m_Maze = maze; }
	virtual void OnUpdate() override;

private:
	const Maze* m_Maze = nullptr;
};
