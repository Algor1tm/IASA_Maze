#include "Application.h"

#include "GameLayer.h"
#include "UILayer.h"
#include "Debug.h"

#include <thread>

Application* Application::s_Instance = nullptr;

Application::Application()
	: m_Run(false)
{
	ASSERT(s_Instance == nullptr);
	s_Instance = this;

	SetFPSLimit(5.f);
	m_RandomEngine = std::mt19937(std::random_device()());

	GameLayer* gameLayer = new GameLayer();
	UILayer* uiLayer = new UILayer();

	uiLayer->SetContext(gameLayer->GetMaze());

	m_Layers.push_back(gameLayer);
	m_Layers.push_back(uiLayer);

	QueueGameEvent(GameEvent::Start);
}

Application::~Application()
{
	for (Layer* layer : m_Layers)
	{
		delete layer;
	}
}

void Application::Run()
{
	using namespace std::chrono;

	steady_clock::time_point nextFrame = high_resolution_clock::now();

	m_Run = true;

	while (m_Run)
	{
		nextFrame += milliseconds(int(1000.f / m_FPSLimit));

		OnUpdate();

		// We need to visualize our program slowly, so we need
		// to strictly limit our fps.
		// In the future UI and game logic will have different update frequency.
		// For example, UI window has VSync('60' fps), but game logic updates ones per second.
		std::this_thread::sleep_until(nextFrame);
	}
}

void Application::QueueGameEvent(GameEvent event)
{
	// For now each event immediately gets dispatched.
	// Other, more advanced way, would be to save events in queue
	// and then process them in main loop.

	OnGameEvent(event);
}

void Application::SetFPSLimit(float limit)
{
	m_FPSLimit = limit;
}

void Application::OnUpdate()
{
	for (Layer* layer : m_Layers)
	{
		layer->OnUpdate();
	}
}

void Application::OnGameEvent(GameEvent event)
{
	if (event == GameEvent::Close || event == GameEvent::Finish)
	{
		m_Run = false;
	}

	for (Layer* layer : m_Layers)
	{
		layer->OnGameEvent(event);
	}
}
