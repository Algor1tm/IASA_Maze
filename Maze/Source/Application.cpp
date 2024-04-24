#include "Application.h"

#include "GameLayer.h"
#include "UILayer.h"
#include "Debug.h"

#include <thread>

#include "raylib.h"

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

	const int screenWidth = 800;
	const int screenHeight = 450;

	SetTraceLogLevel(LOG_ERROR);
	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

	m_Run = true;

	while (m_Run)
	{
#if 0 
		nextFrame += milliseconds(int(1000.f / m_FPSLimit));

		OnUpdate();

		// We need to visualize our program slowly, so we need
		// to strictly limit our fps.
		// In the future UI and game logic will have different update frequency.
		// For example, UI window has VSync('60' fps), but game logic updates ones per second.
		std::this_thread::sleep_until(nextFrame);
#else
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		EndDrawing();

		if (WindowShouldClose())
			m_Run = false;
#endif
	}

	CloseWindow();
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
