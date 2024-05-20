#include "Renderer.h"
#include "Application.h"

#include <raylib.h>


Renderer::Renderer(Window* window)
	: m_Window(window)
{
	m_Font = LoadFontEx("Assets/OpenSans-Regular.ttf", 57.f, 0, 250);
	SetTextureFilter(m_Font.texture, TEXTURE_FILTER_BILINEAR);
}

Renderer::~Renderer()
{
	UnloadFont(m_Font);
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

void Renderer::RenderText(const std::string& text, Vector2 pos, Color color)
{
	Vector2 mpos = GetMappedVector2(pos);
	DrawTextEx(m_Font, text.data(), mpos, m_FontSize, 1.0, color);
}

void Renderer::RenderCenteredText(const std::string& text, Vector2 pos, Vector2 size, Color color)
{
	Vector2 mpos = GetMappedVector2(pos);
	Vector2 msize = GetMappedVector2(size);

	Vector2 textSize = MeasureTextEx(m_Font, text.data(), m_FontSize, 1.f);
	int textX = mpos.x + (msize.x - textSize.x) / 2;
	int textY = mpos.y + (msize.y - textSize.y) / 2;

	DrawTextEx(m_Font, text.data(), {(float)textX, (float)textY}, m_FontSize, 1.0, color);
}

void Renderer::RenderQuad(Color color, Vector2 pos, Vector2 size)
{
	Vector2 mpos = GetMappedVector2(pos);
	Vector2 msize = GetMappedVector2(size);

	DrawRectangle((int)mpos.x, (int)mpos.y, (int)msize.x, (int)msize.y, color);
}

void Renderer::RenderQuad(Texture2D texture, Vector2 pos, Vector2 size, Color tint)
{
	Vector2 mpos = GetMappedVector2(pos);
	Vector2 msize = GetMappedVector2(size);

	Rectangle src = { 0, 0, texture.width, texture.height };
	Rectangle dst = { 0, 0, size.x, size.y };
	DrawTexturePro(texture, src, dst, pos, 0.f, tint);
}

bool Renderer::Button(const std::string& text, Vector2 pos, Vector2 size, Color bgcolor, Color textColor)
{
	RenderQuad(bgcolor, pos, size);
	RenderCenteredText(text, pos, size, textColor);

	Vector2 mpos = GetMappedVector2(pos);
	Vector2 msize = GetMappedVector2(size);

	Vector2 mousePos = GetMousePosition();

	bool isMouseInside = true;
	isMouseInside = isMouseInside && mousePos.x >= mpos.x;
	isMouseInside = isMouseInside && mousePos.y >= mpos.y;
	isMouseInside = isMouseInside && mousePos.x <= mpos.x + msize.x;
	isMouseInside = isMouseInside && mousePos.y <= mpos.y + msize.y;

	if (!isMouseInside)
		return false;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		return true;

	return false;
}

void Renderer::SetFontSize(float fontSize)
{
	float scale = m_CurrentHeight / 720.f;
	m_FontSize = fontSize * scale;
}

int Renderer::GetMappedCoordX(float virtualX)
{
	float mappedX = (float)virtualX / s_ViewportWidth;
	mappedX = mappedX * m_CurrentWidth;
	return (int)std::round(mappedX);
}

int Renderer::GetMappedCoordY(float virtualY)
{
	float mappedY = virtualY / s_ViewportHeight;
	mappedY = mappedY * m_CurrentHeight;
	return (int)std::round(mappedY);
}

Vector2 Renderer::GetMappedVector2(Vector2 vec2)
{
	return { (float)GetMappedCoordX(vec2.x), (float)GetMappedCoordY(vec2.y) };
}
