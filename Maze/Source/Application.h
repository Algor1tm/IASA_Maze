#pragma once

#include "GameEvent.h"
#include "Layer.h"

#include <vector>
#include <random>


// Pattern Singletone

class Application
{
public:
	Application();
	~Application();

	Application(const Application&) = delete;
	Application(Application&&) = delete;

	void Run();

	void QueueGameEvent(GameEvent event);

	void SetFPSLimit(float limit);
	float GetFPSLimit() const { return m_FPSLimit; }
	std::mt19937& GetRandomEngine() { return m_RandomEngine; };

	static Application& Get() { return *s_Instance; }

private:
	void OnUpdate();
	void OnGameEvent(GameEvent event);

private:
	static Application* s_Instance;

private:
	bool m_Run;
	float m_FPSLimit;
	std::mt19937 m_RandomEngine;
	std::vector<Layer*> m_Layers;
};
