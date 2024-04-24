#pragma once

#include "Layer.h"
#include "Maze.h"
#include "Window.h"

#include <string>
#include <raylib.h>


// Virtual Coordinates
//	(0, 0)		    (1600, 0)
//			.
//			  .
//				.
//  (0, 900)	   (1600, 900)

class Renderer
{
public:
	Renderer(Window* window);
	~Renderer();

	void Begin();
	void End();

	void Clear(Color color);

	void RenderText(const std::string& text, int vx, int vy, Color color);
	void RenderCenteredText(const std::string& text, int vx, int vy, int vwidth, int vheight, Color color);
	void RenderQuad(int vx, int vy, int vwidth, int vheight, Color color);

	bool Button(const std::string& text, int vx, int vy, int vwidth, int vheight, Color bgcolor, Color textColor = BLACK);

	void SetFontSize(int fontSize);

	int GetViewportWidth() const { return s_VirtualViewportWidth; }
	int GetViewportHeight() const { return s_VirtualViewportHeight; }

private:
	int GetMappedCoordX(int virtualX);
	int GetMappedCoordY(int virtualY);

private:
	const int s_VirtualViewportWidth = 1600;
	const int s_VirtualViewportHeight = 900;

private:
	Window* m_Window;
	int m_CurrentWidth;
	int m_CurrentHeight;
	int m_FontSize;
};
