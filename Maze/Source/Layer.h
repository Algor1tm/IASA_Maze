#pragma once


class Layer
{
public:
	virtual ~Layer() = default;

	virtual void OnUpdate() {};
};
