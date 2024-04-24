#include "Renderer.h"
#include "Application.h"

#include <raylib.h>


Renderer::Renderer(Window* window)
	: m_Window(window)
{

}

Renderer::~Renderer()
{

}

void Renderer::Begin()
{
	m_CurrentWidth = m_Window->GetWidth();
	m_CurrentHeight = m_Window->GetHeight();

	BeginDrawing();
}

void Renderer::End()
{
	EndDrawing();
}

void Renderer::Clear(Color color)
{
	ClearBackground(color);
}

void Renderer::RenderText(const std::string& text, int vx, int vy, Color color)
{
	int x = GetMappedCoordX(vx);
	int y = GetMappedCoordY(vy);

	DrawText(text.data(), x, y, m_FontSize, color);
}

void Renderer::RenderCenteredText(const std::string& text, int vx, int vy, int vwidth, int vheight, Color color)
{
	int x = GetMappedCoordX(vx);
	int y = GetMappedCoordY(vy);
	int width = GetMappedCoordX(vwidth);
	int height = GetMappedCoordY(vheight);
	
	Vector2 textSize = MeasureTextEx(GetFontDefault(), text.data(), m_FontSize, 1.f);
	int textX = x + (width - textSize.x) / 2;
	int textY = y + (height - textSize.y) / 2;

	DrawText(text.data(), textX, textY, m_FontSize, color);
}

void Renderer::RenderQuad(int vx, int vy, int vwidth, int vheight, Color color)
{
	int x = GetMappedCoordX(vx);
	int y = GetMappedCoordY(vy);
	int width = GetMappedCoordX(vwidth);
	int height = GetMappedCoordY(vheight);

	DrawRectangle(x, y, width, height, color);
}

bool Renderer::Button(const std::string& text, int vx, int vy, int vwidth, int vheight, Color bgcolor, Color textColor)
{
	RenderQuad(vx, vy, vwidth, vheight, bgcolor);
	RenderCenteredText(text, vx, vy, vwidth, vheight, textColor);

	int x = GetMappedCoordX(vx);
	int y = GetMappedCoordY(vy);
	int width = GetMappedCoordX(vwidth);
	int height = GetMappedCoordY(vheight);

	Vector2 mousePos = GetMousePosition();

	bool isMouseInside = true;
	isMouseInside = isMouseInside && mousePos.x >= x;
	isMouseInside = isMouseInside && mousePos.y >= y;
	isMouseInside = isMouseInside && mousePos.x <= x + width;
	isMouseInside = isMouseInside && mousePos.y <= y + height;

	if (!isMouseInside)
		return false;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		return true;

	return false;
}

void Renderer::SetFontSize(int fontSize)
{
	m_FontSize = fontSize;
}

int Renderer::GetMappedCoordX(int virtualX)
{
	float mappedX = (float)virtualX / s_VirtualViewportWidth;
	mappedX = mappedX * m_CurrentWidth;
	return (int)std::round(mappedX);
}

int Renderer::GetMappedCoordY(int virtualY)
{
	float mappedY = (float)virtualY / s_VirtualViewportHeight;
	mappedY = mappedY * m_CurrentHeight;
	return (int)std::round(mappedY);
}
