#pragma once

#include "Layer.h"
#include "Maze.h"
#include "Window.h"

#include <string>
#include <raylib.h>


// Virtual Coordinates (aspect ratio - 16:9)
//	(0, 0)		    (160, 0)
//			.
//			  .
//				.
//  (0, 90)		    (160, 90)

class Renderer
{
public:
	Renderer(Window* window);
	~Renderer();

	void Begin();
	void End();

	void Clear(Color color);

	void RenderQuad(Color color, Vector2 pos, Vector2 size);
	void RenderQuad(Texture2D texture, Vector2 pos, Vector2 size, Color tint = WHITE);

	void RenderText(const std::string& text, Vector2 pos, Color color);
	void RenderCenteredText(const std::string& text, Vector2 pos, Vector2 size, Color color);

	bool Button(const std::string& text, Vector2 pos, Vector2 size, Color bgcolor, Color textColor = BLACK);

	void SetFontSize(float fontSize);
	float GetViewportWidth() const { return s_ViewportWidth; }
	float GetViewportHeight() const { return s_ViewportHeight; }

private:
	int GetMappedCoordX(float virtualX);
	int GetMappedCoordY(float virtualY);
	Vector2 GetMappedVector2(Vector2 vec2);

private:
	const float s_ViewportWidth = 160.f;
	const float s_ViewportHeight = 90.f;

private:
	Window* m_Window;
	int m_CurrentWidth;
	int m_CurrentHeight;

	Font m_Font;
	float m_FontSize;
};
