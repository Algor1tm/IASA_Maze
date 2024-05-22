#pragma once


class Renderer;

class Layer
{
public:
	virtual ~Layer() = default;

	// frameTime in milliseconds
	virtual void OnUpdate(float frameTime) {};
	virtual void OnRender(Renderer* renderer) {};
};
