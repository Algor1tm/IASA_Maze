#include "UILayer.h"
#include "Application.h"

#include <iostream>


UILayer::UILayer()
{

}

UILayer::~UILayer()
{

}

void UILayer::OnUpdate()
{
	// TODO: think of interface, draw Maze
	m_Maze;

	std::cout << "UILayer::OnUpdate()\n";

	// Example of code to exit from game
	//Application::Get().QueueGameEvent(GameEvent::Close);
}
