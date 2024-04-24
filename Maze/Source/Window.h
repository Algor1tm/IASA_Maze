#pragma once


class Window
{
public:
	Window(const char* title, unsigned int width, unsigned int height);
	~Window();

	void OnUpdate();

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;

private:
};