#pragma once

#include "Renderer.h"
#include "Window.h"
#include "Layer.h"

#include <iostream>
#include <format>
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
	void Close();

	std::mt19937& GetRandomEngine() { return m_RandomEngine; };
	Renderer& GetRenderer() { return *m_Renderer; }

	static Application& Get() { return *s_Instance; }

private:
	void OnUpdate(float frameTime);

private:
	static Application* s_Instance;

private:
	bool m_Run;
	std::mt19937 m_RandomEngine;
	Renderer* m_Renderer;
	Window* m_Window;
	std::vector<Layer*> m_Layers;
};
