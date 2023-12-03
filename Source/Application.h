#pragma once

#include "GameEvent.h"
#include "Layer.h"

#include <vector>


// Pattern Singletone

class Application
{
public:
	Application();
	~Application();

	void Run();

	void QueueGameEvent(GameEvent event);
	void SetFPSLimit(float limit);

	static Application& Get() { return *s_Instance; }

private:
	void OnUpdate();
	void OnGameEvent(GameEvent event);

private:
	static Application* s_Instance;

private:
	float m_FPSLimit;
	bool m_Run;
	std::vector<Layer*> m_Layers;
};
