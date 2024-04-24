#include "GameLayer.h"
#include "Application.h"

#include <raylib.h>


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
	Renderer& renderer = Application::Get().GetRenderer();

	int viewportWidth = renderer.GetViewportWidth();
	int viewportHeight = renderer.GetViewportHeight();

	Vector2 mousePos = GetMousePosition();

	renderer.Clear(RAYWHITE);
	renderer.SetFontSize(20);

	if(renderer.Button("Exit!", 700, 400, 200, 100, GREEN))
	{
		Application::Get().Close();
	}

	//m_Maze->Step();
}
