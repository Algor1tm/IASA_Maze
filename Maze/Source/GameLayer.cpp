#include "GameLayer.h"

#include <iostream>


GameLayer::GameLayer()
{
	m_Maze = new Maze();
}

GameLayer::~GameLayer()
{
	delete m_Maze;
}

void GameLayer::OnUpdate()
{
	m_Maze->Step();
}

void GameLayer::OnGameEvent(GameEvent event)
{
	if (event == GameEvent::Start)
	{
		m_Maze->Start();
	}
}
