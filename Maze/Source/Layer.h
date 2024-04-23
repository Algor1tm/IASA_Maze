#pragma once

#include "GameEvent.h"


class Layer
{
public:
	virtual ~Layer() = default;

	virtual void OnUpdate() {};
	virtual void OnGameEvent(GameEvent event) {};
};
