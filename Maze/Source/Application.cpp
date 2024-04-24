#include "Application.h"

#include "GameLayer.h"
#include "Debug.h"


Application* Application::s_Instance = nullptr;

Application::Application()
	: m_Run(false)
{
	ASSERT(s_Instance == nullptr);
	s_Instance = this;

	m_RandomEngine = std::mt19937(std::random_device()());

	m_Window = new Window("Maze", 1280, 720);
	m_Renderer = new Renderer(m_Window);

	GameLayer* gameLayer = new GameLayer();
	m_Layers.push_back(gameLayer);
}

Application::~Application()
{
	for (Layer* layer : m_Layers)
		delete layer;
	
	delete m_Renderer;
	delete m_Window;
}

void Application::Run()
{
	m_Run = true;

	while (m_Run)
	{
		m_Renderer->Begin();
		
		OnUpdate();

		m_Renderer->End();
	}
}

void Application::OnUpdate()
{
	for (Layer* layer : m_Layers)
	{
		layer->OnUpdate();
	}

	m_Window->OnUpdate();
}

void Application::Close()
{
	m_Run = false;
}
