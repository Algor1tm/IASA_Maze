#include "Window.h"
#include "Application.h"

#include <raylib.h>


Window::Window(const char* title, unsigned int width, unsigned int height)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetConfigFlags(FLAG_VSYNC_HINT);

	SetTraceLogLevel(LOG_ERROR);
	InitWindow(width, height, title);
}

Window::~Window()
{
	CloseWindow();
}

void Window::OnUpdate()
{
	if (WindowShouldClose())
		Application::Get().Close();
}

unsigned int Window::GetWidth() const
{
	return GetScreenWidth();
}

unsigned int Window::GetHeight() const
{
	return GetScreenHeight();
}
