#pragma once

#include <xhash>

struct Vector2i
{
	int x;
	int y;

	bool operator==(Vector2i other) const
	{
		return x == other.x && y == other.y;
	}
};


namespace std
{
	// Cantor pairing used for hashing two integers
	//https://stackoverflow.com/questions/919612/mapping-two-integers-to-one-in-a-unique-and-deterministic-way

	template<>
	struct hash<Vector2i>
	{
		size_t operator()(const Vector2i& p) const
		{
			int integer = (p.x + p.y) * (p.x + p.y + 1) / 2 + p.x;
			return hash<int>()(integer);
		}
	};
}
