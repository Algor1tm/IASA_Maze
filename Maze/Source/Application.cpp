#include "Application.h"

#include "GameLayer.h"
#include "Debug.h"

#include <filesystem>


Application* Application::s_Instance = nullptr;

Application::Application()
	: m_Run(false)
{
	ASSERT(s_Instance == nullptr);
	s_Instance = this;

	std::filesystem::current_path("../");

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
	using namespace std::chrono;
	m_Run = true;

	steady_clock::duration frameTime = milliseconds(16);

	while (m_Run)
	{
		steady_clock::time_point timestamp = high_resolution_clock::now();

		m_Renderer->Begin();
		
		float ms = duration_cast<microseconds>(frameTime).count() / 1000.f;
		OnUpdate(ms);

		m_Renderer->End();

		frameTime = high_resolution_clock::now() - timestamp;
	}
}

void Application::OnUpdate(float frameTime)
{
	for (Layer* layer : m_Layers)
	{
		layer->OnUpdate(frameTime);
	}

	m_Window->OnUpdate();
}

void Application::Close()
{
	m_Run = false;
}
