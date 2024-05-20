#pragma once


class Layer
{
public:
	virtual ~Layer() = default;

	// frameTime in milliseconds
	virtual void OnUpdate(float frameTime) {};
};
